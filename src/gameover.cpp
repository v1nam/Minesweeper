#include <string>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawGameOver(float mouseHoverX, float mouseHoverY)
{
    if (!textureMade) {
        BeginTextureMode(gameOverTexture);
        {
            ClearBackground(bgCol);
            DrawTexture(clock, screenWidth - 75 - clock.width / 2, 2, WHITE);
            std::string text = timeElapsed.getTimeDisplay();
            DrawText(text.c_str(), (screenWidth - 150) + 75 - (MeasureText(text.c_str(), 20) / 2), 50, 20, lblue);
            DrawTexture(disflag, (screenWidth - 75 - disflag.width / 2) + 5, 100, WHITE);
            std::string fcDis = mnsp.flagCountDisplay();
            DrawText(fcDis.c_str(), screenWidth - 75 - MeasureText(fcDis.c_str(), 20) / 2, 155, 20, lblue);
            for (int x { 0 }; x < mnsp.columns; x++) {
                for (int y { 0 }; y < mnsp.rows; y++) {
                    Rectangle cellPos = Rectangle { (float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                        (float)cellSize, (float)cellSize };
                    Cell cell = mnsp.grid[x][y];
                    Color cellCol = cell.color;
                    if (cell.revealed && cell.value >= 0)
                        cellCol = colArr[cell.value];

                    DrawRectangleRounded(cellPos, 0.1, 0, cellCol);

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
                    if (cell.value > 0) {
                        const char* text = numbers[cell.value - 1];
                        float size = cellSize / 2.0;
                        DrawText(text, (cellPos.x + cellSize / 2) - (MeasureText(text, size) / 2),
                            cellPos.y + cellSize / 4, size, bgCol);
                    }
                }
            }
        }
        EndTextureMode();
        textureMade = true;
        SetWindowSize(screenWidth, screenHeight);
        gmovBtn = Rectangle { (float)screenWidth - 125, (float)screenHeight - 65, 100.0, 50.0 };
    } else {
        ClearBackground(bgCol);
        DrawTextureRec(gameOverTexture.texture, Rectangle { 0, 0, 548, -548 }, Vector2 { 0, 0 }, WHITE);
        DrawText("You", (screenWidth - 150) + (75 - MeasureText("You", 25) / 2.), screenHeight / 2 + 35, 25, lblue);
        DrawText(mnsp.endText, (screenWidth - 150) + (75 - MeasureText(mnsp.endText, 30) / 2.), screenHeight / 2. + 70,
            30, mnsp.won ? green : red);
        Color hovCol = gray;
        if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, gmovBtn)) {
            hovCol = hlt;
            if (IsMouseButtonPressed(0))
                reset();
        }
        DrawRectangleRounded(gmovBtn, 0.2, 0, hovCol);
        DrawRectangleRoundedLines(gmovBtn, 0.2, 0, 3.0, black);
        DrawText("Menu", gmovBtn.x + (gmovBtn.width / 2.0 - MeasureText("Menu", 20) / 2.0), gmovBtn.y + 15.0, 20,
            aqua);
    }
}