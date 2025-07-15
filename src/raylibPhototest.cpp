#include "raylib.h"
#include <iostream>

using namespace std ;

void phase1(Texture2D img) {
    while(!WindowShouldClose()) {
        Vector2 mose = GetMousePosition() ;
        Rectangle source = { 0, 0, img.width, img.height };
        Rectangle dest = { 0, 0, 1000 , 1000 };  // x, y, width, height
        Vector2 origin = { 0, 0 };
        BeginDrawing() ;
        DrawTexturePro(img , source , dest , origin , 0 ,  WHITE) ;
        ClearBackground(WHITE) ;
        DrawCircle(mose.x , mose.y , 20 , RED) ;
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return ;
        }
        if(IsKeyPressed(KEY_ESCAPE)) {
            return ;
        }
        EndDrawing() ;
    }
}

void phase2(Texture2D img) {
    while(!WindowShouldClose()) {
        Vector2 mose = GetMousePosition() ;
        Rectangle source = { 0, 0, img.width, img.height };
        Rectangle dest = { 250, 100, 500 , 700 };  // x, y, width, height
        Vector2 origin = { 0, 0 };
        BeginDrawing() ;
        DrawTexturePro(img , source , dest , origin , 0 ,  WHITE) ;
        ClearBackground(WHITE) ;
        DrawCircle(mose.x , mose.y , 20 , RED) ;
        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            return ;
        }
        if(IsKeyPressed(KEY_ESCAPE)) {
            return ;
        }
        EndDrawing() ;
    }
}



int main() {
    InitWindow(1000 , 1000 , "test chand draw");

    Texture2D img = LoadTexture("map.png") ;
    Texture2D img1 = LoadTexture("Scientist.png") ;

    while(!IsKeyPressed(KEY_ESCAPE)) {
        phase1(img) ;
        
        phase2(img1) ;
    }

    // cout<< img.height << "     " << img.width << '\n' ;

    CloseWindow();
    return 0;

    UnloadTexture(img) ;
    UnloadTexture(img1) ;
}
