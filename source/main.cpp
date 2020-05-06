#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "assets.hpp"
int main(int argc, char *argv[]) {
  Assets assets(100, 100, "lhll.ttf", "images");
  SDL_Color color = {255, 255, 255, 0};
  int ticks;
  while(true) {
    ticks = SDL_GetTicks();
    for (int i = 0; i < 10000; i++) {
      //assets.draw_text("test", 1, color, 0, 0);
      assets.draw_image("red_cube.png", 1, 10, 10);
    }
    assets.render();
    std::cout << "\r" << SDL_GetTicks() - ticks << "     ";
  }

  return 0;
}
