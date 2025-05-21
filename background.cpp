#include "background.hpp"

background::background(float posX, float posY){
    backgroundScale = {4.f};
    backgroundTex = {LoadTexture("data/map/background.png")};
    backgroundPos = {posX, posY};
}

// Display background
void background::display(){ DrawTextureEx(backgroundTex, backgroundPos, 0.f, backgroundScale, WHITE); }


// Position update
void background::updatePos(float posX, float posY){ backgroundPos = {posX, posY}; }

// Return background position
Vector2 background::getBackgroundPos() { return backgroundPos; }

// Return background collision rectangle
Rectangle background::getBackgroundRec(){
    return Rectangle{
        backgroundPos.x,
        backgroundPos.y,
        backgroundTex.width * backgroundScale,
        backgroundTex.height * backgroundScale
    };
}