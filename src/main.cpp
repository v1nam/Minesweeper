#include "raylib.h"

int main()
{
    const int screenWidth = 436;
    const int screenHeight = 436;

    const int rows = 8;
    const int columns = 8;
    const int cellSize = 50;

    const int pad = 4;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        int mouseHoverX = GetMouseX();
        int mouseHoverY = GetMouseY();

        for (int x{0}; x < columns; x++)
        {
            for (int y{0}; y < rows; y++)
            {
                Rectangle cell = Rectangle{(float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                                           (float)cellSize, (float)cellSize};
                Color col = LIGHTGRAY;
                if (cell.x <= mouseHoverX && cell.y <= mouseHoverY && mouseHoverX <= cell.x + cell.width &&
                    mouseHoverY <= cell.y + cell.height)
                    col = RAYWHITE;
                DrawRectangleRounded(cell, 0.1, 0, col);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
