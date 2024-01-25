#include "raylib.h"

int main(){

    const int WINDOW_W{1920};
    const int WINDOW_H{1080};
    InitWindow(WINDOW_W, WINDOW_H, "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int GRAV{1000};

    // NEBULA VARIABLES
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebulaPos{WINDOW_W, WINDOW_H - nebula.height};

    // nebula animation variables
    int nebFrame{0};
    const float nebUpdateTime{1.0/12};
    float nebRunningTime{0};

    // nebula X velocity (pixels/sec)
    int nebVel{-200};

    // SCARFY VARIABLES
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0.0, 0.0, scarfy.width/6, scarfy.height};
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
        
        // update scarfy animation frame
        runningTime += DT;
        if (runningTime >= updateTime && !isInAir){
            runningTime = 0.0;
            // for drawing/updating which sprite to use on the sprite sheet
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5){
                frame = 0;
            }
        }

        // update nebula animation frame
        nebRunningTime += DT;
        if (nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;
            nebulaRec.x = nebFrame * nebulaRec.width;
            nebFrame++;
            if (nebFrame > 7){
                nebFrame = 0;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        // draw scarfy
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

        // update nebula position
        nebulaPos.x += nebVel * DT;

        // update scarfy position
        scarfyPos.y += velocity * DT;

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}