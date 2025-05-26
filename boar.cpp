#include "boar.hpp"

boar::boar(float posX, float posY){
    // Texture load
    idleTex = LoadTexture("data/animation/boar-idle.png");
    walkTex = LoadTexture("data/animation/boar-walk.png");
    runTex = LoadTexture("data/animation/boar-run.png");
    vanishTex = LoadTexture("data/animation/boar-vanish.png");
    actualTex = idleTex;

    // World position
    worldPos = {posX, posY};

    // Character size
    height = actualTex.height;
    scale = {3.f};

    // Movement variables
    speed = {400.f};
    rightLeft = {1.f};
}

Rectangle boar::getCollisionRec(){
    if(actualTex.id == idleTex.id)
        return Rectangle {
            worldPos.x,
            worldPos.y,
            width * scale,
            height * scale
        };
}