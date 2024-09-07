#include <raylib.h>

void boundCheck(int x, int y, int direction[]);

const int screenWidth = 3000;
const int screenHeight = 2000;

int main(void){

    InitWindow(screenWidth, screenHeight, "example window");

    SetTargetFPS(60);

    int x = screenWidth/2;
    int y = screenHeight/2;

    int velocity = 20;
    int direction[2] = {0,0};

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_Q)){
            break;
        } else if (IsKeyDown(KEY_UP)){
            direction[0] = 0;
            direction[1] = -1;
        } else if (IsKeyDown(KEY_DOWN)){
            direction[0] = 0;
            direction[1] = 1;
        } else if (IsKeyDown(KEY_LEFT)){
            direction[0] = -1;
            direction[1] = 0;
        } else if (IsKeyDown(KEY_RIGHT)){
            direction[0] = 1;
            direction[1] = 0;
        }

        x+=direction[0]*velocity;
        y+=direction[1]*velocity;

        boundCheck(x, y, direction);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(x, y, 100, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void boundCheck(int x, int y, int direction[]){
    if (x>=screenWidth || x<=0){
        direction[0] *= -1;
    }
    if (y>=screenHeight || y<=0){
        direction[1] *= -1;
    }
}
