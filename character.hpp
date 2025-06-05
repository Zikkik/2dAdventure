#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "raylib.h"
#include "raymath.h"

class character{
    protected:
        // Flags
        bool isMoving;
        bool isOnGround;
        bool recentlyDamaged;
        bool isAlive;

        // Animation variables
        int frame;                  
        int maxFrames;
        float animCorrection;     
        float rightLeft;   
        float runningTime; 
        float stopDelay;
        float stopCounter;
        float updateTime;

        // Texture variables
        float width;
        float height;
        float scale;
        Texture2D actualTex;
        Texture2D idleTex;
        Texture2D runTex;

        // Movement variables
        float speed;
        float gravity;
        Vector2 worldPos;
        Vector2 worldPosLast;
        Vector2 velocity;

        // Collision variables
        float paddingX;
        float paddingY;
        Rectangle characterRec;

        // Gameplay variables
        int health;
        int damage;
        float damageCooldown;

    public:
        character();
        virtual void tick(float deltaTime);

        // Movement methods
        void applyGravity(float deltaTime);
        void moveCharacter(float deltaTime);
        void undoMovement();

        // Texture managment
        virtual void updateTex();
        void renderCharacter();
        virtual void updateFrame(float deltaTime);
        virtual void changeDirection();
        void animChangeDelay(float deltaTime);

        // Collision
        virtual Rectangle* getCollisionRec();
        void snapToGround(Rectangle ground);
        virtual void checkTopCollision(Rectangle terrainCollision);
    
        // Getters
        Vector2 getWorldPos();
        Vector2 getSize();
        float getDirection();

        // Gameplay
        void takeDamage(int amount);
        void damageTimer(float deltaTime);
        void aliveCheck();
};

#endif