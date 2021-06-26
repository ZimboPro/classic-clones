#ifndef __TEXTHELPER_H__
#define __TEXTHELPER_H__

#include <string>
#include <raylib.h>

class TextHelper
{
private:
public:
  static void DrawTextPos(const std::string & text, int x, int y, int size, Color textColor);
  static void DrawTextPos(const char * text, int x, int y, int size, Color textColor);
  static Vector2 adjustedPosition(const std::string & text, int x, int y, int size);
  static Vector2 adjustedPosition(const char * text, int x, int y, int size);
};


#endif // __TEXTHELPER_H__
