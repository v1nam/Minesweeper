#include <iostream>
#include <string>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawGameOver()
{
    if (!textureMade) {
        BeginTextureMode(gamePlayTexture);
        {
            for (int x { 0 }; x < mnsp.columns; x++) {
                for (int y { 0 }; y < mnsp.rows; y++) {
                    Rectangle cellPos = indexToPos(x, y);
                    Cell& cell = mnsp.grid[x][y];

                    if (cell.value == -1) {
                        DrawRectangleRounded(cellPos, 0.1, 0, Fade(red, 0.4));
                        if (cell.revealed) {
                            float scale = ((float)cellSize / 3.f) / ((float)boom.width / 2.f);
                            DrawTextureEx(
                                boom,
                                Vector2 { cellPos.x + (scale * boom.width) / 3.f, cellPos.y + (scale * boom.width) / 3.f },
                                0.0, scale, WHITE);
                        } else if (!cell.flagged)
                            DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
                    }
                    if (cell.flagged) {
                        float scale = ((float)cellSize / 3.f) / ((float)flag.width / 2.f);
                        DrawTextureEx(
                            flag,
                            Vector2 { cellPos.x + (scale * flag.width) / 3.f, cellPos.y + (scale * flag.width) / 3.f },
                            0.0, scale, WHITE);
                    }
                }
            }
        }
        EndTextureMode();
        textureMade = true;
    } else {
        ClearBackground(bgCol);
        DrawTextureRec(gamePlayTexture.texture, Rectangle { 0, 0, 548, -548 }, Vector2 { 0, 0 }, WHITE);
        DrawText("You", (screenWidth - 150) + (75 - MeasureText("You", 25) / 2.), screenHeight / 2 + 35, 25, lblue);
        DrawText(mnsp.endText, (screenWidth - 150) + (75 - MeasureText(mnsp.endText, 30) / 2.), screenHeight / 2. + 70,
            30, mnsp.won ? green : red);
        Rectangle& btnRef = menuBtn;
        drawSideBtn("Menu", boundReset, btnRef);
        drawClockFlag();
    }
}