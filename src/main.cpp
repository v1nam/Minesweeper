#include <cmath>
#include <vector>

#include "colors.hpp"
#include "display.hpp"
#include "minesweeper.hpp"
#include "raylib.h"

int main()
{
    const int screenWidth = 548;
    const int screenHeight = 436;

    Minesweeper mnsp = Minesweeper(8, 8, 10);
    Display display = Display(std::min((screenWidth - 4 * (mnsp.columns + 1)) / mnsp.columns, 50), 4, mnsp, screenWidth, screenHeight);
    display.state = State::StartMenu;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    while (!WindowShouldClose()) {
        BeginDrawing();
        display.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
