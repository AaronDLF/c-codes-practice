#include "tinyexpr.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR 0x0000FF
#define GRID_COLOR 0xCCCCCC
#define X_START -10
#define X_END 10
#define Y_START -5
#define Y_END 5
#define X_SCALE ((double)WIDTH / (X_END - X_START))
#define Y_SCALE ((double)HEIGHT / (Y_END - Y_START))
#define STEP 0.001

void draw_at_grid_coordinates(SDL_Surface *psurface, double x, double y,
                              Uint32 color) {

  int x_display = (double)WIDTH / 2 + ((double)x * (double)X_SCALE);
  int y_display = (double)HEIGHT / 2 - ((double)y * (double)Y_SCALE);
  SDL_Rect *shifted_rect = &(SDL_Rect){x_display, y_display, 2, 2};
  SDL_FillRect(psurface, shifted_rect, color);
}

void draw_grid(SDL_Surface *psurface) {

  for (double x = X_START; x <= X_END; x += 0.0001) {
    draw_at_grid_coordinates(psurface, x, 0, GRID_COLOR);
  }

  for (double y = Y_START; y <= Y_END; y += 0.0001) {
    draw_at_grid_coordinates(psurface, 0, y, GRID_COLOR);
  }
}

void draw_expr(SDL_Surface *psurface, char *expr) {

  double x;

  te_variable vars[] = {{"x", &x}};

  int err;
  te_expr *pexpr = te_compile(expr, vars, 1, &err);

  if (pexpr) {

    for (x = X_START; x <= X_END; x += STEP) {

      double res = te_eval(pexpr);
      printf("The result of the expression is: %f \n", res);
      draw_at_grid_coordinates(psurface, x, res, COLOR);
    }

  } else {
    fprintf(stderr, "Error compiling expression at position: %d\n", err);
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  printf("Welcome to the function plotter!\n");

  if (argc != 2) {
    printf("Usage: %s <function>\n", argv[0]);
    return 0;
  }

  char *expr = argv[1];

  SDL_Window *pwindow =
      SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  draw_grid(psurface);
  draw_expr(psurface, expr);

  SDL_Event event;
  bool app_running = true;
  SDL_UpdateWindowSurface(pwindow);

  while (app_running) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = false;
      }
    }
  }
}
