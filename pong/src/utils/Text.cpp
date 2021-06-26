#include "Text.hpp"
#include "TextHelper.hpp"
#include <spdlog/spdlog.h>

Text::Text()
{
  this->x = 0;
  this->y = 0;
  this->initX = 0;
  this->initY = 0;
  this->scaling = false;
}

Text::~Text()
{

}

void Text::setText(const std::string & str, int x, int y, int size, Color color)
{
  this->text = str;
  this->initX = x;
  this->initY = y;
  this->size = size;
  this->color = color;
  this->calcPos(this->initX, this->initY);
}

void Text::setText(const char * str, int x, int y, int size, Color color)
{
  this->text = std::string(str);
  this->initX = x;
  this->initY = y;
  this->size = size;
  this->color = color;
  this->calcPos(this->initX, this->initY);
}

void Text::setText(const std::string & str)
{;
  this->text = str;
  this->calcPos(this->initX, this->initY);
}

void Text::setText(const char * str)
{
  this->text = std::string(str);
  this->calcPos(this->initX, this->initY);
}

void Text::updatePos(int x, int y)
{
  this->initX = x;
  this->initY = y;
  this->calcPos(x, y);
}

void Text::setColor(Color color)
{
  this->color = color;
}

void Text::setSize(int size)
{
  this->size = size;
  this->calcPos(this->initX, this->initY);
}

void Text::render()
{
  DrawText(this->text.c_str(), this->x, this->y, this->size, this->color);
}

bool Text::scale(float duration, int startSize, int endSize)
{
  if (!scaling) {
    this->startScale = GetTime();
    this->setSize(startSize);
    this->scaling = true;
  } else {
    double timeDiff = GetTime() - this->startScale;
    if (timeDiff >= duration) {
      this->scaling = false;
      this->setSize(endSize);
    } else {
      float rate = static_cast<float>(startSize - endSize) / duration;
      int size = static_cast<int>(rate * timeDiff);
      this->setSize(startSize - size);
    }
  }
  return !this->scaling;
}

void Text::calcPos(int x, int y)
{
  Vector2 temp = TextHelper::adjustedPosition(this->text, x, y, this->size);
  this->x = temp.x;
  this->y = temp.y;
}
