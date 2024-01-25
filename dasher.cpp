#include "raylib.h"

struct AnimData{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;  
};

AnimData scarfyData;

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame){
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime){
        
        data.runningTime = 0.0;
        
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame){
            data.frame = 0;
        }
    }

    return data;
}

int main(){

    const int WINDOW_DIM[2]{512, 380};
    InitWindow(WINDOW_DIM[0], WINDOW_DIM[1], "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int GRAV{1000};

    // NEBULA VARIABLES
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    const int SIZE_OF_NEBULAE{10};
    AnimData nebulae[SIZE_OF_NEBULAE]{};

    for (int i = 0; i < SIZE_OF_NEBULAE; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = WINDOW_DIM[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].pos.x = WINDOW_DIM[0] + (i * 300);
    }

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

        if (!isInAir){
            scarfyData = updateAnimData(scarfyData, DT, 5);
        }

        for (int i = 0; i < SIZE_OF_NEBULAE; i++){
            nebulae[i] = updateAnimData(nebulae[i], DT, 7);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        // draw nebulae
        for (int i = 0; i < SIZE_OF_NEBULAE; i++){
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        if(isOnGround(scarfyData,WINDOW_DIM[1])){
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

        for (int i = 0; i < SIZE_OF_NEBULAE; i++){
            // update nebula position
            nebulae[i].pos.x += nebVel * DT;
        }

        // update scarfy position
        scarfyData.pos.y += velocity * DT;

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}