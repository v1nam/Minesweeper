#include <vector>

#include "raylib.h"
#include "minesweeper.hpp"
#include "colors.hpp"

int main()
{
    const int screenWidth = 436;
    const int screenHeight = 436;

    Minesweeper mnsp = Minesweeper();

    const int pad = 4;
    const int cellSize = (screenWidth - pad * (mnsp.columns + 1)) / mnsp.columns;

    const std::vector<Color> colArr = {Color{96, 106, 126, 255}, green, yellow, orange, red, teal, aqua, lblue, blue};
    char const* numbers[] = {"1", "2", "3", "4", "5", "6", "7", "8"}; 

    bool started = false;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(bgCol);

        int mouseHoverX = GetMouseX();
        int mouseHoverY = GetMouseY();

        for (int x{0}; x < mnsp.columns; x++)
        {
            for (int y{0}; y < mnsp.rows; y++)
            {
                Rectangle cellPos = Rectangle{(float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                                           (float)cellSize, (float)cellSize};
                Cell cell = mnsp.grid[x][y];
                Color cellCol = cell.color;

                // checking if cursor is hovering on a cell
                if (cellPos.x <= mouseHoverX && cellPos.y <= mouseHoverY && mouseHoverX <= cellPos.x + cellPos.width &&
                    mouseHoverY <= cellPos.y + cellPos.height && !cell.revealed)
                {
                    cellCol = hlt;
                    if (IsMouseButtonPressed(0))
                    {
                        if (!started)
                        {
                            mnsp.initGame(x, y);
                            started = true;
                        } else mnsp.reveal(x, y);
                    }
                }
                if (cell.revealed && cell.value >= 0)
                    cellCol = colArr[cell.value];

                DrawRectangleRounded(cellPos, 0.1, 0, cellCol);
                if (cell.value == -1)
                    DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
                else if (cell.value > 0)
                {
                    const char* text = numbers[cell.value-1];
                    float size = cellSize / 2.0;
                    DrawText(text, (cellPos.x + cellSize / 2) - (MeasureText(text, size) / 2), cellPos.y + cellSize / 4, size, bgCol);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
