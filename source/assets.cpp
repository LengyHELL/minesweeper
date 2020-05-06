#include "assets.hpp"
#include <iostream>
#include <filesystem>

Assets::Assets(const int width, const int height, const std::string font_path, const std::string image_directory) : width(width), height(height) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL initialization failed!, SDL_Error: " << SDL_GetError() << std::endl;
  }
  else {
    window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      std::cerr << "Window initialization failed! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == NULL) {
        std::cerr << "Renderer initialization failed! SDL_Error: " << SDL_GetError() << std::endl;
      }
    }
  }
  if (TTF_Init() < 0) {
    std::cerr << "TTF initialization failed!, SDL_Error: " << SDL_GetError() << std::endl;
  }
  else {
    font = TTF_OpenFont(font_path.c_str(), 24);
    if (font == NULL) {
        std::cerr << "Font initialization failed!, SDL_Error: " << SDL_GetError() << std::endl;
    }
  }

  std::string filename;
  for (const auto & entry : std::filesystem::directory_iterator(image_directory)) {
    filename = entry.path().filename().string();
    SDL_Surface* surface = IMG_Load((image_directory + "/" + filename).c_str());
    if (surface == NULL) {
      std::cerr << "Image load failed!, Image: " + filename << std::endl;
    }
    else {
      images.insert(std::make_pair(filename, SDL_CreateTextureFromSurface(renderer, surface)));
      SDL_FreeSurface(surface);
    }
  }
}

Assets::~Assets() {
  for (auto& i : images) {
    SDL_DestroyTexture(i.second);
  }
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Assets::render() {
  SDL_RenderPresent(renderer);
  SDL_RenderClear(renderer);
}

void Assets::draw_text(const std::string text, const float scale, const SDL_Color color, const int position_x, const int position_y) {
  if (scale < 0) {
    std::cerr << "Assets::draw_image: scale too small" << std::endl;
  }

  SDL_Texture* texture = NULL;
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (surface == NULL) {
    std::cerr << "Assets::draw_texture: cannot create text" << std::endl;
  }
  else {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
  }

  SDL_Rect rect;
  rect.x = position_x;
  rect.y = position_y;
  rect.w = surface->w * scale;
  rect.h = surface->h * scale;
  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}

void Assets::draw_image(const std::string filename, const float scale, const int position_x, const int position_y) {
  if (scale < 0) {
    std::cerr << "Assets::draw_image: scale too small" + filename << std::endl;
  }
  SDL_Texture* texture = NULL;
  texture = images[filename];
  if (texture == NULL) {
    std::cerr << "Assets::draw_image: image not found " + filename << std::endl;
  }
  SDL_Rect rect;
  rect.x = position_x;
  rect.y = position_y;
  SDL_QueryTexture(texture, 0, 0, &rect.w, &rect.h);
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}
