#include <vector>

#include "raylib.h"

void initGame(std::vector<std::vector<int>> &grid, int x, int y, int mineCount, int rows, int columns)
{
    for (int i{0}; i < mineCount;)
    {
        int mineX = GetRandomValue(0, columns - 1);
        int mineY = GetRandomValue(0, rows - 1);

        if (mineX != x || mineY != y)
        {
            i++;
            grid[mineX][mineY] = -1; // -1 means this cell is a mine
        }
    }
}

int main()
{
    const int screenWidth = 436;
    const int screenHeight = 436;

    const int rows = 8;
    const int columns = 8;
    const int pad = 4;

    const int cellSize = (screenWidth - pad * (columns + 1)) / columns;
    const int mineCount = 10;

    bool started = false;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    std::vector<std::vector<int>> grid(columns);
    for (int j{0}; j < rows; j++)
        grid[j] = std::vector<int>(rows);

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

                // checking if cursor is hovering on a cell
                if (cell.x <= mouseHoverX && cell.y <= mouseHoverY && mouseHoverX <= cell.x + cell.width &&
                    mouseHoverY <= cell.y + cell.height)
                {
                    col = RAYWHITE;
                    if (!started && IsMouseButtonPressed(0))
                    {
                        initGame(grid, x, y, mineCount, rows, columns);
                        started = true;
                    }
                }

                DrawRectangleRounded(cell, 0.1, 0, col);
                if (grid[x][y] == -1)
                    DrawCircle(cell.x + cellSize / 2, cell.y + cellSize / 2, cellSize / 4, BLACK);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
