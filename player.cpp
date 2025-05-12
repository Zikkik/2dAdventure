#include "player.hpp"

player::player(float winWidth, float winHeight) : 
    character(),
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    // Texture load
    idleTex = LoadTexture("data/animation/character-idle.png");
    runTex = LoadTexture("data/animation/character-run.png");
    jumpTex = LoadTexture("data/animation/character-jump");
    actualTex = idleTex;

    // World position
    worldPos = {winWidth/2, winHeight/2};

    // Character size
    height = actualTex.height;
    scale = {3.f};

    speed = {4.f};
    rightLeft = {1.f};
}

void player::tick(float deltaTime){
    // Keyboard movement
    if(IsKeyDown(KEY_A)) velocity.x -= 1.f;
    if(IsKeyDown(KEY_D)) velocity.x += 1.f;
    if(IsKeyDown(KEY_W)) velocity.y -= 1.f;
    if(IsKeyDown(KEY_S)) velocity.y += 1.f;

    character::tick(deltaTime);
}