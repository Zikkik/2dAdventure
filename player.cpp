#include "player.hpp"

player::player(float winWidth, float winHeight) : 
    character(),
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    // Texture load
    idleTex = LoadTexture("data/animation/character-idle.png");
    runTex = LoadTexture("data/animation/character-run.png");
    jumpTex = LoadTexture("data/animation/character-jump.png");
    attackTex = LoadTexture("data/animation/character-attack.png");
    actualTex = idleTex;

    // World position
    worldPos = { winWidth / 2, 0 };

    // Character size
    height = actualTex.height;
    scale = {3.f};

    // Movement variables
    speed = {200.f};
    rightLeft = {1.f};

    // Attack variables
    isInAttack = {false};

    // Jump variables
    jumpForce = {-800.f};
    jumpTime = {0.f};
    maxJumpTime = {1.0f};
    jumpCeiling = {false};
    isInJump = {false};
}

// Player tick
void player::tick(float deltaTime){

    // Keyboard movement
    if(IsKeyDown(KEY_A)) velocity.x -= 1.f;
    if(IsKeyDown(KEY_D)) velocity.x += 1.f;
    if(IsKeyDown(KEY_W) && isOnGround) {
        isInJump = true;
        frame = 0;
    }

    if(isInJump && !jumpCeiling) jump(deltaTime);
    updateTex();
    character::tick(deltaTime);
}


// Overrided updateTex
void player::updateTex(){
    if(isInJump && !isOnGround){
        if(!isOnGround){
            actualTex = jumpTex;
            maxFrames = 15;
            height = jumpTex.height;
            width = jumpTex.width / maxFrames;
        }
    } else
        character::updateTex();
}

// Overrided changeDirection
void player::changeDirection(){
    if(isInJump){
        animCorrection = width / 4;

        // During jump left
        if(velocity.x < 0.f) {
            rightLeft = -1.f;
            animCorrection = width / 4;
        // During jump right
        } else if(velocity.x > 0.f || rightLeft == 1.f) {
            rightLeft = 1.f;
            animCorrection = -width / 2.5;
        }
    } else
        character::changeDirection();
}

// Fall collision
Rectangle player::getCollisionRec(){
        if(actualTex.id == jumpTex.id)
            characterRec = {
                worldPos.x + paddingX,
                worldPos.y + paddingY,
                width * scale - paddingX * 2,
                height * scale - paddingY * 2
            };
        else
            character::getCollisionRec();
    return characterRec;
}

void player::checkTopCollision(Rectangle terrainCollision){
    
    // Auxiliary variables to calculate character down edge and top edge of terrain
    float characterBottom = worldPos.y + getCollisionRec().height  + paddingY;
    float terrainTop = terrainCollision.y + 8;

    // Check collision with terrain and top edge
    if(CheckCollisionRecs(terrainCollision, getCollisionRec()) && 
        characterBottom <= terrainTop){
            isOnGround = true;
            isInJump = false;
            jumpCeiling = false;
            snapToGround(terrainCollision);
        } else 
            isOnGround = false;
}

// Jump method
void player::jump(float deltaTime){
    jumpTime += deltaTime;

    if(jumpTime <= maxJumpTime){
        velocity.y = jumpForce;
        jumpForce = jumpForce + 15;
    } else {
        jumpCeiling = true;
        jumpForce = -800.f;
        jumpTime = 0.f;
    }
}