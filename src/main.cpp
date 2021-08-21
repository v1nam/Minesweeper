#include <vector>

#include "raylib.h"
#include "minesweeper.hpp"
#include "colors.hpp"
#include "display.hpp"

int main()
{
    const int screenWidth = 436;
    const int screenHeight = 436;

    Minesweeper mnsp = Minesweeper(8, 8, 10);
    Display display = Display((screenWidth - 4 * (mnsp.columns + 1)) / mnsp.columns, 4, mnsp);

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        display.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
