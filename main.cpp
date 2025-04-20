#include "raylib.h"

int main() {
    // Create new window for game (default fullscreen)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    int windowDimensions[2]{GetMonitorWidth(0), GetMonitorHeight(0)};
    InitWindow(windowDimensions[0], windowDimensions[1], "Game");

    Texture2D background = LoadTexture("data/map/background.png");
    Vector2 backgroundPos{0.f, 0.f};
    float mapScale{4.f};

    // Game loop
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

            DrawTextureEx(background, backgroundPos, 0.f, mapScale, WHITE);
            
        EndDrawing();
    }

    CloseWindow();
}