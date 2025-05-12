#include "raylib.h"

class terrain{
    private:
        Texture2D terrainTex;
        Vector2 worldPos;
        float scale;
    public:
        terrain(Vector2 pos, Texture2D tex);

        // Texture managment
        void renderTerrain();

        // Collision
        Rectangle getCollisionRec(Vector2 playerPos);
};