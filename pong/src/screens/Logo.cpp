#include "Logo.hpp"
#include <raylib.h>

Logo::Logo()
{
  this->framesCounter = 0;
  this->finishScreen = 0;

  this->logoPositionX = 0;
  this->logoPositionY = 0;

  this->lettersCount = 0;

  this->topSideRecWidth = 0;
  this->leftSideRecHeight = 0;

  this->bottomSideRecWidth = 0;
  this->rightSideRecHeight = 0;

  this->raylib[8] = { 0 };     // raylib text array, max 8 letters
  this->state = 0;              // Tracking animation states (State Machine)
  this->alpha = 1.0f;
}

Logo::~Logo()
{

}

void Logo::init()
{
    finishScreen = 0;
    framesCounter = 0;
    lettersCount = 0;

    logoPositionX = GetScreenWidth()/2 - 128;
    logoPositionY = GetScreenHeight()/2 - 128;

    for (int i = 0; i < 8; i++) raylib[i] = '\0';

    state = 0;
    alpha = 1.0f;
}

void Logo::update()
{
    if (state == 0)                 // State 0: Small box blinking
    {
        framesCounter++;

        if (framesCounter == 80)
        {
            state = 1;
            framesCounter = 0;      // Reset counter... will be used later...
        }
    }
    else if (state == 1)            // State 1: Top and left bars growing
    {
        topSideRecWidth += 8;
        leftSideRecHeight += 8;

        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2)            // State 2: Bottom and right bars growing
    {
        bottomSideRecWidth += 8;
        rightSideRecHeight += 8;

        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3)            // State 3: Letters appearing (one by one)
    {
        framesCounter++;

        if (framesCounter/10)       // Every 12 frames, one more letter!
        {
            lettersCount++;
            framesCounter = 0;
        }

        switch (lettersCount)
        {
            case 1: raylib[0] = 'r'; break;
            case 2: raylib[1] = 'a'; break;
            case 3: raylib[2] = 'y'; break;
            case 4: raylib[3] = 'l'; break;
            case 5: raylib[4] = 'i'; break;
            case 6: raylib[5] = 'b'; break;
            default: break;
        }

        // When all letters have appeared...
        if (lettersCount >= 10)
        {
            state = 4;
            framesCounter = 0;
        }
    }
    else if (state == 4)
    {
        framesCounter++;

        if (framesCounter > 100)
        {
            alpha -= 0.02f;

            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                finishScreen = 1;
            }
        }
    }
}

void Logo::draw()
{
if (state == 0)
    {
        if ((framesCounter/10)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(raylib, GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));
    }
    else if (state == 4)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(raylib, GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));

        if (framesCounter > 20) DrawText("powered by", logoPositionX, logoPositionY - 27, 20, Fade(DARKGRAY, alpha));
    }
}

void Logo::clean()
{

}

bool Logo::finished()
{
  return static_cast<bool>(this->finishScreen);
}

GameScreen Logo::switchToScreen()
{
  return GameScreen::TITLE;
}
