#include "player.hpp"

player::player(float winWidth, float winHeight) : 
    character(),
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    idleTex = LoadTexture("data/animation/character-idle.png");
    runTex = LoadTexture("data/animation/character-run.png");
    jumpTex = LoadTexture("data/animation/character-jump");
    jumpVelocity = {-600};
    actualTex = idleTex;
    worldPos = {winWidth/2, winHeight/2};
    height = actualTex.height;
    scale = {3.f};
    speed = {4.f};
    rightLeft = {1.f};
}

void player::tick(float deltaTime){
    if(IsKeyDown(KEY_A)) velocity.x -= 1.f;
    if(IsKeyDown(KEY_D)) velocity.x += 1.f;

    character::tick(deltaTime);
}

Vector2 player::getScreenPos(){
    return Vector2{
        windowWidth / 2.0f - scale * (0.5f * width), 
        windowHeight / 2.0f - scale * (0.5f * height)
    };
}