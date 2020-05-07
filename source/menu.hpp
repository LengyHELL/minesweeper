#pragma once
#include "assets.hpp"
#include "game.hpp"

class Menu {
  int menu_position_x;
  int menu_position_y;
  int menu_width;
  int menu_height;

public:
  Map<std::string, Button> buttons;
  Map<std::string, Selector> selectors;
  Map<std::string, Text> texts;

  // functions
  void set_select_game(const Assets& assets);
  void update_menu(const Assets& assets);
  void draw_menu(const Assets& assets);
};
