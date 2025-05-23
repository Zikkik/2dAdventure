#include "raylib.h"
#include "character.hpp"

class player : public character{
    private:
        // Jump variables (unique for player)
        Texture2D jumpTex;
        float jumpForce;
        float jumpTime;
        float maxJumpTime;
        bool isInJump;
        bool jumpCeiling;

        // Attack variables (unique for player)
        Texture2D attackTex;
        bool isInAttack;

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

        // Overrided texture managment
        virtual void updateTex() override;
        virtual void changeDirection() override;

        // Overrided collision methods
        virtual Rectangle getCollisionRec();
        virtual void checkTopCollision(Rectangle terrainCollision);

        // Jump method
        void jump(float deltaTime);
};