#include <functional>
#include <random>
#include <string>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

Display::Display(int pad, int screenWidth, int screenHeight)
{
    this->pad = pad;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    startMenuBtn1 = Rectangle { 74.f, screenHeight / 2.0f - 90, 180.0f, 180.0f };
    startMenuBtn2 = Rectangle { 294.0f, screenHeight / 2.0f - 90, 180.0f, 180.0f };
    gameOverTexture = LoadRenderTexture(548, 548);
    gamePlayTexture = LoadRenderTexture(548, 548);

    boundReset = std::bind(&Display::reset, this);
}

void Display::draw()
{
    mouseHoverX = GetMouseX();
    mouseHoverY = GetMouseY();

    switch (state) {
    case State::Playing: {
        drawGame();
        break;
    }
    case State::StartMenu: {
        drawMenu();
        break;
    }
    case State::GameOver: {
        drawGameOver();
        break;
    }
    case State::Paused: {
        ClearBackground(bgCol);
        DrawText(pauseText, ((screenWidth - 150) / 2 - MeasureText(pauseText, 50) / 2), screenHeight / 3, 50, hlt);
        DrawLine(screenWidth - 150, 0, screenWidth - 150, screenHeight, black);
        if (IsKeyPressed(KEY_SPACE))
            state = State::Playing;
        drawClockFlag();

        Rectangle& mbtnRef = menuBtn;
        Rectangle& pbtnRef = pauseBtn;

        drawSideBtn("Menu", boundReset, mbtnRef);
        drawSideBtn(
            "Resume", [this]() {
                this->state = State::Playing;
            },
            pbtnRef);
        break;
    }
    }
}

void Display::drawClockFlag()
{
    DrawTexture(clock, screenWidth - 75 - clock.width / 2, 2, WHITE);
    DrawTexture(disflag, (screenWidth - 75 - disflag.width / 2) + 5, 100, WHITE);
    std::string fcDis = mnsp.flagCountDisplay();
    DrawText(fcDis.c_str(), screenWidth - 75 - MeasureText(fcDis.c_str(), 20) / 2, 155, 20, lblue);
    if (mnsp.started) {
        if (state == State::Playing)
            timeElapsed.timeCounter += GetFrameTime();
        timeElapsed.seconds = (int)timeElapsed.timeCounter % 60;
        timeElapsed.minutes = (int)timeElapsed.timeCounter / 60;
        std::string text = timeElapsed.getTimeDisplay();
        DrawText(text.c_str(), (screenWidth - 150) + 75 - (MeasureText(text.c_str(), 20) / 2), 50, 20, lblue);
    } else {
        const char* text = "00:00";
        DrawText(text, (screenWidth - 150) + 75 - (MeasureText(text, 20) / 2), 50, 20, lblue);
    }
}

void Display::reset()
{
    state = State::StartMenu;
    timeElapsed = TimeDisplay { 0, 0 };
    screenWidth = 548;
    screenHeight = 436;
    SetWindowSize(548, 436);
    mnsp.clear();
    textureMade = false;
}

void Display::drawSideBtn(const char* text, std::function<void()> action, Rectangle& dims)
{
    Color hovCol = gray;
    if (CheckCollisionPointRec(Vector2 { mouseHoverX, mouseHoverY }, dims)) {
        hovCol = hlt;
        if (IsMouseButtonPressed(0))
            action();
    }
    DrawRectangleRounded(dims, 0.2, 0, hovCol);
    DrawRectangleRoundedLines(dims, 0.2, 0, 3.0, black);
    DrawText(text, dims.x + (dims.width / 2.0 - MeasureText(text, 20) / 2.0), dims.y + 15.0, 20,
        aqua);
}

Rectangle Display::indexToPos(int x, int y)
{
    return Rectangle { (float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + (float)pad),
        (float)cellSize, (float)cellSize };
}

std::string TimeDisplay::getTimeDisplay()
{
    std::string secondDisp;
    std::string minDisp;
    if (seconds < 10)
        secondDisp = "0";
    if (minutes < 10)
        minDisp = "0";
    secondDisp += std::to_string(seconds);
    minDisp += std::to_string(minutes);
    minDisp += ":";
    minDisp += secondDisp;
    return minDisp;
}