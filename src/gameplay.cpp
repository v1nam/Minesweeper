#include <string>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawGame(float mouseHoverX, float mouseHoverY)
{
    ClearBackground(bgCol);

    DrawTexture(clock, screenWidth - 75 - clock.width / 2, 2, WHITE);
    DrawTexture(disflag, (screenWidth - 75 - disflag.width / 2) + 5, 100, WHITE);
    std::string fcDis = mnsp.flagCountDisplay();
    DrawText(fcDis.c_str(), screenWidth - 75 - MeasureText(fcDis.c_str(), 20) / 2, 155, 20, lblue);
    if (mnsp.started) {
        timeElapsed.timeCounter += GetFrameTime();
        timeElapsed.seconds = (int)timeElapsed.timeCounter % 60;
        timeElapsed.minutes = (int)timeElapsed.timeCounter / 60;
        std::string text = timeElapsed.getTimeDisplay();
        DrawText(text.c_str(), (screenWidth - 150) + 75 - (MeasureText(text.c_str(), 20) / 2), 50, 20, lblue);
    } else {
        const char* text = "00:00";
        DrawText(text, (screenWidth - 150) + 75 - (MeasureText(text, 20) / 2), 50, 20, lblue);
    }

    if (mnsp.revealedCells == mnsp.rows * mnsp.columns - mnsp.mineCount) {
        mnsp.won = true;
        mnsp.endText = "Won!";
        state = State::GameOver;
        return;
    }
    for (int x { 0 }; x < mnsp.columns; x++) {
        for (int y { 0 }; y < mnsp.rows; y++) {
            Rectangle cellPos = Rectangle { (float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                (float)cellSize, (float)cellSize };
            Cell& cell = mnsp.grid[x][y];
            Color cellCol = cell.color;

            // checking if cursor is hovering on a cell
            if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, cellPos)) {
                cellCol = hlt;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (!mnsp.started)
                        mnsp.initGame(x, y);
                    else if (cell.value == -1) {
                        mnsp.won = false;
                        cell.revealed = true;
                        cell.flagged = false;
                        state = State::GameOver;
                        //DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, red);
                    } else
                        mnsp.reveal(x, y);
                } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                    if (!cell.revealed) {
                        if (cell.flagged) {
                            cell.flagged = false;
                            mnsp.flagCount--;
                        } else if (mnsp.flagCount <= mnsp.mineCount) {
                            cell.flagged = true;
                            mnsp.flagCount++;
                        }
                    }
                }
            }
            if (cell.revealed && cell.value >= 0)
                cellCol = colArr[cell.value];

            DrawRectangleRounded(cellPos, 0.1, 0, cellCol);
            /*
                if (cell.value == -1) {
                    DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
                }
            */
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
                DrawText(text, (cellPos.x + cellSize / 2) - (MeasureText(text, size) / 2), cellPos.y + cellSize / 4,
                    size, bgCol);
            }
        }
    }

    if (IsKeyPressed(KEY_SPACE))
        state = State::Paused;
}