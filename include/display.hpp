#pragma once

#include "colors.hpp"
#include "minesweeper.hpp"
#include "raylib.h"

enum class State {
    Paused,
    Playing,
    GameOver,
    StartMenu
};

class Display {
public:
    int screenWidth;
    int screenHeight;
    int pad;
    int cellSize;

    Rectangle menuBtn1;
    Rectangle menuBtn2;

    State state = State::Playing;

    const std::vector<Color> colArr = { Color { 96, 106, 126, 255 }, green, yellow, orange, red, teal, aqua, lblue, blue };
    char const* numbers[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };

    Minesweeper mnsp;

    Display(int cellSize, int pad, Minesweeper mnsp, int screenWidth, int screenHeight);
    void draw();
};
