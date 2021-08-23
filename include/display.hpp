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
private:
    const char* pauseText = "PAUSED";
    const std::vector<Color> colArr = { Color { 96, 106, 126, 255 }, lblue, yellow, orange, red, teal, aqua, green, blue };
    char const* numbers[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };

public:
    int screenWidth;
    int screenHeight;
    int pad;
    int cellSize;

    Rectangle menuBtn1;
    Rectangle menuBtn2;
    Rectangle gmovBtn;

    State state = State::Playing;

    bool textureMade = false; // for storing whether game over texture is made
    RenderTexture2D gameOverTexture;
    Texture2D boom = LoadTexture("bang.png");

    Minesweeper mnsp;

    Display(int pad, int screenWidth, int screenHeight);
    void draw();
    void drawGame(float mouseHoverX, float mouseHoverY);
    void drawGameOver(float mouseHoverX, float mouseHoverY);
    void drawMenu(float mouseHoverX, float mouseHoverY);
    void reset();
};
