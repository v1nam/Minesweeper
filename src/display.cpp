#include "raylib.h"
#include "display.hpp"
#include "colors.hpp"

Display::Display(int cellSize, int pad, Minesweeper mnsp)
{
    this->pad = pad;
    this->mnsp = mnsp;
    this->cellSize = cellSize;
}

void Display::draw()
{
    switch (state)
    {
    case State::Playing:
    {
        ClearBackground(bgCol);
    
        int mouseHoverX = GetMouseX();
        int mouseHoverY = GetMouseY();

        for (int x{0}; x < mnsp.columns; x++)
        {
            for (int y{0}; y < mnsp.rows; y++)
            {
                Rectangle cellPos = Rectangle{(float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                                           (float)cellSize, (float)cellSize};
                Cell cell = mnsp.grid[x][y];
                Color cellCol = cell.color;

                // checking if cursor is hovering on a cell
                if (cellPos.x <= mouseHoverX && cellPos.y <= mouseHoverY && mouseHoverX <= cellPos.x + cellPos.width &&
                    mouseHoverY <= cellPos.y + cellPos.height && !cell.revealed)
                {
                    cellCol = hlt;
                    if (IsMouseButtonPressed(0))
                    {
                        if (!mnsp.started)
                            mnsp.initGame(x, y);
                        else
                            mnsp.reveal(x, y);
                    }
                }
                if (cell.revealed && cell.value >= 0)
                    cellCol = colArr[cell.value];

                DrawRectangleRounded(cellPos, 0.1, 0, cellCol);
                if (cell.value == -1)
                    DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
                else if (cell.value > 0)
                {
                    const char* text = numbers[cell.value-1];
                    float size = cellSize / 2.0;
                    DrawText(text, (cellPos.x + cellSize / 2) - (MeasureText(text, size) / 2), cellPos.y + cellSize / 4, size, bgCol);
                }
            }
        }
        break;
    }
    case State::GameOver:
        ClearBackground(bgCol);
        break;
    case State::Paused:
        ClearBackground(bgCol);
        break;
    }
}
