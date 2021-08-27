#pragma once

#include <functional>
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
    std::function<void()> boundReset;

public:
    int screenWidth;
    int screenHeight;
    int pad;
    int cellSize;

    float mouseHoverX;
    float mouseHoverY;

    Rectangle startMenuBtn1;
    Rectangle startMenuBtn2;
    Rectangle menuBtn;
    Rectangle pauseBtn;

    State state = State::Playing;
    TimeDisplay timeElapsed = TimeDisplay { 0, 0 };

    const std::vector<Color> colArr = { Color { 96, 106, 126, 255 }, lblue, yellow, orange, red, teal, aqua, green, blue };
    const std::vector<const char*> numbers = { "1", "2", "3", "4", "5", "6", "7", "8" };
    bool textureMade = false; // for storing whether game over texture is made
    RenderTexture2D gameOverTexture;
    RenderTexture2D gamePlayTexture;
    Texture2D boom = LoadTexture("assets/boom.png");
    Texture2D flag = LoadTexture("assets/flag.png");
    Texture2D clock = LoadTexture("assets/clock.png");
    Texture2D disflag = LoadTexture("assets/disflag.png");

    Minesweeper mnsp;

    Display(int pad, int screenWidth, int screenHeight);
    void draw();
    void drawGame();
    void drawGameOver();
    void drawMenu();
    void drawClockFlag();
    void drawSideBtn(const char* text, std::function<void()>, Rectangle& dims);
    void reset();
    Rectangle indexToPos(int x, int y);
};
