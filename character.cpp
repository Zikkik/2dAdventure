#include "character.hpp"
#include "raymath.h"

character::character(){
    isMoving = false;
    isFalling = false;
    frame = {0};
    maxFrames = {};
    stopDelay = {0.1f};
    stopCounter = {0.f};
    runningTime = {0.f};
    updateTime = {1.f / 8.f};
    gravity = {1000};
    animCorretion = {0.f};
}

Vector2 character::getWorldPos(){ return worldPos; }

void character::undoMovement(){ worldPos = worldPosLast; }

void character::updateTex(){
    if (isMoving){
        actualTex = runTex;
        maxFrames = 8;
    } else {
        actualTex = idleTex;
        maxFrames = 4;
    }

    width = actualTex.width / maxFrames;
}

void character::moveCharacter(float deltaTime){
    worldPosLast = worldPos;

    runningTime += deltaTime;
    if(runningTime >= updateTime){
        frame++;
        runningTime = 0;
        if(frame >= maxFrames) frame = 0;
    }

    if (Vector2Length(velocity) != 0.0){
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        if(velocity.x < 0.f) {
            rightLeft = -1.f;
            animCorretion = 0.f;
        } else {
            rightLeft = 1.f;
            animCorretion = width / 2;
        }

        stopCounter = 0.f;
        isMoving = true;
    } else {
        stopCounter += deltaTime;
        if(stopCounter >= stopDelay){
            isMoving = false;
            animCorretion = 0.f;
        }
    }

    updateTex();

    velocity = {};
}

void character::renderCharacter(){
        Rectangle source{width * frame, 0.f, width * rightLeft, height};
        Rectangle dest{worldPos.x - animCorretion, worldPos.y, scale * width, scale * height};
        DrawTexturePro(actualTex, source, dest, Vector2{}, 0.f, WHITE);
}

void character::tick(float deltaTime){

    Rectangle testCol = getCollisionRec();
    if(actualTex.id == idleTex.id)
        DrawRectangleLines(testCol.x, testCol.y, testCol.width, testCol.height, RED);
    if(actualTex.id == runTex.id)
        DrawRectangleLines(testCol.x, testCol.y, testCol.width, testCol.height, PURPLE);
   
    moveCharacter(deltaTime);




    if(isFalling)
        velocity.y += gravity * deltaTime;
    
    renderCharacter();
}

Rectangle character::getCollisionRec(){
    float paddingX = 130.f;
    float paddingY = 100.f;

    if(actualTex.id == idleTex.id)
        return Rectangle{
            worldPos.x + paddingX / 2,
            worldPos.y + paddingY / 2,
            width * scale - paddingX,
            height * scale - paddingY
        };

    if(actualTex.id == runTex.id)
        return Rectangle{
            worldPos.x + paddingX / 2 - width / 4,
            worldPos.y + paddingY / 2,
            width * scale - paddingX,
            height * scale - paddingY
        };


    return Rectangle{0};
}