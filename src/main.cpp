#include <vector>

#include "colors.hpp"
#include "display.hpp"
#include "minesweeper.hpp"
#include "raylib.h"

int main()
{
    const int screenWidth = 548;
    const int screenHeight = 436;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Minesweeper");

    Display display = Display(4, screenWidth, screenHeight);
    display.state = State::StartMenu;

    while (!WindowShouldClose()) {
        BeginDrawing();
        display.draw();
        if (IsKeyPressed(KEY_Q))
            display.reset();
        EndDrawing();
    }
    UnloadTexture(display.gameOverTexture.texture);
    UnloadRenderTexture(display.gameOverTexture);
    CloseWindow();
    return 0;
}
