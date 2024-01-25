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

    const int WINDOW_DIM[2]{512, 380};
    InitWindow(WINDOW_DIM[0], WINDOW_DIM[1], "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int GRAV{1000};

    // NEBULA VARIABLES
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula

    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {WINDOW_DIM[0], WINDOW_DIM[1] - nebula.height / 8}, // Vector2 pos
        0, // int frame
        1.0 / 12.0, // float updateTime
        0.0 // float runningTime
    };

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {WINDOW_DIM[0] + 300, WINDOW_DIM[1] - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0 / 16.0, // float updateTime
        0.0 // float runningTime
    };

    AnimData nebulae[2]{nebData, neb2Data};
  

    // nebula X velocity (pixels/sec)
    int nebVel{-200};

    // SCARFY VARIABLES
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData{
        {0.0, 0.0, scarfy.width/6, scarfy.height}, 
        {WINDOW_DIM[0]/2 - scarfyData.rec.width/2, WINDOW_DIM[1] - scarfyData.rec.height}, 
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
        nebulae[0].runningTime += DT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime){
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7){
                nebulae[0].frame = 0;
            }
        }

        // update nebula 2 animation frame
        nebulae[1].runningTime += DT;
        if (nebulae[1].runningTime >= nebulae[1].updateTime){
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7){
                nebulae[1].frame = 0;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        // draw nebular 2
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        if(scarfyData.pos.y >= WINDOW_DIM[1] - scarfyData.rec.height){
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
        nebulae[0].pos.x += nebVel * DT;

        // update nebula 2 positon
        nebulae[1].pos.x += nebVel * DT;

        // update scarfy position
        scarfyData.pos.y += velocity * DT;

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}