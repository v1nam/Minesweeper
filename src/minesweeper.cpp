#include <vector>
#include <algorithm>
#include <random>

#include "raylib.h"
#include "minesweeper.hpp"

Minesweeper::Minesweeper(int rows, int columns, int mineCount)
{
    this->rows = rows;
    this->columns = columns;
    this->mineCount = mineCount;

    for (int _j{0}; _j < this->columns; _j++)
        grid.push_back(std::vector<Cell>(this->rows));
}

std::vector<Vector2> Minesweeper::adjacents(int x, int y)
{
    std::vector<Vector2> adjc;
    for (int i{-1}; i <= 1; i++)
    {
        for (int j{-1}; j <= 1; j++) {
            int ax = x + i;
            int ay = y + j;
            if (ax >= 0 && ay >= 0 && ax < columns && ay < rows && (ax != x || ay != y))
                adjc.push_back(Vector2{(float)ax, (float)ay});
        }
    }
    return adjc;
}

int Minesweeper::countMines(std::vector<Vector2>& adjc)
{
    int mc = 0;
    for (Vector2& adPos : adjc)
    {
        if (grid[(int)adPos.x][(int)adPos.y].value == -1)
            mc++;
    }
    return mc;
}

void Minesweeper::reveal(int x, int y)
{
    if (!grid[x][y].revealed && grid[x][y].value != -1)
    {
        std::vector<Vector2> adjc = adjacents(x, y);
        grid[x][y].value = countMines(adjc);
        grid[x][y].revealed = true;
        revealedCells++;

        if (grid[x][y].value == 0)
        {
            for (Vector2& adPos : adjc)
                this->reveal(adPos.x, adPos.y);
        }
    }
}

void Minesweeper::initGame(int x, int y, std::mt19937 gen)
{
    std::uniform_int_distribution<> rngX(0, columns - 1);
    std::uniform_int_distribution<> rngY(0, rows - 1);

    for (int i{0}; i < mineCount; i++)
    {
        int mineX = rngX(gen);
        int mineY = rngY(gen);

        if (grid[mineX][mineY].value != -1 && (mineX != x || mineY != y))
            grid[mineX][mineY].value = -1; // -1 means this cell is a mine
        else
            i--;
    }
    this->reveal(x, y);
    started = true;
}
