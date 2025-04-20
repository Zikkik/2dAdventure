#include "raylib.h"

int main() {
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    int windowDimensions[2]{GetMonitorWidth(0), GetMonitorHeight(0)};

    InitWindow(windowDimensions[0], windowDimensions[1], "Game");

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();
}