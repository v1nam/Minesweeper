#include <iostream>
#include <random>
#include <string>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"
#include <random>

Display::Display(int pad, int screenWidth, int screenHeight)
{
    this->pad = pad;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    menuBtn1 = Rectangle { 74.f, screenHeight / 2.0f - 90, 180.0f, 180.0f };
    menuBtn2 = Rectangle { 294.0f, screenHeight / 2.0f - 90, 180.0f, 180.0f };
    gameOverTexture = LoadRenderTexture(548, 548);
}

void Display::draw()
{
    int mouseHoverX = GetMouseX();
    int mouseHoverY = GetMouseY();

    switch (state) {
    case State::Playing: {
        drawGame(mouseHoverX, mouseHoverY);
        break;
    }
    case State::StartMenu: {
        drawMenu(mouseHoverX, mouseHoverY);
        break;
    }
    case State::GameOver: {
        drawGameOver(mouseHoverX, mouseHoverY);
        break;
    }
    case State::Paused: {
        ClearBackground(bgCol);
        DrawText(pauseText, (screenWidth / 2 - MeasureText(pauseText, 50) / 2), screenHeight / 3, 50, hlt);
        if (IsKeyPressed(KEY_SPACE))
            state = State::Playing;
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