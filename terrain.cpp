#include "terrain.hpp"
#include "raymath.h"

terrain::terrain(){}

terrain::terrain(Vector2 pos, Texture2D tex, float scale):
    terrainTex(tex),
    worldPos(pos),
    scale(scale)
{
    scale = {4.f};
}

void terrain::renderTerrain(){
    DrawTextureEx(terrainTex, worldPos, 0.f, scale, WHITE);
}

Rectangle terrain::getCollisionRec(){
    // Vertical and horizontal paddings
    float paddingX = 20.f;
    float paddingY = 10.f;

    // Return collision rectangle
    return Rectangle{
        worldPos.x + paddingX,
        worldPos.y + paddingY,
        terrainTex.width * scale - paddingX * 2,
        terrainTex.height * scale
    };
}