#include <functional>
#include <string>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawGame()
{
    ClearBackground(bgCol);

    if (mnsp.revealedCells == mnsp.rows * mnsp.columns - mnsp.mineCount) {
        mnsp.won = true;
        mnsp.endText = "Won!";
        state = State::GameOver;
        return;
    }
    drawClockFlag();
    Rectangle& mbtnRef = menuBtn;
    Rectangle& pbtnRef = pauseBtn;
    drawSideBtn("Menu", boundReset, mbtnRef);
    drawSideBtn(
        "Pause", [this]() {
            this->state = State::Paused;
        },
        pbtnRef);

    DrawTextureRec(gamePlayTexture.texture, Rectangle { 0, 0, (float)screenWidth - 150, -(float)548 }, Vector2 { 0, 0 }, WHITE);

    int cellHoverX = ((int)mouseHoverX - pad) / (cellSize + pad);
    int cellHoverY = ((int)mouseHoverY - pad) / (cellSize + pad);

    Rectangle cellRect = indexToPos(cellHoverX, cellHoverY);
    if (cellHoverX < mnsp.columns && cellHoverY < mnsp.rows) {
        Cell& hoverCell = mnsp.grid[cellHoverX][cellHoverY];
        int flagC[2] = { cellHoverX, cellHoverY };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!mnsp.started) {
                mnsp.initGame(cellHoverX, cellHoverY);
                mnsp.reveal(cellHoverX, cellHoverY, gamePlayTexture, cellRect, cellSize, numbers, colArr);
                mnsp.started = true;
            } else if (hoverCell.value == -1) {
                mnsp.won = false;
                hoverCell.revealed = true;
                if (hoverCell.flagged) {
                    hoverCell.flagged = false;
                    mnsp.flagCount--;
                }
                state = State::GameOver;
            } else
                mnsp.reveal(cellHoverX, cellHoverY, gamePlayTexture, cellRect, cellSize, numbers, colArr);
        } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            if (!hoverCell.revealed && mnsp.started) {
                if (hoverCell.flagged) {
                    hoverCell.flagged = false;
                    mnsp.flagCount--;
                    mnsp.flagCoords.erase(flagC);
                } else if (mnsp.flagCount < mnsp.mineCount) {
                    hoverCell.flagged = true;
                    mnsp.flagCount++;
                    mnsp.flagCoords.insert(flagC);
                }
            }
        }
        DrawRectangleRounded(cellRect, 0.1, 0, hlt);
    }
    for (int* flagCoord : mnsp.flagCoords) {
        Rectangle cellPos = indexToPos(flagCoord[0], flagCoord[1]);
        float scale = ((float)cellSize / 3.f) / ((float)flag.width / 2.f);
        DrawTextureEx(
            flag,
            Vector2 { cellPos.x + (scale * flag.width) / 3.f, cellPos.y + (scale * flag.width) / 3.f },
            0.0, scale, WHITE);
    }
    if (IsKeyPressed(KEY_SPACE) || !IsWindowFocused())
        state = State::Paused;
}