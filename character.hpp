#include "raylib.h"

class character{
    protected:
        bool isMoving;
        bool isFalling;
        int frame;                  // Actual animation frame
        int maxFrames;              // Total number of animation frames
        float stopDelay;
        float stopCounter;
        float runningTime;
        float updateTime;
        float width;
        float height;
        float scale;
        float speed;
        float rightLeft;            // Rotation
        float animCorretion;
        float gravity;
        Rectangle characterRec;
        Texture2D actualTex;
        Texture2D idleTex;
        Texture2D runTex;
        Vector2 worldPos;
        Vector2 worldPosLast;
        Vector2 velocity;
    public:
        character();
        Vector2 getWorldPos();
        virtual Vector2 getScreenPos() = 0;
        void undoMovement();
        void updateTex();
        void moveCharacter(float deltaTime);
        void renderCharacter();
        virtual void tick(float deltaTime);
        virtual Rectangle getCollisionRec();
};