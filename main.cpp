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
    background secondBackground(firstBackground.getBackgroundRec().width, 0.f);

    // Test terrain
    Texture2D terrainTex = LoadTexture("data/terrain/1.png");
    Vector2 terrainPos{-500.f, windowDimensions[1] - 20};
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
        cameraView.x = camera.target.x - camera.offset.x;
        cameraView.width = windowDimensions[0];           //I have no idea why this line is necessary. Without it, nothing works — it's strange, and I don't want to know why that is.
        
        DrawRectangleLinesEx(cameraView, 1.f, BLACK);

        BeginDrawing();

            ClearBackground(WHITE);

            BeginMode2D(camera);

                // Draw background
                secondBackground.display();

                if(CheckCollisionRecs(firstBackground.getBackgroundRec(), cameraView))
                    firstBackground.display();
                else if (cameraView.x > firstBackground.getBackgroundPos().x){
                    firstBackground.updatePos(secondBackground.getBackgroundPos().x + secondBackground.getBackgroundRec().width, 0.f);
                } else if (cameraView.x < firstBackground.getBackgroundPos().x){
                    firstBackground.updatePos(secondBackground.getBackgroundPos().x - secondBackground.getBackgroundRec().width, 0.f);
                }

                if(CheckCollisionRecs(secondBackground.getBackgroundRec(), cameraView))
                    secondBackground.display();
                else if (cameraView.x > secondBackground.getBackgroundPos().x){
                    secondBackground.updatePos(firstBackground.getBackgroundPos().x + firstBackground.getBackgroundRec().width, 0.f);
                } else if (cameraView.x < secondBackground.getBackgroundPos().x){
                    secondBackground.updatePos(firstBackground.getBackgroundPos().x - firstBackground.getBackgroundRec().width, 0.f);
                }

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

            if(CheckCollisionRecs(firstBackground.getBackgroundRec(), cameraView))
                DrawText("TRUE", 200, 200, 50, RED);
            else
                DrawText("FALSE", 200, 200, 50, RED);

        EndDrawing();
    }
    CloseWindow();
}