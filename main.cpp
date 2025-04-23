#include "raylib.h"
#include "player.hpp"

int main() {
    // Create new window for game (default fullscreen)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Game");
    int windowDimensions[2]{GetMonitorWidth(0), GetMonitorHeight(0)};


    // Setup background
    Texture2D background = LoadTexture("data/map/background.png");
    Vector2 backgroundPos{0.f, 0.f};
    float mapScale{4.f};

    player test(windowDimensions[0], windowDimensions[1]);


    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);


            // Draw Background
            DrawTextureEx(background, backgroundPos, 0.f, mapScale, WHITE);

            test.tick(deltaTime);
            
        EndDrawing();
    }

    CloseWindow();
}