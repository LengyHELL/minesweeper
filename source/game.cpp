#include "game.hpp"
#include <iostream>

int Game::check_sides(const int& x, const int& y, const bool& do_bombs) {
  int counter = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int check_x = x + i;
      int check_y = y + j;
      bool self = (i == 0) && (j == 0);
      if ((check_x >= 0) && (check_x < table_width) && (check_y >= 0) && (check_y < table_height) && !self) {
        if (do_bombs && blocks[check_x][check_y].is_bomb) {
          counter++;
        }
        else if (!do_bombs && blocks[check_x][check_y].is_flag) {
          counter++;
        }
      }
    }
  }
  return counter;
}

void Game::generate(const int& x, const int& y) {
  std::vector<int> selection_array;
  int count = 0;
  for (int w = 0; w < table_width; w++) {
    for (int h = 0; h < table_height; h++) {
      if (!((w >= x - 1) && (w <= x + 1) && (h >= y - 1) && (h <= y + 1))) {
        selection_array.push_back(w);
        selection_array.push_back(h);
      }
    }
  }

  for (int b = 0; b < bombs; b++) {
    int selected = rand() % (selection_array.size() / 2);

    int selected_x = selection_array[selected * 2];
    int selected_y = selection_array[(selected * 2) + 1];

    blocks[selected_x][selected_y].is_bomb = true;

    selection_array.erase(selection_array.begin() + selected * 2, selection_array.begin() + 2 + selected * 2);
  }

  for (int i = 0; i < table_width; i++) {
    for (int j = 0; j < table_height; j++) {
      blocks[i][j].value = check_sides(i, j, true);
    }
  }
}

void Game::reveal(const int& x, const int& y) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int check_x = x + i;
      int check_y = y + j;
      bool self = (i == 0) && (j == 0);
      if ((check_x >= 0) && (check_x < table_width) && (check_y >= 0) && (check_y < table_height) && !self) {
        Block& actual = blocks[check_x][check_y];
        if (!actual.is_shown && !actual.is_bomb && !actual.is_flag) {
          actual.is_shown = true;
          if (actual.value == 0) {
            reveal(check_x, check_y);
          }
        }
      }
    }
  }
}

Game::Game(const int& position_x, const int& position_y, const int& table_width, const int& table_height, const int& bombs,
const SDL_Color& hover_color, const SDL_Color& click_color, const int& block_width)
: position_x(position_x), position_y(position_y), table_width(table_width), table_height(table_height), flags(bombs),
hover_color(hover_color), click_color(click_color), timer(0), frame_time(0), first_click(false), bombs(bombs), game_won(false), game_over(false) {
  block_size = {0, 0, block_width, block_width};
  blocks = std::vector<std::vector<Block>>(table_width, std::vector<Block>(table_height));
}

void Game::update(const Assets& assets) {
  frame_time = SDL_GetTicks() - check_timer;
  check_timer += frame_time;

  if (first_click && !game_over) {
    timer += frame_time;
  }

  int x_at_table = (int)(assets.mouse_position_x - position_x) / block_size.w;
  int y_at_table = (int)(assets.mouse_position_y - position_y) / block_size.h;

  for (int i = 0; i < table_width; i++) {
    for (int j = 0; j < table_height; j++) {
      blocks[i][j].hovered = false;
      blocks[i][j].clicked = false;
    }
  }

  if ((x_at_table >= 0) && (x_at_table < table_width) && (y_at_table >= 0) && (y_at_table < table_height) && !game_over) {
    Block& actual = blocks[x_at_table][y_at_table];
    if (!actual.is_shown) {
      bool mouse_left = assets.mouse_state == SDL_BUTTON(SDL_BUTTON_LEFT);
      bool mouse_right = assets.mouse_state == SDL_BUTTON(SDL_BUTTON_RIGHT);

      if (mouse_left) {
        if (assets.mouse_button_down) {
          if (!first_click) {
            first_click = true;
            generate(x_at_table, y_at_table);
          }
          actual.is_shown = true;
          if (actual.value == 0) {
            reveal(x_at_table, y_at_table);
          }
        }
      }
      else if (mouse_right) {
        if (assets.mouse_button_down && first_click) {
          actual.is_flag = !actual.is_flag;
        }
      }
      else {
        actual.hovered = true;
      }
    }
    else {
      bool mouse_middle = assets.mouse_state == SDL_BUTTON(SDL_BUTTON_MIDDLE);

      if (mouse_middle) {
        if (assets.mouse_button_down && (actual.value == check_sides(x_at_table, y_at_table, false))) {
          for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
              int check_x = x_at_table + i;
              int check_y = y_at_table + j;
              bool self = (i == 0) && (j == 0);
              if ((check_x >= 0) && (check_x < table_width) && (check_y >= 0) && (check_y < table_height) && !self) {
                Block& actual = blocks[check_x][check_y];
                if (!actual.is_shown && !actual.is_flag) {
                  actual.is_shown = true;
                  if (actual.value == 0) {
                    reveal(check_x, check_y);
                  }
                }
              }
            }
          }
        }
        else {
          for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
              int check_x = x_at_table + i;
              int check_y = y_at_table + j;
              bool self = (i == 0) && (j == 0);
              if ((check_x >= 0) && (check_x < table_width) && (check_y >= 0) && (check_y < table_height) && !self) {
                Block& actual = blocks[check_x][check_y];
                if (!actual.is_shown && !actual.is_flag) {
                  actual.hovered = true;
                }
              }
            }
          }
        }
      }
    }
  }
  int hidden_counter = 0;
  for (int i = 0; i < table_width; i++) {
    for (int j = 0; j < table_height; j++) {
      Block& actual = blocks[i][j];
      if (actual.is_shown && actual.is_bomb) {
        game_over = true;
        game_won = false;
      }
      else if (!actual.is_shown) {
        hidden_counter++;
      }
    }
  }
  if (hidden_counter == bombs) {
    game_over = true;
    game_won = true;
  }
  if (game_over && !game_won) {
    for (int i = 0; i < table_width; i++) {
      for (int j = 0; j < table_height; j++) {
        Block& actual = blocks[i][j];
        if (actual.is_bomb) {
          actual.is_shown = true;
        }
      }
    }
  }
}

void Game::draw(const Assets& assets) {
  for (int i = 0; i < table_width; i++) {
    for (int j = 0; j < table_height; j++) {
      Block& actual = blocks[i][j];
      SDL_Color* color = NULL;
      std::string picture = "";

      if (actual.clicked) {
        color = &click_color;
      }
      else if (actual.hovered) {
        color = &hover_color;
      }
      else {
        color = NULL;
      }

      if (actual.is_flag) {
        picture = "block_flag.png";
      }
      else if (!actual.is_shown) {
        picture = "block_hidden.png";
      }
      else if (actual.is_bomb) {
        picture = "block_bomb.png";
      }
      else {
        picture = "block_" + std::to_string(actual.value) + ".png";
      }

      assets.draw_image(picture, position_x + i * block_size.w, position_y + j * block_size.h, color, NULL, &block_size);
    }
  }
}
