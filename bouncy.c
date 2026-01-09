#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600

struct Circle {
  int x;
  int y;
  int radius;
};

void FillCircle(SDL_Surface *psurface, struct Circle circle) {
  int lower_x = circle.x - circle.radius;
  int lower_y = circle.y - circle.radius;
  int higher_x = circle.x + circle.radius;
  int higher_y = circle.y + circle.radius;

  int radius_squared = circle.radius * circle.radius;
}

int main() {

  printf("Hello, Bouncy World!\n");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow =
      SDL_CreateWindow("Bouncy Ball Simulation", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect rect = (SDL_Rect){100, 100, 50, 50};
  SDL_FillRect(psurface, &rect, SDL_MapRGB(psurface->format, 255, 0, 0));
  SDL_UpdateWindowSurface(pwindow);

  SDL_Delay(3000);
}
