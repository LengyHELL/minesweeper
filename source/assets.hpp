#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <map>

class Assets {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  TTF_Font* font;
  std::string image_directory;
  int width;
  int height;
  std::map<std::string, SDL_Texture*> images;

public:
  // user input variables
  bool exit;
  const Uint8* keyboard_state;
  Uint32 mouse_state;
  int mouse_position_x;
  int mouse_position_y;

  // info variables
  const int default_font_size;


  // construct, destruct
  Assets(const int& width, const int& height, const std::string& font_path, const int& default_font_size, const std::string& image_directory);
  ~Assets();

  // methods for operations
  void render();
  void draw_text(const std::string& text, const int& position_x, const int& position_y, const SDL_Color& color, SDL_Rect* area = NULL, const float& scale = 1) const;
  void draw_image(const std::string& filename, const int& position_x, const int& position_y, const SDL_Color* color = NULL, SDL_Rect* area = NULL, const SDL_Rect* size = NULL, const float& angle = 0) const;
  void update_inputs();
};

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
  bool start;
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
  int range_min;
  int range_max;
  float repeat_timer_total;
  float repeat_timer;
  int repeats;
  float ticks;
  float frame_time;

public:
  // variables
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

};
