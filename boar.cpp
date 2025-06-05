#include "boar.hpp"

boar::boar(float posX, float posY){
    // Texture load
    idleTex = LoadTexture("data/animation/boar-idle.png");
    walkTex = LoadTexture("data/animation/boar-walk.png");
    runTex = LoadTexture("data/animation/boar-run.png");
    vanishTex = LoadTexture("data/animation/boar-vanish.png");
    actualTex = idleTex;

    // Flags
    isInCharge = {false};

    // World position
    worldPos = {posX, posY};

    // Character size
    height = actualTex.height;
    scale = {3.f};

    // Movement variables
    speed = {250.f};
    rightLeft = {1.f};
    direction = {1.f};
    movementRangeLeft = {worldPos.x - 500.f};
    movementRangeRight = {worldPos.x + 500.f};

    // Collision variables
    paddingX = {15.f};
    paddingY = {};

    // Gameplay variables
    health = {2};
    damage = {2};
}

void boar::tick(float deltaTime){
    boarPatrol(movementRangeLeft, movementRangeRight);
    velocity.x = direction;

    DrawLine(movementRangeLeft, 0.f, movementRangeLeft, 1920.f, BLACK);
    DrawLine(movementRangeRight, 0.f, movementRangeRight, 1920.f, BLACK);

    character::tick(deltaTime);
}

// Update the texture based on the movement animation
void boar::updateTex(){
    if (isMoving){
        actualTex = walkTex;
        maxFrames = 6;
        height = walkTex.height;
    } else if (isInCharge){
        actualTex = runTex;
        maxFrames = 6;
        height = runTex.height;
    }

    width = actualTex.width / maxFrames;
}

void boar::boarPatrol(float pointA, float pointB){
    if(fabs(characterRec.x - pointA) < 5.f)
        direction = {1.f};

    if(fabs(characterRec.x + characterRec.width - pointB) < 5.f)
        direction = {-1.f};
}

void boar::boarCharge(Rectangle *player){
    Vector2 playerPos = {player->x + player->width / 2, player->y + player->height};
    Vector2 boarPos = {characterRec.x + characterRec.width / 2, characterRec.y + characterRec.height};

    if(Vector2Distance(playerPos, boarPos) <= 200.f)
        isInCharge = true;
}