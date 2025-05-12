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
    Vector2 terrainPos{0.f, windowDimensions[1] / 2};
    terrain testTerrain(terrainPos, terrainTex);

    // Test player
    player testPlayer(windowDimensions[0], windowDimensions[1]);


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
            DrawRectangleLines(testTerrain.getCollisionRec(testPlayer.getWorldPos()).x,  
                                testTerrain.getCollisionRec(testPlayer.getWorldPos()).y,
                                testTerrain.getCollisionRec(testPlayer.getWorldPos()).width,
                                testTerrain.getCollisionRec(testPlayer.getWorldPos()).height,
                                RED
                            );

            // Test player tick
            testPlayer.tick(deltaTime);
            
            // Temporary collision check for tests
            if(CheckCollisionRecs(testTerrain.getCollisionRec(testPlayer.getWorldPos()), testPlayer.getCollisionRec()))
                testPlayer.undoMovement();

        EndDrawing();
    }
    CloseWindow();
}