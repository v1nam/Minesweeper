#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawMenu()
{
    ClearBackground(bgCol);

    float size1 = startMenuBtn1.width / 4.0;
    float size2 = startMenuBtn2.width / 4.0;
    const char* text1 = "8 x 8";
    const char* text2 = "16 x 16";

    Color btcol1 = black;
    Color btcol2 = black;

    bool hov1 = CheckCollisionPointRec(Vector2 { mouseHoverX, mouseHoverY }, startMenuBtn1);
    bool hov2 = CheckCollisionPointRec(Vector2 { mouseHoverX, mouseHoverY }, startMenuBtn2);

    bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (hov1) {
        btcol1 = gray;
        if (mousePressed) {
            screenWidth = 404;
            screenHeight = 404;
            mnsp = Minesweeper(8, 8, 10);
        }
    } else if (hov2) {
        btcol2 = gray;
        if (mousePressed) {
            screenWidth = 548;
            screenHeight = 548;
            mnsp = Minesweeper(16, 16, 40);
        }
    }
    if ((hov1 || hov2) && mousePressed) {
        cellSize = (screenWidth - pad * (mnsp.columns + 1)) / mnsp.columns;
        BeginTextureMode(gamePlayTexture);
        ClearBackground(bgCol);
        for (int x { 0 }; x < mnsp.columns; x++) {
            for (int y { 0 }; y < mnsp.rows; y++)
                DrawRectangleRounded(indexToPos(x, y), 0.1, 0, mnsp.grid[x][y].color);
        }
        EndTextureMode();
        screenWidth += 150;
        SetWindowSize(screenWidth, screenHeight);
        menuBtn = Rectangle { (float)screenWidth - 125, (float)screenHeight - 65, 100.0, 50.0 };
        pauseBtn = Rectangle { (float)screenWidth - 125, (float)screenHeight - 130, 100.0, 50.0 };
        state = State::Playing;
    }

    DrawRectangleRounded(startMenuBtn1, 0.3, 0, btcol1);
    DrawRectangleRounded(startMenuBtn2, 0.3, 0, btcol2);

    DrawText(text1, (startMenuBtn1.x + startMenuBtn1.width / 2.) - (MeasureText(text1, size1) / 2.0), startMenuBtn1.y + 30.0,
        size1, lblue);
    DrawText(text2, (startMenuBtn2.x + startMenuBtn2.width / 2.) - (MeasureText(text2, size2) / 2.0), startMenuBtn2.y + 30.0,
        size2, blue);

    size1 = startMenuBtn1.width / 8.0;
    size2 = startMenuBtn2.width / 8.0;
    text1 = "10 Mines";
    text2 = "40 Mines";

    DrawText(text1, (startMenuBtn1.x + startMenuBtn1.width / 2.) - (MeasureText(text1, size1) / 2.0), startMenuBtn1.y + 110.0,
        size1, red);
    DrawText(text2, (startMenuBtn2.x + startMenuBtn2.width / 2.) - (MeasureText(text2, size2) / 2.0), startMenuBtn2.y + 110.0,
        size2, red);
}