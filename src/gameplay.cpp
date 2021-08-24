#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

void Display::drawGame(float mouseHoverX, float mouseHoverY)
{
    ClearBackground(bgCol);

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
                if (IsMouseButtonPressed(0)) {
                    if (!mnsp.started)
                        mnsp.initGame(x, y);
                    else if (cell.value == -1) {
                        mnsp.won = false;
                        cell.revealed = true;
                        state = State::GameOver;
                        //DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, red);
                    } else
                        mnsp.reveal(x, y);
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