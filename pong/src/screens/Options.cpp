#include "Options.hpp"
#include "../Game.hpp"
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include "ScreenManager.hpp"

Options::Options()
{

}

Options::~Options()
{

}

void Options::init()
{
  this->screenFinished = false;
  this->highlighted = 0;
  int xPosLeft = GetScreenWidth() >> 2;
  int xPosRight = (GetScreenWidth() >> 2) * 3;

  this->titleLabel.setText("Options", GetScreenWidth() >> 1, GetScreenHeight() >> 2, 80, DARKGREEN);

  this->musicLabel.setText("Music", xPosLeft, GetScreenHeight() >> 1, 20, DARKGREEN);
  if (Game::playMusic)
    this->musicValue.setText("On", xPosRight, GetScreenHeight() >> 1, 20, GREEN);
  else
    this->musicValue.setText("Off", xPosRight, GetScreenHeight() >> 1, 20, GREEN);

  this->soundLabel.setText("Sound Effects", xPosLeft, (GetScreenHeight() >> 1) + 30, 20, DARKGREEN);
  if (Game::playSound)
    this->soundValue.setText("On", xPosRight, (GetScreenHeight() >> 1) + 30, 20, DARKGREEN);
  else
    this->soundValue.setText("Off", xPosRight, (GetScreenHeight() >> 1) + 30, 20, DARKGREEN);

  this->masterVolLabel.setText("Master Volume", xPosLeft, (GetScreenHeight() >> 1) + 60, 20, DARKGREEN);
  this->masterVolValue.setText(fmt::format("{} %", Game::masterVol), xPosRight, (GetScreenHeight() >> 1) + 60, 20, DARKGREEN);
  this->musicVolLabel.setText("Music Volume", xPosLeft, (GetScreenHeight() >> 1) + 90, 20, DARKGREEN);
  this->musicVolValue.setText(fmt::format("{} %", Game::musicVol), xPosRight, (GetScreenHeight() >> 1) + 90, 20, DARKGREEN);
  this->soundVolLabel.setText("Sound Volume", xPosLeft, (GetScreenHeight() >> 1) + 120, 20, DARKGREEN);
  this->soundVolValue.setText(fmt::format("{} %", Game::soundVol), xPosRight, (GetScreenHeight() >> 1) + 120, 20, DARKGREEN);
  this->back.setText("Back", GetScreenWidth() >> 1, (GetScreenHeight() >> 1) + 150, 20, DARKGREEN);
}

