#include "character.hpp"
#include "raymath.h"

character::character(){
    frame = {0};
    maxFrames = {};
    runningTime = {0.f};
    updateTime = {1.f / 8.f};
}

void character::tick(float deltaTime){
    bool isMoving = Vector2Length(velocity) != 0.0;

    // Jeśli porusza się – zapisz czas ostatniego ruchu
    if (isMoving) {
        lastMoveTime = GetTime(); // raylib: zwraca czas w sekundach
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
    
        if (velocity.x < 0.f) rightLeft = -1.f;
        else if (velocity.x > 0.f) rightLeft = 1.f;
    }
    
    // Czy nadal jesteśmy „w stanie ruchu” mimo braku inputu?
    bool withinGracePeriod = (GetTime() - lastMoveTime) < moveGracePeriod;
    
    if (isMoving || withinGracePeriod) {
        actualTex = runTex;
        maxFrames = 8;
    } else {
        actualTex = idleTex;
        maxFrames = 4;
    }
    
    width = actualTex.width / maxFrames;
    velocity = {}; // reset prędkości
    
    // Rysowanie
    Rectangle source{width * frame, 0.f, width * rightLeft, height};
    Rectangle dest{worldPos.x, worldPos.y, scale * width, scale * height};
    DrawTexturePro(actualTex, source, dest, Vector2{}, 0.f, WHITE);
    
}