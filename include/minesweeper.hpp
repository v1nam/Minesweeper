#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "colors.hpp"
#include "raylib.h"

class CellVec {
public:
    int x;
    int y;

    bool operator==(const CellVec other) const { return x == other.x && y == other.y; };
};

class HashFunction {
public:
    size_t operator()(const CellVec& cv) const
    {
        return (std::hash<int>()(cv.x)) ^ (std::hash<int>()(cv.y));
    }
};

struct Cell {
    bool revealed = false;
    int value = 0;
    Color color = gray;
    bool flagged = false;
    CellVec pos;
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

    std::unordered_set<CellVec, HashFunction> flagCoords;

    std::vector<std::vector<Cell>> grid;
    std::vector<Cell*> needsUpdate;

    char const* endText = "Lost";

    Minesweeper(int rows = 8, int columns = 8, int mineCount = 10);
    std::vector<Vector2> adjacents(int x, int y);
    int countMines(std::vector<Vector2>& adjc);
    void reveal(int x, int y);
    void initGame(int x, int y);
    void clear();
    std::string flagCountDisplay();
};