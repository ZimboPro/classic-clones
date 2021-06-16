#include <spdlog/spdlog.h>
#include <raylib.h>

int main(int argc, const char** argv) {
  spdlog::info("Create window");
  InitWindow(800, 600, "test");
  spdlog::info("Window created");
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(680, 20);
    EndDrawing();
  }

  spdlog::info("Closing window");
  CloseWindow();
  
  return 0;
}