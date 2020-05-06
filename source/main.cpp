#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "assets.hpp"
int main(int argc, char *argv[]) {
  Assets assets(600, 400, "lhll.ttf", "images");
  SDL_Color color = {255, 255, 255, 0};
  int ticks;
  std::string x, y, b;
  int fps = 60;
  while(!assets.exit) {
    ticks = SDL_GetTicks();
    x = std::to_string(assets.mouse_position_x);
    y = std::to_string(assets.mouse_position_y);
    b = "none";
    if (assets.mouse_state == SDL_BUTTON(SDL_BUTTON_LEFT)) {
      b = "left";
    }
    if (assets.mouse_state == SDL_BUTTON(SDL_BUTTON_RIGHT)) {
      b = "right";
    }
    if (assets.mouse_state == SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
      b = "middle";
    }
    assets.update_inputs();
    assets.render();
    assets.draw_text(x + ", " + y + " - " + b, 1, color, 0, 0);

    if ((SDL_GetTicks() - ticks) < (1000 / fps)) {
      SDL_Delay((1000 / fps) - (SDL_GetTicks() - ticks));
    }
  }

  return 0;
}
