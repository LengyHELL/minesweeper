#include "menu.hpp"

Menu::Menu(const int& position_x, const int& position_y, const int& width, const int& height)
: position_x(position_x), position_y(position_y), width(width), height(height) {}

void Menu::update(const Assets& assets) {
  for (auto& b : buttons) {
    b.second.update(assets);
  }
  for (auto& s : selectors) {
    s.second.update(assets);
  }
}

void Menu::draw(const Assets& assets) {
  SDL_Rect area;
  SDL_Rect size{0, 0, width, height};
  SDL_Rect corner_size{0, 0, 3, 3};
  SDL_Rect vertical_size{0, 0, corner_size.w, size.h - corner_size.h * 2};
  SDL_Rect horizontal_size{0, 0, size.w - corner_size.w * 2, corner_size.h};
  assets.draw_image("button_body.png", position_x, position_y, NULL, NULL, &size);
  assets.draw_image("menu_corner_top_left.png", position_x, position_y, NULL, &area, &corner_size);
  assets.draw_image("menu_side_top.png", area.x + area.w, area.y, NULL, &area, &horizontal_size);
  assets.draw_image("menu_corner_top_right.png", area.x + area.w, area.y, NULL, &area, &corner_size);
  assets.draw_image("menu_side_right.png", area.x, area.y + area.h, NULL, &area, &vertical_size);
  assets.draw_image("menu_corner_bottom_right.png", area.x, area.y + area.h, NULL, &area, &corner_size);
  assets.draw_image("menu_side_bottom.png", area.x - horizontal_size.w, area.y, NULL, &area, &horizontal_size);
  assets.draw_image("menu_corner_bottom_left.png", area.x - corner_size.w, area.y, NULL, &area, &corner_size);
  assets.draw_image("menu_side_left.png", area.x, area.y - vertical_size.h, NULL, NULL, &vertical_size);

  for (auto& b : buttons) {
    b.second.draw(assets);
  }
  for (auto& s : selectors) {
    s.second.draw(assets);
  }
  for (auto& t : texts) {
    t.second.draw(assets);
  }
}
