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
static void ChangeToScreen(int screen);     // No transition effect

static void TransitionToScreen(int screen);
static void UpdateTransition(void);
static void DrawTransition(void);

static void UpdateDrawFrame(void);          // Update and Draw one frame

static Logo logo;
static Title title;
static Menu menu;
static GamePlay gamePlay;
static Ending end;
static Options options;

int main(int argc, char const *argv[])
{
  Game game;
  game.init();

  InitAudioDevice();

  spdlog::info("Load font");
  // Game::font = LoadFont("assets/mecha.png");
  spdlog::info("Load music");
  Game::music = LoadMusicStream("assets/ambient.ogg");
  spdlog::info("Load sound");
  Game::fxCoin = LoadSound("assets/coin.wav");
  SetSoundVolume(Game::fxCoin, 0.4f);

  spdlog::info("Play music");
  SetMusicVolume(Game::music, 0.4f);
  PlayMusicStream(Game::music);

  // Setup and Init first screen
  Game::currentScreen = TITLE;
  spdlog::info("Init Logo");
  // logo.init();
  title.init();

  SetExitKey(KEY_NULL);

  while (game.isRunning() && Game::currentScreen != GameScreen::EXIT)
  {
    UpdateDrawFrame();
  }
  spdlog::info("Start clean up");

  switch (Game::currentScreen)
    {
        case LOGO: logo.clean(); break;
        case TITLE: title.clean(); break;
        case MENU: menu.clean(); break;
        case GAMEPLAY: gamePlay.clean(); break;
        case ENDING: end.clean(); break;
        default: break;
    }

    // Unload all global loaded data (i.e. fonts) here!
    // UnloadFont(Game::font);
    UnloadMusicStream(Game::music);
    UnloadSound(Game::fxCoin);

    CloseAudioDevice();     // Close audio context

  game.clean();

  return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------

// Change to next screen, no transition
static void ChangeToScreen(int screen)
{
    // Unload current screen
    switch (Game::currentScreen)
    {
        case LOGO: logo.clean(); break;
        case TITLE: title.clean(); break;
        case MENU: menu.clean(); break;
        case GAMEPLAY: gamePlay.clean(); break;
        case ENDING: end.clean(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: logo.init(); break;
        case TITLE: title.init(); break;
        case MENU: menu.init(); break;
        case GAMEPLAY: gamePlay.init(); break;
        case ENDING: end.init(); break;
        default: break;
    }

    Game::currentScreen = static_cast<GameScreen>(screen);
}

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
            switch (transFromScreen)
            {
                case LOGO: logo.clean(); break;
                case TITLE: title.clean(); break;
                case OPTIONS: options.clean(); break;
                case MENU: menu.clean(); break;
                case GAMEPLAY: gamePlay.clean(); break;
                case ENDING: end.clean(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: logo.init(); break;
                case TITLE: title.init(); break;
                case MENU: menu.init(); break;
                case GAMEPLAY: gamePlay.init(); break;
                case ENDING: end.init(); break;
                default: break;
            }

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
    UpdateMusicStream(Game::music);       // NOTE: Game::music keeps playing between screens

    if (!onTransition)
    {
        switch(Game::currentScreen)
        {
            case LOGO:
            {
                logo.update();

                if (logo.finished()) TransitionToScreen(logo.switchToScreen());

            } break;
            case TITLE:
            {
                title.update();

                if (title.finished()) TransitionToScreen(title.switchToScreen());

            } break;
            case OPTIONS:
            {
                options.update();

                if (options.finished()) TransitionToScreen(options.switchToScreen());

            } break;
            case MENU:
            {
                menu.update();

                if (menu.finished()) TransitionToScreen(menu.switchToScreen());

            } break;
            case GAMEPLAY:
            {
                gamePlay.update();

                if (gamePlay.finished()) TransitionToScreen(gamePlay.switchToScreen());
                //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);

            } break;
            case ENDING:
            {
                end.update();

                if (end.finished()) TransitionToScreen(end.switchToScreen());

            } break;
            default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        switch(Game::currentScreen)
        {
            case LOGO: logo.draw(); break;
            case TITLE: title.draw(); break;
            case OPTIONS: options.draw(); break;
            case MENU: menu.draw(); break;
            case GAMEPLAY: gamePlay.draw(); break;
            case ENDING: end.draw(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
