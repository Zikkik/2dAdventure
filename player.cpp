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
    worldPos = {winWidth/2, winHeight/2};

    // Character size
    height = actualTex.height;
    scale = {3.f};

    // Movement variables
    speed = {200.f};
    rightLeft = {1.f};
}

void player::tick(float deltaTime){
    // Keyboard movement
    if(IsKeyDown(KEY_A)) velocity.x -= 1.f;
    if(IsKeyDown(KEY_D)) velocity.x += 1.f;

    updateTex();
    character::tick(deltaTime);
}

void player::updateTex(){
    if(!isOnGround){
        actualTex = fallTex;
        maxFrames = 3;
        width = actualTex.width / maxFrames;
    } else {
        character::updateTex();
    }   
}

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