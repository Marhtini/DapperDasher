#include "raylib.h"

int main(){

    const int WINDOW_W{1920};
    const int WINDOW_H{1080};
    InitWindow(WINDOW_W, WINDOW_H, "Dapper Dasher");

    // gravity
    const int GRAV{1}; // pixles per frame, per frame. (p/f)/f

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6; // six images in the sprite sheet
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    
    Vector2 scarfyPos;
    scarfyPos.x = WINDOW_W/2 - scarfyRec.width/2;
    scarfyPos.y = WINDOW_H - scarfyRec.height;

    // jump height
    const int JUMP_VELOCITY{-20};

    // currently in the air?
    bool isInAir{false};

    int velocity{0};

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        if(scarfyPos.y >= WINDOW_H - scarfyRec.height){
            // keep your feet on the ground!
            velocity = 0;
            isInAir = false;
        }
        else{
            // apply gravity
            velocity += GRAV;
        }

        // check if jumping
        if((IsKeyPressed(KEY_SPACE) == true) && (!isInAir)){
            velocity += JUMP_VELOCITY;
            isInAir = true;
        }

        scarfyPos.y += velocity;

        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();

}