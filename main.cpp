#include "raylib.h"
#include "player.hpp"
#include "terrain.hpp"

int main() {
    // Create new window for game (default fullscreen)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Game");
    float windowDimensions[2]{
        static_cast<float>(GetMonitorWidth(0)), 
        static_cast<float>(GetMonitorHeight(0))};

    // Setup background
    Texture2D background = LoadTexture("data/map/background.png");
    Vector2 backgroundPos{0.f, 0.f};
    float mapScale{4.f};

    // Test terrain
    Texture2D terrainTex = LoadTexture("data/terrain/1.png");
    Vector2 terrainPos{windowDimensions[0] / 2 - terrainTex.width, windowDimensions[1] - 20};
    terrain testTerrain(terrainPos, terrainTex);

    // Test player
    player testPlayer(windowDimensions[0], windowDimensions[1] / 3);


    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        float const deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

            // Draw background
            DrawTextureEx(background, backgroundPos, 0.f, mapScale, WHITE);

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

        EndDrawing();
    }
    CloseWindow();
}