#include <array>
#include "raylib.h"
#include "player.hpp"
#include "terrain.hpp"
#include "background.hpp"
#include "boar.hpp"

int main() {
    // Create new window for game (default fullscreen)
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Game");
    float windowDimensions[2]{
        static_cast<float>(GetMonitorWidth(0)), 
        static_cast<float>(GetMonitorHeight(0))
    };

    // Setup background
    background background(0.f, 0.f);

    // Terrain load
    terrain ground( Vector2 { -100.f, windowDimensions[1] - 50.f },
                    LoadTexture("data/terrain/ground.png"),
                    4.5f);

    terrain leftIsland( Vector2 { -100.f, windowDimensions[1] / 1.7},
                    LoadTexture("data/terrain/island.png"),
                    3.f);

    terrain rightIsland( Vector2 { windowDimensions[0] - 824.f, windowDimensions[1] / 2 },
                    LoadTexture("data/terrain/island.png"),
                    3.f);

    std::array <terrain*, 3> terrains = {&ground, &leftIsland, &rightIsland};

    // Test player
    player testPlayer(windowDimensions[0], windowDimensions[1] / 3);

    // Test boar
    boar testBoar(windowDimensions[0] / 2, windowDimensions[1] / 3);

    // Setup FPS
    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        float const deltaTime = GetFrameTime();

        BeginDrawing();

            ClearBackground(WHITE);

                background.display();

                // Collision check between player and terrains
                bool grounded = false;
                for (terrain* t : terrains) {
                    t->renderTerrain();
                    if(testPlayer.checkTopCollision(t->getCollisionRec()))
                        grounded = true;
                }

                testPlayer.setOnGround(grounded);
                testPlayer.tick(deltaTime);


        EndDrawing();
    }
    CloseWindow();
}