#include <raylib.h>

const int screenWidth = 3000;
const int screenHeight = 2000;

const int INC = 10;

const Color BGCOLOR = {46,46,46,100};
const Color GRIDCOLOR = {255,255,255,150};
//const Color BGCOLOR = {0,0,0,0};

float SCALE = 4.0;

void renderAxes(){
    ClearBackground(BGCOLOR);

    const int XAXIS[2][2] = {{0, screenHeight/2}, {screenWidth, screenHeight/2}};
    const int YAXIS[2][2] = {{screenWidth/2, 0}, {screenWidth/2, screenHeight}};

    DrawLine(XAXIS[0][0], XAXIS[0][1], XAXIS[1][0], XAXIS[1][1], WHITE);
    DrawLine(YAXIS[0][0], YAXIS[0][1], YAXIS[1][0], YAXIS[1][1], WHITE);
}

void renderFunction(RenderTexture2D *func){
    Vector2 points[][2] = {{1,2}, {22,200}, {400, 500}, {1000, 2000}};
    BeginTextureMode(*func);
    //DrawLineStrip(*points, sizeof(points)/sizeof(points[0]), GREEN);
    DrawLine(screenWidth/2, screenHeight/2, 1000, screenHeight, GREEN);
    EndTextureMode();
}

void gridTexture(RenderTexture2D *target){
    BeginTextureMode(*target);
    ClearBackground(BGCOLOR);

    for(int i=screenWidth/2; i<screenWidth; i+=INC*SCALE){
        DrawRectangle(i, 0, 1, screenHeight, GRIDCOLOR);
    }

    for(int i=screenWidth/2; i>0; i-=INC*SCALE){
        DrawRectangle(i-1, 0, 1, screenHeight, GRIDCOLOR);
    }

    for(int i=screenHeight/2; i<screenHeight; i+=INC*SCALE){
        DrawRectangle(0, i, screenWidth, 1, GRIDCOLOR);
    }

    for(int i=screenHeight/2; i>0; i-=INC*SCALE){
        DrawRectangle(0, i-1, screenWidth, 1, GRIDCOLOR);
    }

    EndTextureMode();
}

int main(void){

    InitWindow(screenWidth, screenHeight, "GraphCC");

    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D func = LoadRenderTexture(screenWidth, screenHeight);
    Texture2D img = LoadTexture("./mario.png");
    float aspect_ratio = (float)img.height/(float)img.width;
    img.width = 200;
    img.height = aspect_ratio*img.width;

    int x = screenWidth/2-img.width/2;
    int y = screenHeight/2-img.height/2;

    gridTexture(&target);
    renderFunction(&func);

    InitAudioDevice();
    Sound sfx = LoadSound("./mario.wav");
    PlaySound(sfx);


    while(!WindowShouldClose()){

        if(IsKeyDown(KEY_S)){
            y+=50;
        }
        if(IsKeyDown(KEY_W)){
            y-=50;
        }
        if(IsKeyDown(KEY_D)){
            x+=50;
        }
        if(IsKeyDown(KEY_A)){
            x-=50;
        }
        if(IsKeyPressed(KEY_Q)){
            break;
        }
        if(IsKeyPressed(KEY_EQUAL)){
            SCALE+=0.5;
            gridTexture(&target);
            renderFunction(&target);
        }
        if(IsKeyPressed(KEY_MINUS)){
            if(SCALE<1.0){
                continue;
            }
            SCALE-=0.5;
            gridTexture(&target);
            renderFunction(&target);
        }

        BeginDrawing();
        renderAxes();
        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)target.texture.height}, (Vector2){0,0}, GRIDCOLOR);
        DrawTextureRec(func.texture, (Rectangle){0, 0, (float)func.texture.width, (float)func.texture.height}, (Vector2){0,0}, GREEN);
        DrawTexture(img, x, y,WHITE);
        EndDrawing();
    }

    UnloadTexture(img);
    UnloadRenderTexture(target);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
