#include "raylib.h"

class character{
    protected:
        // Flags
        bool isMoving;
        bool isOnGround;

        // Animation variables
        int frame;                  
        int maxFrames;
        float animCorretion;     
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
    public:
        character();
        virtual void tick(float deltaTime);

        // Movement methods
        void moveCharacter(float deltaTime);
        void applyGravity(float deltaTime);
        void undoMovement();

        // Texture managment
        void updateTex();
        void renderCharacter();

        // Return charater world position
        Vector2 getWorldPos();

        // Collision
        Rectangle getCollisionRec();
        void snapToGround(Rectangle ground);
        void checkTopCollision(Rectangle terrainCollision);
};