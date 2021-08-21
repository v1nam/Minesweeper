#pragma once

#include "raylib.h"
#include "minesweeper.hpp"
#include "colors.hpp"

enum class State
{
    Paused,
    Playing,
    GameOver
};

class Display
{
    public:
        int pad;
        int cellSize;

        State state = State::Playing;

        const std::vector<Color> colArr = {Color{96, 106, 126, 255}, green, yellow, orange, red, teal, aqua, lblue, blue};
        char const* numbers[8] = {"1", "2", "3", "4", "5", "6", "7", "8"}; 

        Minesweeper mnsp;

        Display(int cellSize, int pad, Minesweeper mnsp);
        void draw();
};
