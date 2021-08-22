#pragma once

#include <random>
#include <vector>

#include "colors.hpp"
#include "raylib.h"

struct Cell {
    bool revealed = false;
    int value = 0;
    Color color = gray;
};

class Minesweeper {
public:
    int rows;
    int columns;
    int mineCount;
    int revealedCells = 0;

    bool started = false;
    bool won = false;

    std::vector<std::vector<Cell>> grid;
    char const* endText = "Lost";

    Minesweeper(int rows = 8, int columns = 8, int mineCount = 10);
    std::vector<Vector2> adjacents(int x, int y);
    int countMines(std::vector<Vector2>& adjc);
    void reveal(int x, int y);
    void initGame(int x, int y, std::mt19937 gen);
    void clear();
};
