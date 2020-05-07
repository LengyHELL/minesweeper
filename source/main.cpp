#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "assets.hpp"
int main(int argc, char *argv[]) {
  Assets assets(600, 400, "lhll.ttf", 24, "images");
  SDL_Color color = {255, 255, 255, 0};
  int ticks;
  std::string x, y, b;
  int fps = 60;
  SDL_Color tc{255, 255, 255, 0};
  SDL_Color hc{125, 125, 125, 0};
  Button button(10, 20, 200, 50, "Hello", 1, tc, hc);
  while(!assets.exit) {
    ticks = SDL_GetTicks();
    assets.update_inputs();

    button.update_button(assets);
    button.draw_button(assets);

    if (button.selected) {
      std::cout << "press" << std::endl;
    }

    assets.render();
    if ((SDL_GetTicks() - ticks) < (1000 / fps)) {
      SDL_Delay((1000 / fps) - (SDL_GetTicks() - ticks));
    }
  }

  return 0;
}
