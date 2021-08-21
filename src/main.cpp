#include <vector>

#include "colors.hpp"
#include "display.hpp"
#include "minesweeper.hpp"
#include "raylib.h"

int main()
{
    const int screenWidth = 548;
    const int screenHeight = 436;

    Display display = Display(4, screenWidth, screenHeight);
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
