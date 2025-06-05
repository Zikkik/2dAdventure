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
    isOnPatrol = {true};
    chargeTargetReached = {false};

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
    if(isAlive){
        if(!recentlyDamaged){ 
            if(isOnPatrol)
                boarPatrol(movementRangeLeft, movementRangeRight);

            if(isInCharge)
                boarCharge();
        }

        character::tick(deltaTime);
    }

    DrawText(TextFormat("isAlive: %.s", isAlive ? "TRUE" : "FALSE"), 100, 100, 20, RED);
}

// Update the texture based on the movement animation
void boar::updateTex(){
    if (isOnPatrol){
        actualTex = walkTex;
        maxFrames = 6;
        height = walkTex.height;
    } 
    
    if (isInCharge){
        actualTex = runTex;
        maxFrames = 6;
        height = runTex.height;
    }

    if (recentlyDamaged){
        actualTex = vanishTex;
        maxFrames = 4;
        height = vanishTex.height;
    }

    width = actualTex.width / maxFrames;
}

// Change boar speed and lock direction
void boar::boarCharge(){
    speed = 400.f;
    velocity.x = direction;
}

// Boar patrol space beetween two points
void boar::boarPatrol(float pointA, float pointB){
    speed = 250.f;

    if(fabs(characterRec.x - pointA) < 5.f){
        direction = {1.f};
        if(isInCharge)
            isInCharge = false;
    }

    if(fabs(characterRec.x + characterRec.width - pointB) < 5.f){
        direction = {-1.f};
        if(isInCharge)
            isInCharge = false;
    }

    velocity.x = direction;
}

// Boar charge toward the player
void boar::chargeCheck(Rectangle *player){
    if (isInCharge) return;

    Vector2 playerPos = {player->x + player->width / 2, player->y + player->height};
    Vector2 boarPos = {characterRec.x + characterRec.width / 2, characterRec.y + characterRec.height};

    float distance = Vector2Distance(playerPos, boarPos);
    bool isPlayerInFront = (direction > 0 && playerPos.x > boarPos.x) || 
                           (direction < 0 && playerPos.x < boarPos.x);

    if (player->x >= movementRangeLeft && player->x <= movementRangeRight 
        && isPlayerInFront && distance <= 300.f) {
        isInCharge = true;
    }
}