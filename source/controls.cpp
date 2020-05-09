#include "controls.hpp"

// Button

Button::Button(const int& position_x, const int& position_y, const int& width, const int& height, const std::string& text, const int& text_scale,
const SDL_Color& text_color, const SDL_Color& hover_color, const SDL_Color& click_color, const bool& on_mouse_down)
: position_x(position_x), position_y(position_y), width(width), height(height), text(text), text_scale(text_scale), text_color(text_color),
hover_color(hover_color), click_color(click_color), on_mouse_down(on_mouse_down), selected(false), click_lock(true) {}

void Button::draw(const Assets& assets) {
  SDL_Color* color = NULL;
  if (mouse_click) {
    color = &click_color;
  }
  else if (mouse_hover) {
    color = &hover_color;
  }

  SDL_Rect area;
  SDL_Rect size{0, 0, width, height};
  SDL_Rect corner_size{0, 0, 3, 3};
  SDL_Rect vertical_size{0, 0, corner_size.w, size.h - corner_size.h * 2};
  SDL_Rect horizontal_size{0, 0, size.w - corner_size.w * 2, corner_size.h};
  assets.draw_image("button_body.png", position_x, position_y, color, NULL, &size);
  assets.draw_image("button_corner_top_left.png", position_x, position_y, color, &area, &corner_size);
  assets.draw_image("button_side_top.png", area.x + area.w, area.y, color, &area, &horizontal_size);
  assets.draw_image("button_corner_top_right.png", area.x + area.w, area.y, color, &area, &corner_size);
  assets.draw_image("button_side_right.png", area.x, area.y + area.h, color, &area, &vertical_size);
  assets.draw_image("button_corner_bottom_right.png", area.x, area.y + area.h, color, &area, &corner_size);
  assets.draw_image("button_side_bottom.png", area.x - horizontal_size.w, area.y, color, &area, &horizontal_size);
  assets.draw_image("button_corner_bottom_left.png", area.x - corner_size.w, area.y, color, &area, &corner_size);
  assets.draw_image("button_side_left.png", area.x, area.y - vertical_size.h, color, NULL, &vertical_size);

  int scaled_font_size = assets.default_font_size * text_scale;
  int text_position_x = position_x + (int)scaled_font_size / 2;
  int text_position_y = position_y + (int)(height - scaled_font_size) / 2;
  assets.draw_text(text, text_position_x, text_position_y, text_color, NULL, text_scale);
}

void Button::update(const Assets& assets) {
  bool x_in_range = (assets.mouse_position_x >= position_x) && (assets.mouse_position_x <= (position_x + width));
  bool y_in_range = (assets.mouse_position_y >= position_y) && (assets.mouse_position_y <= (position_y + height));
  mouse_hover = x_in_range && y_in_range;

  bool mouse_right = assets.mouse_state == SDL_BUTTON(SDL_BUTTON_LEFT);
  if (!mouse_right) {
    click_lock = false;
  }
  if (!mouse_hover && mouse_right) {
    click_lock = true;
  }
  mouse_click = mouse_hover && mouse_right && !click_lock;

  if (on_mouse_down) {
    selected = mouse_click && assets.mouse_button_down;
  }
  else {
    selected = mouse_click && assets.mouse_button_up;
  }
}



// Selector

Selector::Selector(const int& position_x, const int& position_y, const int& width, const int& height, const std::string& text, const int& text_scale,
const SDL_Color& text_color, const SDL_Color& hover_color, const SDL_Color& click_color, const int& range_min, const int& range_max, const int& range_actual)
: position_x(position_x), position_y(position_y), width(width), height(height), text(text), text_scale(text_scale), text_color(text_color),
hover_color(hover_color), click_color(click_color), range_min(range_min), range_max(range_max), range_actual(range_actual), click_lock(true),
repeat_timer_total(1000), repeat_timer(0), repeats(1) {}

