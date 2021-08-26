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

    drawSideBtn("Menu", std::bind(&Display::reset, this), mbtnRef);
    drawSideBtn(
        "Pause", [this]() {
            this->state = State::Paused;
        },
        pbtnRef);

    int cellHoverX = ((int)mouseHoverX - pad) / (cellSize + pad);
    int cellHoverY = ((int)mouseHoverY - pad) / (cellSize + pad);
    if (cellHoverX < mnsp.columns && cellHoverY < mnsp.rows) {
        Cell& hoverCell = mnsp.grid[cellHoverX][cellHoverY];

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!mnsp.started)
                mnsp.initGame(cellHoverX, cellHoverY);
            else if (hoverCell.value == -1) {
                mnsp.won = false;
                hoverCell.revealed = true;
                if (hoverCell.flagged) {
                    hoverCell.flagged = false;
                    mnsp.flagCount--;
                }
                state = State::GameOver;
            } else
                mnsp.reveal(cellHoverX, cellHoverY);
        } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            if (!hoverCell.revealed && mnsp.started) {
                if (hoverCell.flagged) {
                    hoverCell.flagged = false;
                    mnsp.flagCount--;
                } else if (mnsp.flagCount < mnsp.mineCount) {
                    hoverCell.flagged = true;
                    mnsp.flagCount++;
                }
            }
        }
    }
    for (int x { 0 }; x < mnsp.columns; x++) {
        for (int y { 0 }; y < mnsp.rows; y++) {
            Rectangle cellPos = Rectangle { (float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                (float)cellSize, (float)cellSize };
            Cell& cell = mnsp.grid[x][y];
            Color cellCol = cell.color;

            if (cellHoverX == x && cellHoverY == y)
                cellCol = hlt;

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

    if (IsKeyPressed(KEY_SPACE) || !IsWindowFocused())
        state = State::Paused;
}