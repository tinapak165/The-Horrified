#include "raylib.h"

enum AppState {
    STATE_MENU,
    STATE_FUNCTION1,
    STATE_FUNCTION2
};

int main() {
    InitWindow(800, 600, "Menu & Function Selection App");
    SetTargetFPS(60);

    AppState currentState = STATE_MENU;

    Rectangle btnFunction1 = { 100, 100, 200, 50 };
    Rectangle btnFunction2 = { 100, 200, 200, 50 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == STATE_MENU) {
            DrawText("MAIN MENU", 300, 50, 40, BLACK);
            DrawRectangleRec(btnFunction1, LIGHTGRAY);
            DrawText("Function 1", btnFunction1.x + 20, btnFunction1.y + 15, 20, BLACK);

            DrawRectangleRec(btnFunction2, LIGHTGRAY);
            DrawText("Function 2", btnFunction2.x + 20, btnFunction2.y + 15, 20, BLACK);

            Vector2 mousePos = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mousePos, btnFunction1)) {
                    currentState = STATE_FUNCTION1;
                }
                else if (CheckCollisionPointRec(mousePos, btnFunction2)) {
                    currentState = STATE_FUNCTION2;
                }
            }
        }

        else if (currentState == STATE_FUNCTION1) {
            DrawText("Function 1 - Draw Circle", 200, 50, 30, BLACK);
            DrawCircle(400, 300, 50, RED);
            DrawText("Press SPACE to return to menu", 200, 550, 20, DARKGRAY);

            if (IsKeyPressed(KEY_SPACE)) {
                currentState = STATE_MENU;
            }
        }

        else if (currentState == STATE_FUNCTION2) {
            DrawText("Function 2 - Draw Rectangle", 200, 50, 30, BLACK);
            DrawRectangle(350, 250, 100, 100, BLUE);
            DrawText("Press SPACE to return to menu", 200, 550, 20, DARKGRAY);

            if (IsKeyPressed(KEY_SPACE)) {
                currentState = STATE_MENU;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
