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
  void draw_image(const std::string& filename, const int& position_x, const int& position_y, const SDL_Color* color = NULL, SDL_Rect* area = NULL, const SDL_Rect* size = NULL) const;
  void update_inputs();
};

class Button {
  int button_position_x;
  int button_position_y;
  int button_width;
  int button_height;
  std::string button_text;
  int button_text_scale;
  SDL_Color button_text_color;
  SDL_Color button_hover_color;

public:
  // variables
  bool mouse_hover;
  bool selected;

  // constructor, destructor
  Button(const int& button_position_x, const int& button_position_y, const int& button_width, const int& button_height, const std::string& button_text,
  const int& button_text_scale, const SDL_Color& button_text_color, const SDL_Color& button_hover_color);
  ~Button() {}

  //functions
  void draw_button(const Assets& assets);
  void update_button(const Assets& assets);
};

class Selector {

};

class Text {

};
