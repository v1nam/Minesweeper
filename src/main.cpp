#include <sstream>
#include <vector>
#include <algorithm>

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

std::vector<Vector2> adjacents(std::vector<std::vector<Cell>> &grid, int x, int y, int rows, int columns)
{
    std::vector<Vector2> adjc;
    for (int i{-1}; i <= 1; i++)
    {
        for (int j{-1}; j <= 1; j++) {
            int ax = x + i;
            int ay = y + j;
            if (ax >= 0 && ay >= 0 && ax < columns && ay < rows && (ax != x || ay != y))
                adjc.push_back(Vector2{(float)ax, (float)ay});
        }
    }
    return adjc;
}

int countMines(std::vector<std::vector<Cell>> &grid, std::vector<Vector2>& adjc)
{
    int mc = 0;
    for (Vector2& adPos : adjc)
    {
        if (grid[(int)adPos.x][(int)adPos.y].value == -1)
            mc++;
    }
    return mc;
}

void reveal(std::vector<std::vector<Cell>> &grid, int x, int y, int rows, int columns)
{
    if (!grid[x][y].revealed && grid[x][y].value != -1)
    {
        std::vector<Vector2> adjc = adjacents(grid, x, y, rows, columns);
        grid[x][y].value = countMines(grid, adjc);
        grid[x][y].revealed = true;

        if (grid[x][y].value == 0)
        {
            for (Vector2& adPos : adjc)
                reveal(grid, adPos.x, adPos.y, rows, columns);
        }
    }
}

void initGame(std::vector<std::vector<Cell>> &grid, int x, int y, int mineCount, int rows, int columns)
{
    std::vector<int> minePosX = {x};
    std::vector<int> minePosY = {y};
    for (int i{0}; i < mineCount;)
    {
        int mineX = GetRandomValue(0, columns - 1);
        int mineY = GetRandomValue(0, rows - 1);

        if (std::find(minePosX.begin(), minePosX.end(), mineX) == minePosX.end() || std::find(minePosY.begin(), minePosY.end(), mineY) == minePosY.end())
        {
            i++;
            grid[mineX][mineY].value = -1; // -1 means this cell is a mine
            minePosX.push_back(mineX);
            minePosY.push_back(mineY);
        }
    }
    reveal(grid, x, y, rows, columns);
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

    const std::vector<Color> colArr = {Color{96, 106, 126, 255}, green, yellow, orange, red, teal, aqua, lblue, blue};
    char const* numbers[] = {"1", "2", "3", "4", "5", "6", "7", "8"}; 

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
                        } else reveal(grid, x, y, rows, columns);
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
