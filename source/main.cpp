#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* args[]) {
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;

  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL initialization failed!, SDL_Error: " << SDL_GetError() << std::endl;
  }
  else {
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      std::cerr << "Window initialization failed! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else {
      screenSurface = SDL_GetWindowSurface(window);

      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF ,0xFF, 0xFF));
      SDL_UpdateWindowSurface(window);
      SDL_Delay(2000);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
