#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "menu.hpp"

int main(int argc, char *argv[]) {
  SDL_Color tc{60, 60, 60, 0};
  SDL_Color hc{125, 125, 125, 0};
  SDL_Color cc{125, 255, 125, 0};

  Assets assets(600, 400, "lhll.ttf", 16, "images");

  Menu select_difficulty(5, 20, 590, 360);
  select_difficulty.buttons.insert(std::make_pair("easy", Button(20, 80, 200, 40, "Easy", 1, tc, hc, cc, true)));
  select_difficulty.buttons.insert(std::make_pair("medium", Button(20, 130, 200, 40, "Medium", 1, tc, hc, cc, false)));
  select_difficulty.selectors.insert(std::make_pair("width", Selector(20, 180, 125, 40, "Width", 1, tc, hc, cc, 10, 100, 30)));
  select_difficulty.texts.insert(std::make_pair("title", Text(20, 30, "Select difficulty", 2, tc)));

  float ticks = 0;
  float frame_time;
  float fps = 0;
  float fps_cap = 60;

  while(!assets.exit) {
    assets.update_inputs();

    for (int i = 0; i < 100; i++) {
      select_difficulty.update(assets);
      select_difficulty.draw(assets);
    }

    assets.render();

    frame_time = SDL_GetTicks() - ticks;
    ticks += frame_time;
    if (frame_time < (1000 / fps_cap)) {
      SDL_Delay((1000 / fps_cap) - frame_time);
    }
    assets.draw_text(std::to_string((int)(1000 / frame_time)) + " fps", 0, 0, tc);
  }

  return 0;
}
