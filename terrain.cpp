#include "terrain.hpp"
#include "raymath.h"

terrain::terrain(Vector2 pos, Texture2D tex):
    terrainTex(tex),
    worldPos(pos)
{
    scale = {4.f};
}

void terrain::renderTerrain(){
    DrawTextureEx(terrainTex, worldPos, 0.f, scale * 10, WHITE);
}

Rectangle terrain::getCollisionRec(){
    // Vertical and horizontal paddings
    float paddingX = terrainTex.width / 2;
    float paddingY = terrainTex.height / 2;

    // Return collision rectangle
    return Rectangle{
        worldPos.x + paddingX / 2,
        worldPos.y + paddingY / 2,
        terrainTex.width * scale * 10 - paddingX,
        terrainTex.height * scale - paddingY
    };
}