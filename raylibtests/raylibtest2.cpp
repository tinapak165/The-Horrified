 #include "raylib.h"
    #include <iostream>
    
    using namespace std ;
    
    bool ColorEquals(Color c1, Color c2) {
        return (c1.r == c2.r) &&
               (c1.g == c2.g) &&
               (c1.b == c2.b) &&
               (c1.a == c2.a);
    }
    
    void draw() {
    
        while(!WindowShouldClose()) {
    
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                return ;
            }
    
            BeginDrawing() ;
    
            DrawText("heil" , 400 , 300 , 50 , RED) ;
            DrawText("if you want to ba press mouse left button" , 10 , 500 , 30 , BLUE) ;
    
    
            EndDrawing();
        }
    }
    
    
    // int main() {
    //     // پنجره
    //     InitWindow(800, 600, "Command Click App");
    
    //     Color background = RAYWHITE;
    
    //     // دکمه‌ها
    //     Rectangle redButton   = { 100, 100, 150, 50 };
    //     Rectangle greenButton = { 100, 200, 150, 50 };
    //     Rectangle blueButton  = { 100, 300, 150, 50 };
    
    //     SetTargetFPS(60);
    
    
    //     while (!WindowShouldClose()) {
    //         // چک کردن کلیک موس
    //         Vector2 mousePoint = GetMousePosition();
    
    //         if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //             if (CheckCollisionPointRec(mousePoint, redButton)) {
    //                 background = RED;
    //             }
    //             else if (CheckCollisionPointRec(mousePoint, greenButton)) {
    //                 background = GREEN;
    //             }
    //             else if (CheckCollisionPointRec(mousePoint, blueButton)) {
    //                 background = BLUE;
    //             }
    //         }
    
    //         if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    //             draw() ;
    //         }
    
    //         // رسم
    //         BeginDrawing();
    //         ClearBackground(background);
    
    //         // دکمه‌ها
    //         DrawRectangleRec(redButton, (ColorEquals(background , RED)) ? DARKGRAY : RED);
    //         DrawText("RED", redButton.x + 40, redButton.y + 15, 20, WHITE);
    
    //         DrawRectangleRec(greenButton, (ColorEquals(background , GREEN)) ? DARKGREEN : GREEN);
    //         DrawText("GREEN", greenButton.x + 30, greenButton.y + 15, 20, WHITE);
    
    //         DrawRectangleRec(blueButton, (ColorEquals(background , BLUE)) ? DARKBLUE : BLUE);
    //         DrawText("BLUE", blueButton.x + 40, blueButton.y + 15, 20, WHITE);
    
    //         DrawText("Click a button to change background color!", 20, 20, 20, BLACK);
    
    //         EndDrawing();
    //     }
    
    //     CloseWindow();
    //     return 0;
    // }
    