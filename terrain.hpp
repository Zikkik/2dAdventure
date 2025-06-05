#include "raylib.h"

class terrain{
    private:
        Texture2D terrainTex;
        Vector2 worldPos;
        float scale;
    public:
        terrain();
        terrain(Vector2 pos, Texture2D tex, float scale);

        // Texture managment
        void renderTerrain();

        // Collision
        Rectangle getCollisionRec();
};