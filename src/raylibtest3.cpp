#include "raylib.h"

void DrawRectangleCustom() {
    DrawRectangle(100, 100, 200, 150, RED);
}

void DrawCircleCustom() {
    DrawCircle(400, 300, 50, BLUE);
}

void DrawLineCustom() {
    DrawLine(50, 50, 400, 400, GREEN);
}

int main() {
    InitWindow(800, 600, "test chand draw");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleCustom();
        DrawCircleCustom();
        DrawLineCustom();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
