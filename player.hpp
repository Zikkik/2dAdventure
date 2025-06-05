#ifndef PLAYER_HPP
#define PLAYER_HPP
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

        // Window size
        float windowWidth;
        float windowHeight;

    public:
        player(float winWidth, float winHeight);

        // Overrided tick from the character class
        void tick(float deltaTime) override;

        // Overrided texture managment
        void updateTex() override;
        void changeDirection() override;
        void updateFrame(float deltaTime) override;

        // Overrided collision methods
        Rectangle* getCollisionRec() override;
        bool checkTopCollision(Rectangle terrainCollision) override;

        // Jump method
        void jump(float deltaTime);

        // Attack method
        void attack(character *enemy);

        // Getters
        bool getAttackBool();
};

#endif