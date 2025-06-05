#include <cmath>
#include "raylib.h"
#include "character.hpp"


class boar : public character{
    private:
        // Additional flags
        bool isInCharge;
        bool isOnPatrol;
        bool chargeTargetReached;

        // Additional Textures
        Texture2D walkTex;
        Texture2D vanishTex;

        // Movement variables
        float movementRangeLeft;
        float movementRangeRight;
        float direction;

    public:
        boar(float posX, float posY);

        // Overrided tick from the character class
        void tick(float deltaTime) override;

        // Overrided texture managment
        void updateTex() override;

        // Boar mechanics
        void boarCharge();
        void boarPatrol(float pointA, float pointB);
        void chargeCheck(Rectangle *player);

};