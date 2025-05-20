#include "raylib.h"

class character{
    protected:
        // Flags
        bool isMoving;
        bool isOnGround;
        bool jumpCeiling;
        bool isInJump;

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
        Texture2D fallTex;

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
        void updateFrame(float deltaTime);
        void changeDirection();
        void animChangeDelay(float deltaTime);

        // Collision
        virtual Rectangle getCollisionRec();
        void snapToGround(Rectangle ground);
        void checkTopCollision(Rectangle terrainCollision);
    
        // Return charater world position
        Vector2 getWorldPos();
};