void Selector::draw(const Assets& assets) {
  int scaled_font_size = assets.default_font_size * text_scale;
  SDL_Color* color_up = NULL;
  SDL_Color* color_down = NULL;
  if (mouse_click_up) {
    color_up = &click_color;
  }
  else if (mouse_hover_up) {
    color_up = &hover_color;
  }
  if (mouse_click_down) {
    color_down = &click_color;
  }
  else if (mouse_hover_down) {
    color_down = &hover_color;
  }

  SDL_Rect area;
  SDL_Rect size{0, 0, width, height};
  SDL_Rect button_size{0, 0, (int)height / 2, (int)height / 2};
  SDL_Rect corner_size{0, 0, 3, 3};
  SDL_Rect vertical_size{0, 0, corner_size.w, size.h - corner_size.h * 2};
  SDL_Rect horizontal_size{0, 0, size.w - (corner_size.w + button_size.w), corner_size.h};
  assets.draw_image("button_body.png", position_x, position_y, NULL, NULL, &size);
  assets.draw_image("button_corner_top_left.png", position_x, position_y, NULL, &area, &corner_size);
  assets.draw_image("button_side_top.png", area.x + area.w, area.y, NULL, &area, &horizontal_size);
  assets.draw_image("button_corner_top_right.png", area.x + area.w, area.y, NULL, &area, &corner_size);

  assets.draw_image("selector_arrow_up.png", area.x + area.w, area.y, color_up, NULL, &button_size);
  assets.draw_image("selector_arrow_down.png", area.x + area.w, area.y + button_size.h, color_down, NULL, &button_size);

  assets.draw_image("button_side_right.png", area.x, area.y + area.h, NULL, &area, &vertical_size);
  assets.draw_image("button_corner_bottom_right.png", area.x, area.y + area.h, NULL, &area, &corner_size);
  assets.draw_image("button_side_bottom.png", area.x - horizontal_size.w, area.y, NULL, &area, &horizontal_size);
  assets.draw_image("button_corner_bottom_left.png", area.x - corner_size.w, area.y, NULL, &area, &corner_size);
  assets.draw_image("button_side_left.png", area.x, area.y - vertical_size.h, NULL, NULL, &vertical_size);

  int text_position_x = position_x + (int)scaled_font_size / 2;
  int text_position_y = position_y + (int)(height - scaled_font_size) / 2;
  assets.draw_text(text, text_position_x, text_position_y, text_color, NULL, text_scale);

  text_position_x = (position_x + width) - (int)(3.25 * scaled_font_size);
  assets.draw_text(std::to_string(range_actual), text_position_x, text_position_y, text_color, NULL, text_scale);
}

void Selector::update(const Assets& assets) {
  bool x_in_range = (assets.mouse_position_x >= (position_x + width - assets.default_font_size * text_scale)) && (assets.mouse_position_x <= (position_x + width));
  bool up_y_in_range = (assets.mouse_position_y >= position_y) && (assets.mouse_position_y < (position_y + (int)height / 2));
  bool down_y_in_range = (assets.mouse_position_y >= (position_y + (int)height / 2)) && (assets.mouse_position_y <= (position_y + height));
  mouse_hover_up = x_in_range && up_y_in_range;
  mouse_hover_down = x_in_range && down_y_in_range;

  bool mouse_right = assets.mouse_state == SDL_BUTTON(SDL_BUTTON_LEFT);
  if (!mouse_right) {
    click_lock = false;
  }
  if (!mouse_hover_up && !mouse_hover_down && mouse_right) {
    click_lock = true;
  }
  mouse_click_up = mouse_hover_up && mouse_right && !click_lock;
  mouse_click_down = mouse_hover_down && mouse_right && !click_lock;

  if (mouse_click_up || mouse_click_down) {
    if (repeat_timer == 0) {
      if (mouse_click_up) {
        if (range_actual < range_max) {
          range_actual += 1;
        }
      }
      else if (mouse_click_down) {
        if (range_actual > range_min) {
          range_actual -= 1;
        }
      }
      repeat_timer = repeat_timer_total * (1 / repeats);
      if (repeat_timer < 100) {
        repeat_timer = 100;
      }
      repeats++;
    }
  }
  else {
    repeats = 1;
    repeat_timer = 0;
  }

  frame_time = SDL_GetTicks() - ticks;
  ticks += frame_time;
  repeat_timer -= frame_time;
  if (repeat_timer < 0) {
    repeat_timer = 0;
  }
}



// Text

Text::Text(const int& position_x, const int& position_y, const std::string& text, const int& text_scale, const SDL_Color& text_color)
: position_x(position_x), position_y(position_y), text(text), text_scale(text_scale), text_color(text_color) {}

void Text::draw(const Assets& assets) {
  assets.draw_text(text, position_x, position_y, text_color, NULL, text_scale);
}
