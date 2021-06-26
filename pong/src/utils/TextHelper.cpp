#include "TextHelper.hpp"

void TextHelper::DrawTextPos(const std::string & text, int x, int y, int size, Color textColor)
{
  DrawTextPos(text.c_str(), x, y, size, textColor);
}

void TextHelper::DrawTextPos(const char * text, int x, int y, int size, Color textColor)
{
  int adjustToLeft = MeasureText(text, size) >> 1;
  int adjustToTop = size >> 1;
  DrawText(text, x - adjustToLeft, y - adjustToTop, size, textColor);
}

Vector2 TextHelper::adjustedPosition(const std::string & text, int x, int y, int size)
{
  return adjustedPosition(text.c_str(), x, y, size);
}

Vector2 TextHelper::adjustedPosition(const char * text, int x, int y, int size)
{
  Vector2 temp;
  temp.x = x - (MeasureText(text, size) >> 1);
  temp.y = y - (size >> 1);
  return temp;
}
