#include "character.hpp"
#include "raymath.h"

character::character(){
    // Flags
    isMoving = false;
    isOnGround = false;

    // Animation variables
    frame = {};
    maxFrames = {};
    stopDelay = {0.1f};
    stopCounter = {0.f};
    runningTime = {0.f};
    updateTime = {1.f / 8.f};
    animCorretion = {0.f};

    // Collision variables
    paddingX = {65.f};
    paddingY = {50.f};
}

// Return charater world position
Vector2 character::getWorldPos(){ return worldPos; }

// Change position to previous character's position
void character::undoMovement(){ worldPos = worldPosLast; }

// Update the texture based on the movement animation
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

    // Time between animation frames
    runningTime += deltaTime;
    if(runningTime >= updateTime){
        frame++;
        runningTime = 0;
        if(frame >= maxFrames) frame = 0;
    }

    // Check character's velocity
    if (Vector2Length(velocity) != 0.0){
        // Update world position
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        // Change texture direction
        if(velocity.x < 0.f) {
            rightLeft = -1.f;
            animCorretion = 0.f;
        } else {
            rightLeft = 1.f;
            // Animation correction
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

    // Reset character's velocity
    velocity = {};
}

void character::renderCharacter(){
        Rectangle source{width * frame, 0.f, width * rightLeft, height};
        Rectangle dest{worldPos.x - animCorretion, worldPos.y, scale * width, scale * height};
        DrawTexturePro(actualTex, source, dest, Vector2{}, 0.f, WHITE);
}

void character::tick(float deltaTime){

    // Testing
    Rectangle testCol = getCollisionRec();
    if(actualTex.id == idleTex.id)
        DrawRectangleLines(testCol.x, testCol.y, testCol.width, testCol.height, RED);
    if(actualTex.id == runTex.id)
        DrawRectangleLines(testCol.x, testCol.y, testCol.width, testCol.height, PURPLE);
   
    moveCharacter(deltaTime);

    
    renderCharacter();
}

Rectangle character::getCollisionRec(){
    // Return the rectangle based on character's actual animation
    if(actualTex.id == idleTex.id)
        characterRec = {
            worldPos.x + paddingX,
            worldPos.y + paddingY,
            width * scale - paddingX * 2,
            height * scale - paddingY * 2
        };

    if(actualTex.id == runTex.id)
        characterRec = {
            worldPos.x + paddingX - width / 4,
            worldPos.y + paddingY,
            width * scale - paddingX * 2,
            height * scale - paddingY * 2
        };
    
    return characterRec;
}

void character::snapToGround(Rectangle ground){
    if(isOnGround){
        worldPos.y = ground.y - height * scale + paddingY + 3;
        worldPosLast.y = ground.y - height * scale + paddingY + 3;
    }
}

void character::checkTopCollision(Rectangle terrainCollision){
    // Auxiliary variables
    float characterBottom = worldPos.y + getCollisionRec().height  + paddingY;
    float terrainTop = terrainCollision.y + 8;

    // Check kollision with terrain and top edge
    if(CheckCollisionRecs(terrainCollision, getCollisionRec()) && 
        characterBottom <= terrainTop)
            isOnGround = true;
    else 
        isOnGround = false;

    snapToGround(terrainCollision);
}