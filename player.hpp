#include "raylib.h"
#include "character.hpp"

class player : public character{
    private:
        Texture2D jumpTex;
        int jumpVelocity;
        float windowWidth;
        float windowHeight;
    public:
        player(float winWidth, float winHeight);
        virtual void tick(float deltaTime) override;
        Vector2 getScreenPos();
};