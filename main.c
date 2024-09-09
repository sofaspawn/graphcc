#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define FPS 60

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

//FIXME: fix the function to render graphs
void renderFunction(RenderTexture2D *func){
    Vector2 points[screenWidth];
    for(int i=0; i<screenWidth; i++){
        int x = (i + (float)screenWidth)*SCALE;
        int y = 200*sin(x)+(double)screenHeight/2;
        Vector2 point = {x, y};
        points[i] = point;
    }
    BeginTextureMode(*func);
    DrawLineStrip(points, sizeof(points)/sizeof(points[0]), RED);
    //DrawLine(screenWidth/2, screenHeight/2, 1000, screenHeight, GREEN);
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

void keepMarioInBounds(Texture2D img, int x, int y, int *x_dir, int *y_dir, int velocity, Sound boundTouch){

    if(x<=0 || x+img.width>=screenWidth) {
        PlaySound(boundTouch);
        *x_dir*=-1;
    }
    if(y<=0 || y+img.height>=screenHeight) {
        PlaySound(boundTouch);
        *y_dir*=-1;
    }

    //to keep mario moving in the same direction
    /* 
    if(*x<0){*x = screenWidth+*x;}
    if(*x>=screenWidth){*x = screenWidth-*x;}
    if(*y<0){*y = screenHeight+*y;}
    if(*y>=screenHeight){*y = screenHeight-*y;}
    */
}

void move(int *x, int *y, int direction[], int *velocity){
    *x += direction[0] * *velocity;
    *y += direction[1] * *velocity;
}

int main(void){

    InitWindow(screenWidth, screenHeight, "GraphCC");

    SetTargetFPS(FPS);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D func = LoadRenderTexture(screenWidth, screenHeight);
    Texture2D img = LoadTexture("./assets/mario.png");
    float aspect_ratio = (float)img.height/(float)img.width;
    img.width = 100;
    img.height = aspect_ratio*img.width;

    srand(time(NULL));
    int x = rand() % screenWidth;
    int y = rand() % screenHeight;
    int direction[] = {rand() % 5, rand() % 5};
    int velocity = 8;
    //int y = screenHeight/2-img.height/2;

    gridTexture(&target);
    renderFunction(&func);

    InitAudioDevice();
    Sound spawn_sfx = LoadSound("./mario_sfx/mario_spawn.wav");
    Sound boundTouch = LoadSound("./mario_sfx/bound-touch.wav");

    int i = 0;

    while(!WindowShouldClose()){

        if(i%600==0 || i!=0){
            PlaySound(spawn_sfx);
        }

        move(&x, &y, direction, &velocity);
        keepMarioInBounds(img, x, y, &direction[0], &direction[1], velocity, boundTouch);

        if(IsKeyDown(KEY_Q)){
            break;
        }
        if(IsKeyDown(KEY_EQUAL)){
            SCALE+=0.5;
            gridTexture(&target);
            renderFunction(&target);
        }
        if(IsKeyDown(KEY_MINUS)){
            if(SCALE<1.0){
                continue;
            }
            SCALE-=0.5;
            gridTexture(&target);
            renderFunction(&target);
        }

        BeginDrawing();
        //DrawText((char*)FPS , 0, 0, 50, RED);
        renderAxes();
        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)target.texture.height}, (Vector2){0,0}, GRIDCOLOR);
        DrawTextureRec(func.texture, (Rectangle){0, 0, (float)func.texture.width, (float)func.texture.height}, (Vector2){0,0}, GREEN);
        DrawTexture(img, x, y, WHITE);
        EndDrawing();

        i+=1;
    }

    UnloadTexture(img);
    UnloadRenderTexture(target);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
