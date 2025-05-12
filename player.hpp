#include "raylib.h"
#include "character.hpp"

class player : public character{
    private:
        // Jump variables (unique for player)
        Texture2D jumpTex;
        int jumpVelocity;

        // Window size
        float windowWidth;
        float windowHeight;
    public:
        player(float winWidth, float winHeight);

        // Overrided tick from the character class
        virtual void tick(float deltaTime) override;
};