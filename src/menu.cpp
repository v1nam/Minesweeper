#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawMenu(float mouseHoverX, float mouseHoverY)
{
    ClearBackground(bgCol);

    float size1 = menuBtn1.width / 4.0;
    float size2 = menuBtn2.width / 4.0;
    const char* text1 = "8 x 8";
    const char* text2 = "16 x 16";

    Color btcol1 = black;
    Color btcol2 = black;

    if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, menuBtn1)) {
        btcol1 = gray;
        if (IsMouseButtonPressed(0)) {
            screenWidth = 404;
            screenHeight = 404;
            SetWindowSize(screenWidth, screenHeight);
            mnsp = Minesweeper(8, 8, 10);
            cellSize = (screenWidth - pad * (mnsp.columns + 1)) / mnsp.columns;
            state = State::Playing;
        }
    }
    if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, menuBtn2)) {
        btcol2 = gray;
        if (IsMouseButtonPressed(0)) {
            screenWidth = 548;
            screenHeight = 548;
            SetWindowSize(screenWidth, screenHeight);
            mnsp = Minesweeper(16, 16, 40);
            cellSize = (screenWidth - pad * (mnsp.columns + 1)) / mnsp.columns;
            state = State::Playing;
        }
    }

    DrawRectangleRounded(menuBtn1, 0.3, 0, btcol1);
    DrawRectangleRounded(menuBtn2, 0.3, 0, btcol2);

    DrawText(text1, (menuBtn1.x + menuBtn1.width / 2.) - (MeasureText(text1, size1) / 2.0), menuBtn1.y + 30.0,
        size1, lblue);
    DrawText(text2, (menuBtn2.x + menuBtn2.width / 2.) - (MeasureText(text2, size2) / 2.0), menuBtn2.y + 30.0,
        size2, blue);

    size1 = menuBtn1.width / 8.0;
    size2 = menuBtn2.width / 8.0;
    text1 = "10 Mines";
    text2 = "40 Mines";

    DrawText(text1, (menuBtn1.x + menuBtn1.width / 2.) - (MeasureText(text1, size1) / 2.0), menuBtn1.y + 110.0,
        size1, red);
    DrawText(text2, (menuBtn2.x + menuBtn2.width / 2.) - (MeasureText(text2, size2) / 2.0), menuBtn2.y + 110.0,
        size2, red);
}