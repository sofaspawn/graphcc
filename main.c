#include <raylib.h>

const int screenWidth = 3000;
const int screenHeight = 2000;

const Color BGCOLOR = {46,46,46,100};
float SCALE = 2.0;
//const Color GRIDCOLOR = {255,255,255,100};

void renderAxes(){
    ClearBackground(BGCOLOR);

    const int XAXIS[2][2] = {{0, screenHeight/2}, {screenWidth, screenHeight/2}};
    const int YAXIS[2][2] = {{screenWidth/2, 0}, {screenWidth/2, screenHeight}};

    DrawLine(XAXIS[0][0], XAXIS[0][1], XAXIS[1][0], XAXIS[1][1], WHITE);
    DrawLine(YAXIS[0][0], YAXIS[0][1], YAXIS[1][0], YAXIS[1][1], WHITE);
}

void renderGrid(RenderTexture2D *target){
    DrawTextureRec(target->texture, (Rectangle){0, 0, (float)target->texture.width, (float)target->texture.height}, (Vector2){0,0}, BGCOLOR);
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
        DrawLine(i, 0, i, screenHeight, WHITE);
    }

    for(int i=0; i<screenHeight; i+=inc*SCALE){
        DrawLine(0, i, screenWidth, i, WHITE);
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
            //TODO: implement the render texture function to call it when changing scale
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
        renderGrid(&target);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
