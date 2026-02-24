#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

typedef struct {
  int x;
  int y;
} Point2D;

void render(uint32_t* displayBuffer, int width, int height);
void draw_line(uint32_t* displayBuffer, int width, Point2D p1, Point2D p2);

#endif
