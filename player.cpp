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
    fallTex = LoadTexture("data/animation/character-fall.png");
    actualTex = idleTex;

    // World position
    worldPos = {winWidth/2, 0};

    // Character size
    height = actualTex.height;
    scale = {3.f};

    // Movement variables
    speed = {200.f};
    rightLeft = {1.f};

    // Jump variables
    jumpForce = {-800.f};
    jumpTime = {0.f};
    maxJumpTime = {1.0f};
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