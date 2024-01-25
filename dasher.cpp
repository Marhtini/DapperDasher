#include "raylib.h"

struct AnimData{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;  
};

AnimData nebData;
AnimData neb2Data;
AnimData scarfyData;

int main(){

    const int WINDOW_W{1920};
    const int WINDOW_H{1080};
    InitWindow(WINDOW_W, WINDOW_H, "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int GRAV{1000};

    // NEBULA VARIABLES
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula

    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {WINDOW_W, WINDOW_H - nebula.height / 8}, // Vector2 pos
        0, // int frame
        1.0 / 12.0, // float updateTime
        0.0 // float runningTime
    };

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {WINDOW_W + 300, WINDOW_H - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0 / 16.0, // float updateTime
        0.0 // float runningTime
    };

    // nebula X velocity (pixels/sec)
    int nebVel{-200};

    // SCARFY VARIABLES
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData{
        {0.0, 0.0, scarfy.width/6, scarfy.height}, 
        {WINDOW_W/2 - scarfyData.rec.width/2, WINDOW_H - scarfyData.rec.height}, 
        0, 
        1.0 / 12.0, 
        0.0
    };

    // jump velocity (pixels/second)
    const int JUMP_VELOCITY{-600};

    // currently in the air?
    bool isInAir{false};
    int velocity{0};

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        
        // delta time (time since last frame)
        const float DT{GetFrameTime()};
        
        // update scarfy animation frame
        scarfyData.runningTime += DT;
        if (scarfyData.runningTime >= scarfyData.updateTime && !isInAir){
            scarfyData.runningTime = 0.0;

            // for drawing/updating which sprite to use on the sprite sheet
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;
            if (scarfyData.frame > 5){
                scarfyData.frame = 0;
            }
        }

        // update nebula animation frame
        nebData.runningTime += DT;
        if (nebData.runningTime >= nebData.updateTime){
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7){
                nebData.frame = 0;
            }
        }

        // update nebula 2 animation frame
        neb2Data.runningTime += DT;
        if (neb2Data.runningTime >= neb2Data.updateTime){
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7){
                neb2Data.frame = 0;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        // draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // draw nebular 2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        if(scarfyData.pos.y >= WINDOW_H - scarfyData.rec.height){
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
        nebData.pos.x += nebVel * DT;

        // update nebula 2 positon
        neb2Data.pos.x += nebVel * DT;

        // update scarfy position
        scarfyData.pos.y += velocity * DT;

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}