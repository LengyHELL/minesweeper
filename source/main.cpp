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

  Assets assets(240, 400, "lhll.ttf", 16, "images");

  Menu select_difficulty(0, 0, 240, 400);
  select_difficulty.texts.insert(std::make_pair("title", Text(10, 30, "Select difficulty", 2, tc)));

  select_difficulty.buttons.insert(std::make_pair("easy", Button(10, 70, 220, 30, "Easy", 1, tc, hc, cc, false)));
  select_difficulty.buttons.insert(std::make_pair("medium", Button(10, 110, 220, 30, "Medium", 1, tc, hc, cc, false)));
  select_difficulty.buttons.insert(std::make_pair("hard", Button(10, 150, 220, 30, "Hard", 1, tc, hc, cc, false)));
  select_difficulty.buttons.insert(std::make_pair("custom", Button(155, 190, 75, 164, "Custom", 1, tc, hc, cc, false)));

  select_difficulty.selectors.insert(std::make_pair("width", Selector(10, 190, 135, 48, "Width", 1, tc, hc, cc, 9, 70, 9)));
  select_difficulty.selectors.insert(std::make_pair("height", Selector(10, 248, 135, 48, "Height", 1, tc, hc, cc, 9, 40, 9)));
  select_difficulty.selectors.insert(std::make_pair("bombs", Selector(10, 306, 135, 48, "Bombs", 1, tc, hc, cc, 1, 999, 10)));

  Menu gui(0, 0, 600, 400);

  Game game(250, 80, 9, 9, 10, hc, cc, 24);

  float ticks = 0;
  float frame_time;
  float fps = 0;
  float fps_cap = 60;

  std::string state = "select_difficulty";

  int block_width = 24;

  while(!assets.exit) {
    assets.update_inputs();

    if (state == "select_difficulty") {
      select_difficulty.update(assets);
      select_difficulty.draw(assets);

      int selected_width = select_difficulty.selectors.at("width").range_actual;
      int selected_height = select_difficulty.selectors.at("height").range_actual;
      int selected_bombs = select_difficulty.selectors.at("bombs").range_actual;

      select_difficulty.selectors.at("bombs").range_max = (selected_width * selected_height - 1);

      bool selected = true;
      if (select_difficulty.buttons.at("easy").selected) {
        game = Game(10, 50, 9, 9, 10, hc, cc, block_width);
      }
      else if (select_difficulty.buttons.at("medium").selected) {
        game = Game(10, 50, 16, 16, 40, hc, cc, block_width);;
      }
      else if (select_difficulty.buttons.at("hard").selected) {
        game = Game(10, 50, 30, 16, 99, hc, cc, block_width);;
      }
      else if (select_difficulty.buttons.at("custom").selected) {
        game = Game(10, 50, selected_width, selected_height, selected_bombs, hc, cc, block_width);
      }
      else {
        selected = false;
      }

      if (selected) {
        state = "game";
        int window_width = (game.get_width() * block_width) + 20;
        int window_height = (game.get_height() * block_width) + 130;
        gui = Menu(0, 0, window_width, window_height);
        gui.buttons.insert(std::make_pair("restart", Button(10, 10, 100, 30, "Restart", 1, tc, hc, cc, false)));
        gui.buttons.insert(std::make_pair("new_game", Button(window_width - 110, 10, 100, 30, "New game", 1, tc, hc, cc, false)));
        gui.texts.insert(std::make_pair("timer", Text(20, window_height - 60, "Time:", 1, tc)));
        gui.texts.insert(std::make_pair("flags", Text(20, window_height - 30, "Flags:", 1, tc)));
        assets.resize_window(window_width, window_height);
      }
    }
    else if (state == "game") {
      gui.update(assets);
      game.update(assets);
      gui.draw(assets);
      game.draw(assets);

      gui.texts.at("timer").text = "Time: " + std::to_string((int)game.get_timer() / 1000);
      gui.texts.at("flags").text = "Flags: " + std::to_string(game.get_flags());

      if (gui.buttons.at("restart").selected) {
        game = Game(10, 50, game.get_width(), game.get_height(), game.get_bombs(), hc, cc, block_width);
      }
      else if (gui.buttons.at("new_game").selected) {
        state = "select_difficulty";
        assets.resize_window(240, 400);
      }
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
