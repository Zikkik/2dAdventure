#include "raylib.h"
#include "character.hpp"

class player : public character{
    public:
        player(float winWidth, float winHeight);
        virtual void tick(float deltaTime) override;
};