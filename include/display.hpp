#pragma once

#include <string>

#include "colors.hpp"
#include "minesweeper.hpp"
#include "raylib.h"

enum class State {
    Paused,
    Playing,
    GameOver,
    StartMenu
};

struct TimeDisplay {
    int minutes;
    int seconds;
    float timeCounter = 0.0;
    std::string getTimeDisplay();
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
    TimeDisplay timeElapsed = TimeDisplay { 0, 0 };

    bool textureMade = false; // for storing whether game over texture is made
    RenderTexture2D gameOverTexture;
    Texture2D boom = LoadTexture("assets/boom.png");
    Texture2D flag = LoadTexture("assets/flag.png");
    Texture2D clock = LoadTexture("assets/clock.png");
    Texture2D disflag = LoadTexture("assets/disflag.png");

    Minesweeper mnsp;

    Display(int pad, int screenWidth, int screenHeight);
    void draw();
    void drawGame(float mouseHoverX, float mouseHoverY);
    void drawGameOver(float mouseHoverX, float mouseHoverY);
    void drawMenu(float mouseHoverX, float mouseHoverY);
    void drawClockFlag();
    void reset();
};
