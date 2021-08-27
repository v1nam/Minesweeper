#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "colors.hpp"
#include "raylib.h"

struct Cell {
    bool revealed = false;
    int value = 0;
    Color color = gray;
    bool flagged = false;
};

class Minesweeper {
private:
    std::string mineCountStr;

public:
    int rows;
    int columns;
    int mineCount;
    int revealedCells = 0;
    int flagCount = 0;

    bool started = false;
    bool won = false;

    std::unordered_set<int*> flagCoords;

    std::vector<std::vector<Cell>> grid;
    char const* endText = "Lost";

    Minesweeper(int rows = 8, int columns = 8, int mineCount = 10);
    std::vector<Vector2> adjacents(int x, int y);
    int countMines(std::vector<Vector2>& adjc);
    void reveal(int x, int y, RenderTexture2D& gridTex,
        Rectangle& cellPos,
        int& cellSize,
        const std::vector<const char*>& numbers,
        const std::vector<Color>& colArr);
    void initGame(int x, int y);
    void clear();
    std::string flagCountDisplay();
};
