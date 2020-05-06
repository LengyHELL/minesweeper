#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <map>

class Assets {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event* event;
  TTF_Font* font;
  std::string image_directory;
  int width;
  int height;
  std::map<std::string, SDL_Texture*> images;

public:
  // construct, destruct
  Assets(const int width, const int height, const std::string font_path, const std::string image_directory);
  ~Assets();

  // methods for operations
  void render();
  void draw_text(const std::string text, const float scale, const SDL_Color color, const int position_x, const int position_y);
  void draw_image(const std::string filename, const float scale, const int position_x, const int position_y);
};