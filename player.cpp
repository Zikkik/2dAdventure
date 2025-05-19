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
    bool wasOnGround = isOnGround;

    // Keyboard movement
    if(IsKeyDown(KEY_A)) velocity.x -= 1.f;
    if(IsKeyDown(KEY_D)) velocity.x += 1.f;
    if(IsKeyDown(KEY_W) && isOnGround) isInJump = true;

    if(isInJump) jump(deltaTime);
    updateTex();
    character::tick(deltaTime);

    if (!wasOnGround && isOnGround)
        landingTimer = 0.f;
}

void player::updateTex(){
    if(!isOnGround){
        actualTex = fallTex;
        maxFrames = 3;
        frame = 0;
        width = actualTex.width / maxFrames;
        landingTimer = 0.f;

    } else if (landingTimer < landingDuration) {
        actualTex = fallTex;
        maxFrames = 3;
        frame = static_cast<int>((landingTimer / landingDuration) * 2.f);

        if(frame >  2) frame = 2;

        width = actualTex.width / maxFrames;
        landingTimer += GetFrameTime();

    } else
        character::updateTex();
}

// Fall collision
Rectangle player::getCollisionRec(){
        if(actualTex.id == fallTex.id)
            characterRec = {
                worldPos.x + paddingX - width / 4,
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
    isOnGround = false;

    jumpTime += deltaTime;
    if(jumpTime <= maxJumpTime){
        velocity.y = jumpForce;
        jumpForce = jumpForce + 15;
    } else {
        isInJump = false;
        jumpForce = -600.f;
        jumpTime = 0.f;
    }
}