#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600

#define SCALE 10

typedef struct {
  int vx, vy;
} Velocity;

Velocity get_rand_step() {
  int choice = rand() / (RAND_MAX / 4);

  switch (choice) {
  case 0: // up
    return (Velocity){0, -1};

  case 1: // down
    return (Velocity){0, 1};

  case 2: // left
    return (Velocity){-1, 0};

  case 3: // right
    return (Velocity){1, 0};
  }

  fprintf(stderr, "Error: invalid random %d choice\n", choice);
  exit(-1);
}

int main(int argc, char *argv[]) {
  int num_agents;

  if (argc == 1) {
    num_agents = 5;
  } else if (argc == 2) {
    num_agents = atoi(argv[1]);
  } else {
    printf("Usage: %s [num_agents]\n", argv[0]);
    return -1;
  }

  srand(time(NULL));

  SDL_Window *pwindow =
      SDL_CreateWindow("Random Walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect rect = (SDL_Rect){WIDTH / 2, HEIGHT / 2, 2, 2};

  int app_running = 1;
  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = 0;
      }
    }

    Velocity v = get_rand_step();
    for (int i = 0; i < SCALE; i++) {
      rect.x += v.vx;
      rect.y += v.vy;

      if (rect.x < 0 || rect.x >= WIDTH)
        v.vx *= -1;
      if (rect.y < 0 || rect.y >= HEIGHT)
        v.vy *= -1;

      SDL_FillRect(psurface, &rect, 0xFFFFFF);
    }
    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(20);
  }
}
