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
    float paddingX = 70.f;
    float paddingY = 10.f;
    return Rectangle{
        worldPos.x,
        worldPos.y,
        terrainTex.width * scale - paddingX,
        terrainTex.height * scale - paddingY
    };
}