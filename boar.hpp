#include "raylib.h"
#include "character.hpp"

class boar : public character{
    private:
        // Additional Textures
        Texture2D walkTex;
        Texture2D vanishTex;
    public:
        boar(float posX, float posY);

        // Overrided collision methods
        Rectangle getCollisionRec() override;
};