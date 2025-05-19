#include "raylib.h"
#include "character.hpp"

class player : public character{
    private:
        // Jump variables (unique for player)
        Texture2D jumpTex;
        float jumpForce;

        // Landing variables (for animation)
        float landingTimer;
        float landingDuration;

        // Window size
        float windowWidth;
        float windowHeight;
    public:
        player(float winWidth, float winHeight);

        // Overrided tick from the character class
        virtual void tick(float deltaTime) override;

        // Overrided texture update
        virtual void updateTex() override;

        // Overrided collision rectangle
        virtual Rectangle getCollisionRec();

        // Jump function
        void jump();
};