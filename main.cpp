#include "raylib.h"
#include "player.hpp"
#include "terrain.hpp"

int main() {
    // Create new window for game (default fullscreen)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Game");
    float windowDimensions[2]{
        static_cast<float>(GetMonitorWidth(0)), 
        static_cast<float>(GetMonitorHeight(0))
    };

    // Setup background
    float mapScale = {4.5f};
    Texture2D background = LoadTexture("data/map/background.png");
    Vector2 backgroundPos1 = {0.f, 0.f};
    Vector2 backgroundPos2 = {background.width * mapScale, 0.f};

    // Test terrain
    Texture2D terrainTex = LoadTexture("data/terrain/1.png");
    Vector2 terrainPos{windowDimensions[0] / 2 - terrainTex.width, windowDimensions[1] - 20};
    terrain testTerrain(terrainPos, terrainTex);

    // Test player
    player testPlayer(windowDimensions[0], windowDimensions[1] / 3);

    // Camera setup
    float playerAnchor = {windowDimensions[0] / 2 - testPlayer.getSize().x};
    Camera2D camera = {};
    camera.target.y = {windowDimensions[1] / 2};
    camera.offset = {playerAnchor, windowDimensions[1] / 2};
    camera.rotation = {0.f};
    camera.zoom = {1.f};


    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        float const deltaTime = GetFrameTime();

        // Camera following player in X
        camera.target.x = testPlayer.getWorldPos().x;
        
        BeginDrawing();

            ClearBackground(WHITE);

            BeginMode2D(camera);

                // Draw background
                DrawTextureEx(background, backgroundPos1, 0.f, mapScale, WHITE);
                DrawTextureEx(background, backgroundPos2, 0.f, mapScale, WHITE);

                // Debug
                DrawText(TextFormat("CameraTarget: %.2f", camera.target.x), 200, 200, 20, GREEN);
                DrawText(TextFormat("CameraTarget: %.2f", camera.offset), 200, 220, 20, GREEN);

                // Draw test terrain with collision rectangle
                testTerrain.renderTerrain();
                DrawRectangleLines(testTerrain.getCollisionRec().x,  
                                    testTerrain.getCollisionRec().y,
                                    testTerrain.getCollisionRec().width,
                                    testTerrain.getCollisionRec().height,
                                    RED
                                );

                // Test player tick
                testPlayer.tick(deltaTime);

                testPlayer.checkTopCollision(testTerrain.getCollisionRec());
                
                // Temporary collision check for tests
                //if(CheckCollisionRecs(testTerrain.getCollisionRec(), testPlayer.getCollisionRec()))
                //   testPlayer.undoMovement();

            EndMode2D();

        EndDrawing();
    }
    CloseWindow();
}