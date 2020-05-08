#pragma once
#include "assets.hpp"
#include "controls.hpp"

class Menu {
  int position_x;
  int position_y;
  int width;
  int height;

public:
  // elements
  std::map<std::string, Button> buttons;
  std::map<std::string, Selector> selectors;
  std::map<std::string, Text> texts;

  // constructor ,destructor
  Menu(const int& position_x, const int& position_y, const int& width, const int& height);
  ~Menu() {}

  // functions
  void update(const Assets& assets);
  void draw(const Assets& assets);
};
