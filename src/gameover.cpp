#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawGameOver(float mouseHoverX, float mouseHoverY)
{
    if (!textureMade) {
        BeginTextureMode(gameOverTexture);
        {
            ClearBackground(bgCol);
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
                        if (cell.revealed) {
                            float scale = ((float)cellSize / 3.f) / ((float)boom.width / 2.f);
                            DrawTextureEx(
                                boom,
                                Vector2 { cellPos.x + (scale * boom.width) / 3.f, cellPos.y + (scale * boom.width) / 3.f },
                                0.0, scale, WHITE);
                        } else
                            DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
                    } else if (cell.value > 0) {
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
        screenWidth += 100;
        SetWindowSize(screenWidth, screenHeight);
        gmovBtn = Rectangle { (float)screenWidth - 90, (float)screenHeight - 100, 80.0, 50.0 };
    } else {
        ClearBackground(bgCol);
        DrawTextureRec(gameOverTexture.texture, Rectangle { 0, 0, 548, -548 }, Vector2 { 0, 0 }, WHITE);
        DrawText("You", (screenWidth - 100) + (50 - MeasureText("You", 25) / 2.), screenHeight / 2 - 50, 25, lblue);
        DrawText(mnsp.endText, (screenWidth - 100) + (50 - MeasureText(mnsp.endText, 30) / 2.), screenHeight / 2. + 25,
            30, mnsp.won ? green : red);
        Color hovCol = gray;
        if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, gmovBtn)) {
            hovCol = hlt;
            if (IsMouseButtonPressed(0))
                reset();
        }
        DrawRectangleRounded(gmovBtn, 0.3, 0, hovCol);
        DrawRectangleRoundedLines(gmovBtn, 0.3, 0, 3.0, black);
        DrawText("M e n u", gmovBtn.x + (gmovBtn.width / 2.0 - MeasureText("M e n u", 18) / 2.0), gmovBtn.y + 15.0, 18,
            aqua);
    }
}