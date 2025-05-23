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
    worldPos = {winWidth / 2, 0};

    // Character size
    height = actualTex.height;
    scale = {3.f};

    // Movement variables
    speed = {500.f};
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
    if(IsKeyDown(KEY_A) && !isInAttack) velocity.x -= 1.f;
    if(IsKeyDown(KEY_D) && !isInAttack) velocity.x += 1.f;
    if(IsKeyPressed(KEY_SPACE)){
        isInAttack = true;
        frame = 0;
    }

    if(IsKeyDown(KEY_W) && isOnGround) {
        isInJump = true;
        frame = 0;
    }

    // Test
    if(actualTex.id == attackTex.id)
        DrawRectangleLinesEx(getCollisionRec(), 1.f, BLACK);
    if(actualTex.id == jumpTex.id)
        DrawRectangleLinesEx(getCollisionRec(), 1.f, BLACK);

    if(isInJump && !jumpCeiling) jump(deltaTime);

    character::tick(deltaTime);
}

// Overrided updateTex
void player::updateTex(){
    if(isInAttack){
        actualTex = attackTex;
        maxFrames = 8;
        height = attackTex.height;
        width = attackTex.width / maxFrames;
        if (frame >= maxFrames - 1)
            isInAttack = false;

    } else if(isInJump && !isOnGround){
        actualTex = jumpTex;
        maxFrames = 15;
        height = jumpTex.height;
        width = jumpTex.width / maxFrames;

    } else
        character::updateTex();
}

// Overrided changeDirection
void player::changeDirection(){
    if(isInJump){
        // During jump left
        if(rightLeft == -1.f) {
            animCorrection = width / 4;
        // During jump right
        } else {
            animCorrection = -width / 2.5;
        }

    } else if(isInAttack){
        // During attack left
        if(rightLeft == -1.f) 
            animCorrection = width / 3.5;

        // During attack right
        else if(rightLeft == 1.f) 
            animCorrection = width / 2.5;

    } else
        character::changeDirection();
}

void player::updateFrame(float deltaTime){
    if(isInAttack)
        updateTime = 1.f / 10.f;
    else
        updateTime = 1.f / 8.f;

    character::updateFrame(deltaTime);
}

// Player collisions
Rectangle player::getCollisionRec(){
        if(actualTex.id == jumpTex.id)
            characterRec = {
                worldPos.x + paddingX,
                worldPos.y + paddingY,
                width * scale - paddingX * 2,
                height * scale - paddingY * 2
            };

        if(actualTex.id == attackTex.id)
            characterRec = {
                worldPos.x + paddingX,
                worldPos.y + paddingY,
                width * scale - paddingX * 3,
                height * scale - paddingY * 2
            };

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

void player::attack(float deltaTime){
    isInAttack = true;
}