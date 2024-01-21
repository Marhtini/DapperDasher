#include "raylib.h"

int main(){

    int w{1920};
    int h{1080};
    InitWindow(w, h, "Dapper Dasher");

    SetTargetFPS(60);

    while(WindowShouldClose() != true){
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

}