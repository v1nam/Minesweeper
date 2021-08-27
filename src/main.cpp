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

    Image icon = LoadImage("assets/iconmine.png");
    SetWindowIcon(icon);

    Display display = Display(4, screenWidth, screenHeight);
    display.state = State::StartMenu;

    while (!WindowShouldClose()) {
        BeginDrawing();
        display.draw();
        if (IsKeyPressed(KEY_Q))
            display.reset();
        EndDrawing();
    }
    UnloadImage(icon);
    UnloadTexture(display.boom);
    UnloadTexture(display.flag);
    UnloadTexture(display.disflag);
    UnloadTexture(display.clock);
    UnloadTexture(display.gamePlayTexture.texture);
    UnloadRenderTexture(display.gamePlayTexture);
    CloseWindow();
    return 0;
}
