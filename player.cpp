#include "player.hpp"

player::player(float winWidth, float winHeight) 
    : character()
{
    idleTex = LoadTexture("data/animation/character-idle.png");
    runTex = LoadTexture("data/animation/character-run.png");
    actualTex = idleTex;
    worldPos = {winWidth/2, winHeight/2};
    height = actualTex.height;
    scale = {4.f};
    speed = {2.f};
    rightLeft = {1.f};
}

void player::tick(float deltaTime){
    if(IsKeyDown(KEY_A)) velocity.x -= 1.0;
    if(IsKeyDown(KEY_D)) velocity.x += 1.0;

    character::tick(deltaTime);
}