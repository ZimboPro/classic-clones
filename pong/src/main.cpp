#include "Game.hpp"
#include "AI.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include <raylib.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include "screens/Logo.hpp"
#include "screens/Title.hpp"
#include "screens/Menu.hpp"
#include "screens/GamePlay.hpp"
#include "screens/Options.hpp"
#include "screens/Ending.hpp"
#include "screens/Pause.hpp"
#include "screens/ScreenManager.hpp"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 600;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;

// NOTE: Some global variables that require to be visible for all screens,
// are defined in screens.h (i.e. Game::currentScreen)

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------

static void TransitionToScreen(int screen);
static void UpdateTransition(void);
static void DrawTransition(void);

static void UpdateDrawFrame(void);          // Update and Draw one frame


int main(int argc, char const *argv[])
{
  Game::init();
  Game::createScreens();

  // Setup and Init first screen
  ScreenManager::setCurrent(LOGO);
  spdlog::info("Init Logo");
  // logo.init();
  ScreenManager::getCurrentScreen()->init();


  while (Game::isRunning() && ScreenManager::currentScreen() != GameScreen::EXIT)
  {
    UpdateDrawFrame();
  }
  spdlog::info("Start clean up");
  ScreenManager::getCurrentScreen()->clean();

  Game::clean();

  return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------

// Define transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = Game::currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            Game::screens[transFromScreen]->clean();

            // Load next screen
            Game::screens[transToScreen]->init();

            Game::currentScreen = static_cast<GameScreen>(transToScreen);

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (Game::playMusic)
      UpdateMusicStream(Game::music);       // NOTE: Game::music keeps playing between screens

    // if (!onTransition)
    // {
      ScreenManager::getCurrentScreen()->update();
    //   if (ScreenManager::getCurrentScreen()->finished()) {
    //     TransitionToScreen(ScreenManager::getCurrentScreen()->switchToScreen());
    //   }
    // }
    // else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        ScreenManager::render();

        // Draw full screen rectangle in front of everything
        // if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
