#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <time.h>

#include "menu.hpp"
#include "game.hpp"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  SDL_Color tc{60, 60, 60, 0};
  SDL_Color hc{125, 125, 125, 0};
  SDL_Color cc{125, 255, 125, 0};

  Assets assets(600, 400, "lhll.ttf", 16, "images");

  Menu select_difficulty(5, 20, 590, 360);
  select_difficulty.buttons.insert(std::make_pair("restart", Button(20, 80, 200, 40, "Restart", 1, tc, hc, cc, false)));
  select_difficulty.buttons.insert(std::make_pair("medium", Button(20, 130, 200, 40, "Test", 1, tc, hc, cc, true)));
  select_difficulty.selectors.insert(std::make_pair("width", Selector(20, 180, 125, 40, "Width", 1, tc, hc, cc, 10, 100, 30)));
  select_difficulty.texts.insert(std::make_pair("title", Text(20, 30, "Select difficulty", 2, tc)));

  Game game(250, 80, 9, 9, 10, hc, cc, 24);


  float ticks = 0;
  float frame_time;
  float fps = 0;
  float fps_cap = 60;

  while(!assets.exit) {
    assets.update_inputs();

    game.update(assets);

    select_difficulty.update(assets);
    select_difficulty.draw(assets);
    game.draw(assets);

    if (select_difficulty.buttons.at("restart").selected) {
      game = Game(250, 80, 9, 9, 10, hc, cc, 24);
    }

    assets.render();

    frame_time = SDL_GetTicks() - ticks;
    ticks += frame_time;
    if (frame_time < (1000 / fps_cap)) {
      SDL_Delay((1000 / fps_cap) - frame_time);
    }
    assets.draw_text(std::to_string((int)(1000 / frame_time)) + " fps ," + std::to_string((int)game.get_timer() / 1000) + " sec", 0, 0, tc);
  }

  return 0;
}
