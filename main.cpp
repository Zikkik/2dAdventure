#include "raylib.h"
#include "player.hpp"
#include "terrain.hpp"
#include "background.hpp"

int main() {
    // Create new window for game (default fullscreen)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Game");
    float windowDimensions[2]{
        static_cast<float>(GetMonitorWidth(0)), 
        static_cast<float>(GetMonitorHeight(0))
    };

    // Setup background
    background firstBackground(0.f, 0.f);

    // Test terrain
    Texture2D terrainTex = LoadTexture("data/terrain/1.png");
    Vector2 terrainPos{windowDimensions[0] / 2 - terrainTex.width, windowDimensions[1] - 20};
    terrain testTerrain(terrainPos, terrainTex);

    // Test player
    player testPlayer(windowDimensions[0], windowDimensions[1] / 3);

    // Camera setup
    Camera2D camera = {};
        camera.target.x = {testPlayer.getWorldPos().x};
        camera.target.y = {windowDimensions[1] / 2};
        camera.offset = {windowDimensions[0] / 2 - testPlayer.getSize().x, windowDimensions[1] / 2};
        camera.rotation = {0.f};
        camera.zoom = {1.f};

    Rectangle cameraView = {};
        cameraView.x = {camera.target.x - camera.offset.x};
        cameraView.y = {camera.target.y - camera.offset.y};
        cameraView.width = {windowDimensions[0]};
        cameraView.height = {windowDimensions[1]};

    // Setup FPS
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
                firstBackground.display();
                
                //DrawTextureEx(background, backgroundPos2, 0.f, mapScale, WHITE);


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