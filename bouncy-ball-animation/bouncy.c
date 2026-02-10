#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define WHITE_COLOR 0xFFFFFFFF
#define BLACK_COLOR 0x00000000
#define BLUE_COLOR 0x4682B4
#define A_GRAVITY 0.2
#define TRAJECTORY_SIZE 100

struct Circle {
  double x;
  double y;
  double radius;
  double vx;
  double vy;
};

void FillCircle(SDL_Surface *psurface, struct Circle circle) {
  double lower_x = circle.x - circle.radius;
  double lower_y = circle.y - circle.radius;
  double higher_x = circle.x + circle.radius;
  double higher_y = circle.y + circle.radius;

  double radius_squared = circle.radius * circle.radius;

  for (double x = lower_x; x <= higher_x; x++) {
    for (double y = lower_y; y <= higher_y; y++) {
      double center_distance_squared =
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

  // Bounce on horizontal edges (left and right)
  if (circle->x - circle->radius <= 0 || circle->x + circle->radius >= WIDTH) {
    circle->vx = -circle->vx;

    // Adjust position to prevent going out of bounds
    if (circle->x - circle->radius <= 0)
      circle->x = circle->radius;
    if (circle->x + circle->radius >= WIDTH)
      circle->x = WIDTH - circle->radius;
  }

  // Bounce on vertical edges (top and bottom)

  if (circle->y - circle->radius <= 0 || circle->y + circle->radius >= HEIGHT) {
    circle->vy = -circle->vy;
    // Adjust position to prevent going out of bounds
    if (circle->y - circle->radius <= 0)
      circle->y = circle->radius;
    if (circle->y + circle->radius >= HEIGHT)
      circle->y = HEIGHT - circle->radius;
  }
}

void FillTrajectory(SDL_Surface *psurface, struct Circle circle) {
  static struct Circle trajectory[TRAJECTORY_SIZE];
  static int index = 0;
  trajectory[index] = circle;
  index = (index + 1) % TRAJECTORY_SIZE;

  for (int i = 0; i < TRAJECTORY_SIZE; i++) {
    struct Circle traj_circle = trajectory[i];
    double lower_x = traj_circle.x - traj_circle.radius / 4;
    double lower_y = traj_circle.y - traj_circle.radius / 4;
    double higher_x = traj_circle.x + traj_circle.radius / 4;
    double higher_y = traj_circle.y + traj_circle.radius / 4;

    double radius_squared = (traj_circle.radius / 4) * (traj_circle.radius / 4);

    for (double x = lower_x; x <= higher_x; x++) {
      for (double y = lower_y; y <= higher_y; y++) {
        double center_distance_squared =
            (x - traj_circle.x) * (x - traj_circle.x) +
            (y - traj_circle.y) * (y - traj_circle.y);
        if (center_distance_squared < radius_squared) {
          SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
          SDL_FillRect(psurface, &pixel, BLUE_COLOR);
        }
      }
    }
  }
}

int main() {

  printf("Hello, Bouncy World!\n");

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow = SDL_CreateWindow(
      "Bouncy Ball Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  struct Circle circle = (struct Circle){200, 200, 50, 5, 1};

  SDL_Rect erase_rect = (SDL_Rect){0, 0, WIDTH, HEIGHT};
  SDL_Event event;
  int simulation = 1;

  while (simulation) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        simulation = 0;
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          simulation = 0;
        }
      }
    }
    SDL_FillRect(psurface, &erase_rect, BLACK_COLOR);
    FillCircle(psurface, circle);
    FillTrajectory(psurface, circle);
    step(&circle);
    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(20);
  }
}
