#include "assets.hpp"
#include <iostream>
#include <filesystem>

Assets::Assets(const int& width, const int& height, const std::string& font_path, const int& default_font_size, const std::string& image_directory)
: width(width), height(height), default_font_size(default_font_size), exit(false) {
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
    font = TTF_OpenFont(font_path.c_str(), default_font_size);
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
  update_inputs();
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

void Assets::draw_text(const std::string& text, const int& position_x, const int& position_y, const SDL_Color& color, SDL_Rect* area, const float& scale) const {
  if (scale < 0) {
    std::cerr << "Assets::draw_text: scale too small" << std::endl;
  }

  SDL_Texture* texture = NULL;
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (surface == NULL) {
    std::cerr << "Assets::draw_text: cannot create text" << std::endl;
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

  if (area != NULL) {
    area->x = rect.x;
    area->y = rect.y;
    area->w = rect.w;
    area->h = rect.h;
  }
}

void Assets::draw_image(const std::string& filename, const int& position_x, const int& position_y, const SDL_Color* color, SDL_Rect* area, const SDL_Rect* size, const float& angle) const {
  if (size != NULL) {
    if ((size->w < 1) || (size->h < 1)) {
      std::cerr << "Assets::draw_image: size too small " + filename << std::endl;
    }
  }
  SDL_Texture* texture = NULL;
  texture = images.at(filename);
  if (texture == NULL) {
    std::cerr << "Assets::draw_image: image not found " + filename << std::endl;
  }

  SDL_Rect rect;
  rect.x = position_x;
  rect.y = position_y;
  if (size != NULL) {
    rect.w = size->w;
    rect.h = size->h;
  }
  else {
    SDL_QueryTexture(texture, 0, 0, &rect.w, &rect.h);
  }
  if (color != NULL) {
    SDL_SetTextureColorMod(texture, color->r, color->g, color->b);
  }
  SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
  SDL_SetTextureColorMod(texture, 255, 255, 255);

  if (area != NULL) {
    area->x = rect.x;
    area->y = rect.y;
    area->w = rect.w;
    area->h = rect.h;
  }
}

void Assets::update_inputs() {
  mouse_button_up = false;
  mouse_button_down = false;
  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit = true;
    }
    mouse_button_up = (event.type == SDL_MOUSEBUTTONUP);
    mouse_button_down = (event.type == SDL_MOUSEBUTTONDOWN);
  }
  keyboard_state = SDL_GetKeyboardState(NULL);
  if (mouse_button_up) {
    SDL_GetMouseState(&mouse_position_x, &mouse_position_y);
  }
  else {
    mouse_state = SDL_GetMouseState(&mouse_position_x, &mouse_position_y);
  }
}
