#pragma once
#include "assets.hpp"
#include "game.hpp"

class Menu {
  int position_x;
  int position_y;
  int width;
  int height;

public:
  Map<std::string, Button> buttons;
  Map<std::string, Selector> selectors;
  Map<std::string, Text> texts;

  // functions
  void set_select_game(const Assets& assets);
  void update(const Assets& assets);
  void draw(const Assets& assets);
};
