#include <raylib.h>

const int screenWidth = 3000;
const int screenHeight = 2000;

const Color BGCOLOR = {46,46,46,100};
//const Color BGCOLOR = {0,0,0,0};
float SCALE = 2.0;
const Color GRIDCOLOR = {255,255,255,150};

void renderAxes(){
    ClearBackground(BGCOLOR);

    const int XAXIS[2][2] = {{0, screenHeight/2}, {screenWidth, screenHeight/2}};
    const int YAXIS[2][2] = {{screenWidth/2, 0}, {screenWidth/2, screenHeight}};

    DrawLine(XAXIS[0][0], XAXIS[0][1], XAXIS[1][0], XAXIS[1][1], WHITE);
    DrawLine(YAXIS[0][0], YAXIS[0][1], YAXIS[1][0], YAXIS[1][1], WHITE);
}

void computeFunction(){
}

void renderFunction(RenderTexture2D *target){
}

void gridTexture(RenderTexture2D *target){
    BeginTextureMode(*target);
    ClearBackground(BGCOLOR);

    int inc = 10;

    for(int i=0; i<screenWidth; i+=inc*SCALE){
        DrawRectangle(i, 0, 1, screenHeight, GRIDCOLOR);
    }

    for(int i=0; i<screenHeight; i+=inc*SCALE){
        DrawRectangle(0, i, screenWidth, 1, GRIDCOLOR);
    }

    EndTextureMode();
}

int main(void){

    InitWindow(screenWidth, screenHeight, "draw graphs and shit");

    SetTargetFPS(90);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    gridTexture(&target);

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_Q)){
            break;
        }
        if(IsKeyPressed(KEY_EQUAL)){
            SCALE+=0.5;
            gridTexture(&target);
        }
        if(IsKeyPressed(KEY_MINUS)){
            if(SCALE>0){
                SCALE-=0.5;
                gridTexture(&target);
            }
        }

        BeginDrawing();
        renderAxes();
        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)target.texture.height}, (Vector2){0,0}, GRIDCOLOR);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
