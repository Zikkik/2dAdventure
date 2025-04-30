#include "terrain.hpp"
#include "raymath.h"

terrain::terrain(Vector2 pos, Texture2D tex):
    terrainTex(tex),
    worldPos(pos),
    scale(4.f)
{
}

void terrain::renderTerrain(){
    DrawTextureEx(terrainTex, worldPos, 0.f, scale, WHITE);
}

Rectangle terrain::getCollisionRec(Vector2 playerPos){
    float paddingX = terrainTex.width / 2;
    float paddingY = terrainTex.width / 2;
    return Rectangle{
        worldPos.x + paddingX / 2,
        worldPos.y + paddingY / 2,
        terrainTex.width * scale - paddingX,
        terrainTex.height * scale - paddingY
    };
}