#pragma once
#include "assets.hpp"

class Button {
  int position_x;
  int position_y;
  int width;
  int height;
  std::string text;
  int text_scale;
  SDL_Color text_color;
  SDL_Color hover_color;
  SDL_Color click_color;
  bool on_mouse_down;
  bool mouse_click;
  bool mouse_hover;
  bool click_lock;

public:
  // variables
  bool selected;

  // constructor, destructor
  Button(const int& position_x, const int& position_y, const int& width, const int& height, const std::string& text,
  const int& text_scale, const SDL_Color& text_color, const SDL_Color& hover_color, const SDL_Color& click_color, const bool& on_mouse_down);
  ~Button() {}

  //functions
  void draw(const Assets& assets);
  void update(const Assets& assets);
};

class Selector {
  int position_x;
  int position_y;
  int width;
  int height;
  std::string text;
  int text_scale;
  SDL_Color text_color;
  SDL_Color hover_color;
  SDL_Color click_color;
  bool mouse_click_up;
  bool mouse_click_down;
  bool mouse_hover_up;
  bool mouse_hover_down;
  bool click_lock;
  float repeat_timer_total;
  float repeat_timer;
  int repeats;
  float ticks;
  float frame_time;

public:
  // variables
  int range_min;
  int range_max;
  int range_actual;

  // constructor, destructor
  Selector(const int& position_x, const int& position_y, const int& width, const int& height, const std::string& text,
  const int& text_scale, const SDL_Color& text_color, const SDL_Color& hover_color, const SDL_Color& click_color, const int& range_min, const int& range_max, const int& range_actual);
  ~Selector() {}

  //functions
  void draw(const Assets& assets);
  void update(const Assets& assets);
};

class Text {
  int position_x;
  int position_y;
  std::string text;
  int text_scale;
  SDL_Color text_color;

public:
  // constructor, destructor
  Text(const int& position_x, const int& position_y, const std::string& text, const int& text_scale, const SDL_Color& text_color);
  ~Text() {}

  //functions
  void draw(const Assets& assets);
};
