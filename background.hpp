#include "raylib.h"

class background{
    private:
        // Background variables
        float backgroundScale;
        Texture2D backgroundTex;
        Vector2 backgroundPos;

    public:
        background(float posX, float posY);

        // Display background
        void display();

        // Position update
        void updatePos(float posX, float posY);

        // Getters
        Vector2 getBackgroundPos();
        Rectangle getBackgroundRec();
};