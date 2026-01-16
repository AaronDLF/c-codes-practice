#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR 0xFF0000

int main() {
  printf("Welcome to the function plotter!\n");
  SDL_Window *pwindow =
      SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect rect = (SDL_Rect){50, 50, 50, 50};
  SDL_FillRect(psurface, &rect, COLOR);

  SDL_Event event;
  bool app_running = true;

  while (app_running) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = false;
      }
    }
    SDL_UpdateWindowSurface(pwindow);
  }
}
