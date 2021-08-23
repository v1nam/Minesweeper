#include <random>

#include "colors.hpp"
#include "display.hpp"
#include "raylib.h"

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
    std::random_device rd;
    std::mt19937 gen(rd());

    int mouseHoverX = GetMouseX();
    int mouseHoverY = GetMouseY();

    switch (state) {
    case State::Playing: {
        ClearBackground(bgCol);

        if (mnsp.revealedCells == mnsp.rows * mnsp.columns - mnsp.mineCount) {
            mnsp.won = true;
            mnsp.endText = "Won!";
            state = State::GameOver;
            break;
        }
        for (int x { 0 }; x < mnsp.columns; x++) {
            for (int y { 0 }; y < mnsp.rows; y++) {
                Rectangle cellPos = Rectangle { (float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                    (float)cellSize, (float)cellSize };
                Cell& cell = mnsp.grid[x][y];
                Color cellCol = cell.color;

                // checking if cursor is hovering on a cell
                if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, cellPos)) {
                    cellCol = hlt;
                    if (IsMouseButtonPressed(0)) {
                        if (!mnsp.started)
                            mnsp.initGame(x, y, gen);
                        else if (cell.value == -1) {
                            mnsp.won = false;
                            cell.revealed = true;
                            state = State::GameOver;
                            //DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, red);
                        } else
                            mnsp.reveal(x, y);
                    }
                }
                if (cell.revealed && cell.value >= 0)
                    cellCol = colArr[cell.value];

                DrawRectangleRounded(cellPos, 0.1, 0, cellCol);
                /*
                if (cell.value == -1) {
                    DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, bgCol);
                }
                */
                if (cell.value > 0) {
                    const char* text = numbers[cell.value - 1];
                    float size = cellSize / 2.0;
                    DrawText(text, (cellPos.x + cellSize / 2) - (MeasureText(text, size) / 2), cellPos.y + cellSize / 4,
                        size, bgCol);
                }
            }
        }

        if (IsKeyPressed(KEY_SPACE))
            state = State::Paused;
        break;
    }
    case State::StartMenu: {
        ClearBackground(bgCol);

        float size1 = menuBtn1.width / 4.0;
        float size2 = menuBtn2.width / 4.0;
        const char* text1 = "8 x 8";
        const char* text2 = "16 x 16";

        Color btcol1 = black;
        Color btcol2 = black;

        if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, menuBtn1)) {
            btcol1 = gray;
            if (IsMouseButtonPressed(0)) {
                screenWidth = 404;
                screenHeight = 404;
                SetWindowSize(screenWidth, screenHeight);
                mnsp = Minesweeper(8, 8, 10);
                cellSize = (screenWidth - pad * (mnsp.columns + 1)) / mnsp.columns;
                state = State::Playing;
            }
        }
        if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, menuBtn2)) {
            btcol2 = gray;
            if (IsMouseButtonPressed(0)) {
                screenWidth = 548;
                screenHeight = 548;
                SetWindowSize(screenWidth, screenHeight);
                mnsp = Minesweeper(16, 16, 40);
                cellSize = (screenWidth - pad * (mnsp.columns + 1)) / mnsp.columns;
                state = State::Playing;
            }
        }

        DrawRectangleRounded(menuBtn1, 0.3, 0, btcol1);
        DrawRectangleRounded(menuBtn2, 0.3, 0, btcol2);

        DrawText(text1, (menuBtn1.x + menuBtn1.width / 2.) - (MeasureText(text1, size1) / 2.0), menuBtn1.y + 30.0,
            size1, lblue);
        DrawText(text2, (menuBtn2.x + menuBtn2.width / 2.) - (MeasureText(text2, size2) / 2.0), menuBtn2.y + 30.0,
            size2, blue);

        size1 = menuBtn1.width / 8.0;
        size2 = menuBtn2.width / 8.0;
        text1 = "10 Mines";
        text2 = "40 Mines";

        DrawText(text1, (menuBtn1.x + menuBtn1.width / 2.) - (MeasureText(text1, size1) / 2.0), menuBtn1.y + 110.0,
            size1, red);
        DrawText(text2, (menuBtn2.x + menuBtn2.width / 2.) - (MeasureText(text2, size2) / 2.0), menuBtn2.y + 110.0,
            size2, red);
        break;
    }
    case State::GameOver: {
        if (!textureMade) {
            BeginTextureMode(gameOverTexture);
            {
                ClearBackground(bgCol);
                for (int x { 0 }; x < mnsp.columns; x++) {
                    for (int y { 0 }; y < mnsp.rows; y++) {
                        Rectangle cellPos = Rectangle { (float)pad + x * (cellSize + pad), (float)pad + y * (cellSize + pad),
                            (float)cellSize, (float)cellSize };
                        Cell cell = mnsp.grid[x][y];
                        Color cellCol = cell.color;
                        if (cell.revealed && cell.value >= 0)
                            cellCol = colArr[cell.value];

                        DrawRectangleRounded(cellPos, 0.1, 0, cellCol);
                        if (cell.value == -1) {
                            Color mineCol = bgCol;
                            if (cell.revealed)
                                mineCol = red;
                            DrawCircle(cellPos.x + cellSize / 2, cellPos.y + cellSize / 2, cellSize / 4, mineCol);
                        } else if (cell.value > 0) {
                            const char* text = numbers[cell.value - 1];
                            float size = cellSize / 2.0;
                            DrawText(text, (cellPos.x + cellSize / 2) - (MeasureText(text, size) / 2), cellPos.y + cellSize / 4,
                                size, bgCol);
                        }
                    }
                }
            }
            EndTextureMode();
            textureMade = true;
            screenWidth += 100;
            SetWindowSize(screenWidth, screenHeight);
            gmovBtn = Rectangle { (float)screenWidth - 90, (float)screenHeight - 100, 80.0, 50.0 };
        } else {
            ClearBackground(bgCol);
            DrawTextureRec(gameOverTexture.texture, Rectangle { 0, 0, 548, -548 }, Vector2 { 0, 0 }, WHITE);
            DrawText("You", (screenWidth - 100) + (50 - MeasureText("You", 25) / 2.), screenHeight / 2 - 50, 25, lblue);
            DrawText(mnsp.endText, (screenWidth - 100) + (50 - MeasureText(mnsp.endText, 30) / 2.),
                screenHeight / 2. + 25, 30, mnsp.won ? green : red);
            Color hovCol = gray;
            if (CheckCollisionPointRec(Vector2 { (float)mouseHoverX, (float)mouseHoverY }, gmovBtn)) {
                hovCol = hlt;
                if (IsMouseButtonPressed(0))
                    reset();
            }
            DrawRectangleRounded(gmovBtn, 0.3, 0, hovCol);
            DrawRectangleRoundedLines(gmovBtn, 0.3, 0, 3.0, black);
            DrawText("M e n u", gmovBtn.x + (gmovBtn.width / 2.0 - MeasureText("M e n u", 18) / 2.0), gmovBtn.y + 15.0, 18, aqua);
        }
        break;
    }
    case State::Paused:
        ClearBackground(bgCol);
        DrawText(pauseText, (screenWidth / 2 - MeasureText(pauseText, 50) / 2), screenHeight / 3, 50, hlt);
        if (IsKeyPressed(KEY_SPACE))
            state = State::Playing;
        break;
    }
}

void Display::reset()
{
    state = State::StartMenu;
    screenWidth = 548;
    screenHeight = 436;
    SetWindowSize(548, 436);
    mnsp.clear();
    textureMade = false;
}