void Options::update()
{
  if (IsKeyPressed(KEY_UP))
    this->highlighted--;
  if (IsKeyPressed(KEY_DOWN))
    this->highlighted++;
  if (this->highlighted < 0)
    this->highlighted = 0;
  if (this->highlighted > 5)
    this->highlighted = 5;

  this->musicValue.setColor(DARKGREEN);
  this->soundValue.setColor(DARKGREEN);
  this->masterVolValue.setColor(DARKGREEN);
  this->musicVolValue.setColor(DARKGREEN);
  this->soundVolValue.setColor(DARKGREEN);
  this->back.setColor(DARKGREEN);

  switch (this->highlighted)
  {
  case 0:
    this->musicValue.setColor(GREEN);
    break;
  case 1:
    this->soundValue.setColor(GREEN);
    break;
  case 2:
    this->masterVolValue.setColor(GREEN);
    break;
  case 3:
    this->musicVolValue.setColor(GREEN);
    break;
  case 4:
    this->soundVolValue.setColor(GREEN);
    break;
  default:
    this->back.setColor(GREEN);
    break;
  }

  if (IsKeyPressed(KEY_LEFT))
  {
    switch (this->highlighted)
    {
    case 0:
      Game::playMusic = false;
      StopMusicStream(Game::music);
      this->musicValue.setText("Off");
      Game::setBoolStorageValue(StorageEnum::MusicSound, Game::playMusic);
      break;
    case 1:
      Game::playSound = false;
      this->soundValue.setText("Off");
      Game::setBoolStorageValue(StorageEnum::FxSound, Game::playSound);
      break;
    case 2:
      Game::masterVol -= 10.0f;
      if (Game::masterVol < 0.0f)
        Game::masterVol = 0.0f;
      SetMasterVolume(Game::masterVol);
      this->masterVolValue.setText(fmt::format("{} %", Game::masterVol));
      if (Game::playSound)
        PlaySound(Game::fxCoin);
      Game::setFloatStorageValue(StorageEnum::MasterVol, Game::masterVol);
      break;
    case 3:
      Game::musicVol -= 10.0f;
      if (Game::musicVol < 0.0f)
        Game::musicVol = 0.0f;
      SetMusicVolume(Game::music, Game::musicVol);
      this->musicVolValue.setText(fmt::format("{} %", Game::musicVol));
      Game::setFloatStorageValue(StorageEnum::MusicSound, Game::musicVol);
      break;
    case 4:
      Game::soundVol -= 10.0f;
      if (Game::soundVol < 0.0f)
        Game::soundVol = 0.0f;
      SetSoundVolume(Game::fxCoin, Game::soundVol);
      if (Game::playSound)
        PlaySound(Game::fxCoin);
      this->soundVolValue.setText(fmt::format("{} %", Game::soundVol));
      Game::setFloatStorageValue(StorageEnum::FXVol, Game::soundVol);
      break;
    }
  }
  if (IsKeyPressed(KEY_RIGHT))
  {
    switch (this->highlighted)
    {
    case 0:
      Game::playMusic = true;
      if (!IsMusicPlaying(Game::music))
        PlayMusicStream(Game::music);
      this->musicValue.setText("On");
      Game::setBoolStorageValue(StorageEnum::MusicSound, Game::playMusic);
      break;
    case 1:
      Game::playSound = true;
      this->soundValue.setText("On");
      Game::setBoolStorageValue(StorageEnum::FxSound, Game::playSound);
      break;
    case 2:
      Game::masterVol += 10.0f;
      if (Game::masterVol > 100.0f)
        Game::masterVol = 100.0f;
      SetMasterVolume(Game::masterVol);
      if (Game::playSound)
        PlaySound(Game::fxCoin);
      this->masterVolValue.setText(fmt::format("{} %", Game::masterVol));
      Game::setFloatStorageValue(StorageEnum::MasterVol, Game::masterVol);
      break;
    case 3:
      Game::musicVol += 10.0f;
      if (Game::musicVol > 100.0f)
        Game::musicVol = 100.0f;
      SetMusicVolume(Game::music, Game::musicVol);
      this->musicVolValue.setText(fmt::format("{} %", Game::musicVol));
      Game::setFloatStorageValue(StorageEnum::MusicSound, Game::musicVol);
      break;
    case 4:
      Game::soundVol += 10.0f;
      if (Game::soundVol > 100.0f)
        Game::soundVol = 100.0f;
      SetSoundVolume(Game::fxCoin, Game::soundVol);
      if (Game::playSound)
        PlaySound(Game::fxCoin);
      this->soundVolValue.setText(fmt::format("{} %", Game::soundVol));
      Game::setFloatStorageValue(StorageEnum::FXVol, Game::soundVol);
      break;
    }
  }

  if (IsKeyPressed(KEY_ESCAPE) || (IsKeyPressed(KEY_ENTER) && this->highlighted == 5)) {
    this->screenFinished = true;
    ScreenManager::navigateBack();
  }
}

void Options::draw()
{
  this->titleLabel.render();
  this->musicLabel.render();
  this->musicValue.render();
  this->soundLabel.render();
  this->soundValue.render();

  this->masterVolLabel.render();
  this->masterVolValue.render();
  this->musicVolLabel.render();
  this->musicVolValue.render();
  this->soundVolLabel.render();
  this->soundVolValue.render();

  this->back.render();

}

void Options::clean()
{

}


GameScreen Options::switchToScreen()
{
  return this->screen;
}
