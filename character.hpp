#include "raylib.h"

class character{
    protected:
        bool isMoving;
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
        Rectangle characterRec;
        Texture2D actualTex;
        Texture2D idleTex;
        Texture2D runTex;
        Vector2 worldPos;
        Vector2 velocity;
    public:
        character();
        virtual void tick(float deltaTime);
};