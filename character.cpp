#include "character.hpp"
#include "raymath.h"

character::character(){
    isMoving = false;
    frame = {0};
    maxFrames = {};
    stopDelay = {0.1f};
    stopCounter = {0.f};
    runningTime = {0.f};
    updateTime = {1.f / 8.f};

}

void character::tick(float deltaTime){
    runningTime += deltaTime;
    if(runningTime >= updateTime){
        frame++;
        runningTime = 0;
        if(frame >= maxFrames) frame = 0;
    }

    Texture2D prevTex = actualTex;

    if (Vector2Length(velocity) != 0.0){
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        if(velocity.x < 0.f)
            rightLeft = -1.f;
        else
            rightLeft = 1.f;

        stopCounter = 0.f;
        isMoving = true;
    } else {
        stopCounter += deltaTime;
        if(stopCounter >= stopDelay)
            isMoving = false;
    }

    if (isMoving){
        actualTex = runTex;
        maxFrames = 8;
    } else {
        actualTex = idleTex;
        maxFrames = 4;
    }

    width = actualTex.width / maxFrames;

    velocity = {};

    Rectangle source{width * frame, 0.f, width * rightLeft, height};
    Rectangle dest{worldPos.x, worldPos.y, scale * width, scale * height};
    DrawTexturePro(actualTex, source, dest, Vector2{}, 0.f, WHITE);
}