#include <vector>

#include "raylib.h"

// from https://nordtheme.com
const Color bgCol  = Color{46, 52, 64, 255};
const Color red    = Color{191, 97, 106, 255};
const Color hlt    = Color{76, 86, 106, 255};
const Color teal   = Color{143, 188, 187, 255};
const Color aqua   = Color{136, 192, 208, 255};
const Color blue   = Color{94, 129, 172, 255};
const Color gray   = Color{67, 76, 94, 255};
const Color lblue  = Color{129, 161, 193, 255};
const Color green  = Color{163, 190, 140, 255};
const Color yellow = Color{235, 203, 139, 255};
const Color orange = Color{208, 135, 112, 255};


struct Cell
{
    bool revealed = false;
    int value = 0;
    Color color = gray;
};

void reveal(std::vector<std::vector<Cell>> &grid, int x, int y)
{

}

void initGame(std::vector<std::vector<Cell>> &grid, int x, int y, int mineCount, int rows, int columns)
{
    for (int i{0}; i < mineCount;)
    {
        int mineX = GetRandomValue(0, columns - 1);
        int mineY = GetRandomValue(0, rows - 1);

        if (mineX != x || mineY != y)
        {
            i++;
            grid[mineX][mineY].value = -1; // -1 means this cell is a mine
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

    const Color colArr[8] = {green, yellow, orange, red, teal, aqua, lblue, blue};

    bool started = false;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    std::vector<std::vector<Cell>> grid(columns);
    for (int j{0}; j < columns; j++)
        grid[j] = std::vector<Cell>(rows);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(bgCol);

        int mouseHoverX = GetMouseX();
        int mouseHoverY = GetMouseY();

        for (int x{0}; x < columns; x++)
        {
            for (int y{0}; y < rows; y++)
            {
                Rectangle cellPos = Rectangle{(float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                                           (float)cellSize, (float)cellSize};
                Cell cell = grid[x][y];
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
                            initGame(grid, x, y, mineCount, rows, columns);
                            started = true;
                        } else reveal(grid, x, y);
                    }
                }

                DrawRectangleRounded(cellPos, 0.1, 0, cellCol);
                if (cell.value == -1)
                    DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
