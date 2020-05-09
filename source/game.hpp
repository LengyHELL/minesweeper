#pragma once

#include <vector>

#include "assets.hpp"

struct Block {
  Block() : is_bomb(false), is_flag(false), is_shown(false), hovered(false), clicked(false) {}
  ~Block() {}
  bool is_bomb;
  bool is_flag;
  bool is_shown;
  bool hovered;
  bool clicked;
  int value;
};

class Game {
  int flags;
  int table_width;
  int table_height;
  int position_x;
  int position_y;
  std::vector<std::vector<Block>> blocks;
  float timer;
  float check_timer;
  float frame_time;
  SDL_Rect block_size;
  SDL_Color hover_color;
  SDL_Color click_color;
  bool first_click;
  int bombs;
  bool game_over;
  bool game_won;

  int check_sides(const int& x, const int& y, const bool& do_bombs);
  void generate(const int& x, const int& y);
  void reveal(const int& x, const int& y);

public:
  // constructor, destructor
  Game(const int& position_x, const int& position_y, const int& table_width, const int& table_height, const int& bombs, const SDL_Color& hover_color, const SDL_Color& click_color, const int& block_width);
  ~Game() {}

  // functions
  void update(const Assets& assets);
  void draw(const Assets& assets);

  // getters
  float get_timer() const { return timer; }
  int get_flags() const { return flags; }
  int get_width() const { return table_width; }
  int get_height() const { return table_height; }
  int get_bombs() const { return bombs; }
};
