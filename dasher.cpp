#include "raylib.h"

int main(){

    const int WINDOW_W{1920};
    const int WINDOW_H{1080};
    InitWindow(WINDOW_W, WINDOW_H, "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int GRAV{1000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6; // six images in the sprite sheet
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    
    Vector2 scarfyPos;
    scarfyPos.x = WINDOW_W/2 - scarfyRec.width/2;
    scarfyPos.y = WINDOW_H - scarfyRec.height;

    // jump velocity (pixels/second)
    const int JUMP_VELOCITY{-600};

    // currently in the air?
    bool isInAir{false};

    int velocity{0};

    // for tracking current animation frame
    int frame{0};
    // update the scarfy animation 12 times per second.
    const float updateTime{1.0 / 12.0};
    // time since last updated animation
    float runningTime{0};

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        
        // delta time (time since last frame)
        const float DT{GetFrameTime()};
        
        runningTime += DT;
        if (runningTime >= updateTime){
            runningTime = 0.0;
            // for drawing/updating which sprite to use on the sprite sheet
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5){
                frame = 0;
            }
        }

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
            velocity += GRAV * DT;
        }

        // check if jumping
        if((IsKeyPressed(KEY_SPACE) == true) && (!isInAir)){
            velocity += JUMP_VELOCITY;
            isInAir = true;
        }

        scarfyPos.y += velocity * DT;

        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();

}