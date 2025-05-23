#include "character.hpp"

character::character(){
    // Flags
    isMoving = {false};
    isOnGround = {false};

    // Animation variables
    frame = {};
    maxFrames = {};
    stopDelay = {0.1f};
    stopCounter = {0.f};
    runningTime = {0.f};
    updateTime = {1.f / 8.f};
    animCorrection = {0.f};

    // Collision variables
    paddingX = {65.f};
    paddingY = {50.f};

    // Gravity
    gravity = {200.0f};
}

// Character tick
void character::tick(float deltaTime){

    // Testing
    Rectangle testCol = getCollisionRec();
    if(actualTex.id == idleTex.id)
        DrawRectangleLines(testCol.x, testCol.y, testCol.width, testCol.height, RED);
    if(actualTex.id == runTex.id)
        DrawRectangleLines(testCol.x, testCol.y, testCol.width, testCol.height, PURPLE);

    moveCharacter(deltaTime);

    if(!isOnGround)
        applyGravity(deltaTime);
    else
        velocity = {};

    renderCharacter();
}

// Update the texture based on the movement animation
void character::updateTex(){
    if (isMoving){
        actualTex = runTex;
        maxFrames = 8;
        height = runTex.height;
    } else {
        actualTex = idleTex;
        maxFrames = 4;
        height = idleTex.height;
    }

    width = actualTex.width / maxFrames;
}

// Display character sprite in the window
void character::renderCharacter(){
    Rectangle source{width * frame, 0.f, width * rightLeft, height};
    Rectangle dest{worldPos.x - animCorrection, worldPos.y, scale * width, scale * height};
    DrawTexturePro(actualTex, source, dest, Vector2{}, 0.f, WHITE);
}

// Update actual frame in character's sprite
void character::updateFrame(float deltaTime){
    // Time between animation frames
    runningTime += deltaTime;
    if(runningTime >= updateTime){
        frame++;
        runningTime = 0;
        if(frame >= maxFrames) frame = 0;
    }
}

// Change texture direction
void character::changeDirection(){
    if(isOnGround){
        if(velocity.x < 0.f) {
        // On ground left
            rightLeft = -1.f;
            animCorrection = 0.f;
        } else if(velocity.x > 0.f) {
        // On ground right
            rightLeft = 1.f;
            animCorrection = width / 2;
        }
    } 
}

// Delay for smoother texture changes
void character::animChangeDelay(float deltaTime){
    stopCounter += deltaTime;
    if(stopCounter >= stopDelay){
        isMoving = false;
        animCorrection = 0.f;
    }
}

// Use gravity to apply character's falling
void character::applyGravity(float deltaTime){
    velocity.y += gravity;
    worldPos.y += velocity.y * deltaTime;
}

// All character's movements
void character::moveCharacter(float deltaTime){
    worldPosLast = worldPos;

    updateFrame(deltaTime);

    // Check character's velocity
    if (Vector2Length(velocity) != 0.0){

        Vector2 scaledVelocity;

        // Vertical movement depends on ground state
        if(isOnGround)
            scaledVelocity = {Vector2Normalize(velocity).x * speed * deltaTime, velocity.y * deltaTime};
        else
            scaledVelocity = {velocity.x * speed / 2 * deltaTime, velocity.y * deltaTime};

        // Update world position
        worldPos = Vector2Add(worldPos, scaledVelocity);

        // Update character's variables
        stopCounter = 0.f;
        if(velocity.x != 0) isMoving = true;
    } else 
        animChangeDelay(deltaTime);

    changeDirection();

    updateTex();

    // Reset velocity
    velocity = {};
}

// Change position to previous character's position
void character::undoMovement(){ worldPos = worldPosLast; }

Rectangle character::getCollisionRec(){
    // Return the rectangle based on character's actual animation
    if(actualTex.id == idleTex.id)
        characterRec = {
            worldPos.x + paddingX,
            worldPos.y + paddingY,
            width * scale - paddingX * 2,
            height * scale - paddingY * 2
        };

    if(actualTex.id == runTex.id)
        characterRec = {
            worldPos.x + paddingX - width / 4,
            worldPos.y + paddingY,
            width * scale - paddingX * 2,
            height * scale - paddingY * 2
        };
    
    return characterRec;
}

// If the character touches the ground, they are snapped to their top edge
void character::snapToGround(Rectangle ground){
    if(isOnGround){
        worldPos.y = ground.y - height * scale + paddingY + 3;
        worldPosLast.y = ground.y - height * scale + paddingY + 3;
    }
}

// Check character's collision with terrain from the top
void character::checkTopCollision(Rectangle terrainCollision){

    // Auxiliary variables to calculate character down edge and top edge of terrain
    float characterBottom = worldPos.y + getCollisionRec().height  + paddingY;
    float terrainTop = terrainCollision.y + 8;

    // Check collision with terrain and top edge
    if(CheckCollisionRecs(terrainCollision, getCollisionRec()) && 
        characterBottom <= terrainTop){
            isOnGround = true;
            snapToGround(terrainCollision);
        } else 
            isOnGround = false;
}

// Return charater world position
Vector2 character::getWorldPos(){ return worldPos; }

// Return character size
Vector2 character::getSize() { return Vector2{width, height}; }

// Return character direction
float character::getDirection() { return rightLeft; }