#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "assets.hpp"
int main(int argc, char *argv[]) {
  Assets assets(600, 400, "lhll.ttf", 20, "images");

  float ticks = 0;
  float frame_time;
  float fps = 0;
  float fps_cap = 60;

  SDL_Color tc{255, 255, 255, 0};
  SDL_Color hc{125, 125, 125, 0};
  SDL_Color cc{125, 255, 125, 0};
  Button button(10, 50, 200, 40, "G", 1, tc, hc, cc, true);
  Button button2(10, 110, 200, 40, "N", 1, tc, hc, cc, false);

  Selector selector(10, 170, 200, 40, "Select", 1, tc, hc, cc, 0, 100, 50);

  while(!assets.exit) {
    assets.update_inputs();

    button.update(assets);
    button.draw(assets);

    button2.update(assets);
    button2.draw(assets);

    selector.update(assets);
    selector.draw(assets);

    assets.render();

    frame_time = SDL_GetTicks() - ticks;
    ticks += frame_time;
    if (frame_time < (1000 / fps_cap)) {
      SDL_Delay((1000 / fps_cap) - frame_time);
    }
    assets.draw_text(std::to_string((int)(1000 / frame_time)) + " fps" + std::to_string(button2.selected), 0, 0, tc);
  }

  return 0;
}
