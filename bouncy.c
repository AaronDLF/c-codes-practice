#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define WHITE_COLOR 0xFFFFFFFF
#define A_GRAVITY 10

struct Circle {
  int x;
  int y;
  int radius;
  int vx;
  int vy;
};

void FillCircle(SDL_Surface *psurface, struct Circle circle) {
  int lower_x = circle.x - circle.radius;
  int lower_y = circle.y - circle.radius;
  int higher_x = circle.x + circle.radius;
  int higher_y = circle.y + circle.radius;

  int radius_squared = circle.radius * circle.radius;

  for (int x = lower_x; x <= higher_x; x++) {
    for (int y = lower_y; y <= higher_y; y++) {
      int center_distance_squared =
          (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y);
      if (center_distance_squared < radius_squared) {
        SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
        SDL_FillRect(psurface, &pixel, WHITE_COLOR);
      }
    }
  }
}

void step(struct Circle *circle) {
  circle->x += circle->vx;
  circle->y += circle->vy;
  circle->vy += A_GRAVITY;
}

int main() {

  printf("Hello, Bouncy World!\n");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow =
      SDL_CreateWindow("Bouncy Ball Simulation", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  struct Circle circle = (struct Circle){200, 200, 50, 1, 1};
  FillCircle(psurface, circle);
  SDL_UpdateWindowSurface(pwindow);

  SDL_Event event;
  int simulation = 1;

  while (simulation) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        simulation = 0;
      }
    }
  }

  SDL_Delay(3000);
}
