# include "render.h"
# include <stdint.h>
# include <stdlib.h>

void render(uint32_t* displayBuffer, int width, int height) {
  int scale = 200;
  int centerX = width / 2;
  int centerY = height / 2;

  // define points
  Point2D points[8];
  points[0].x = centerX + (-1 * scale);
  points[0].y = centerY - (1 * scale);
  points[1].x = centerX + (1 * scale);
  points[1].y = centerY - (1 * scale);
  points[2].x = centerX + (1 * scale);
  points[2].y = centerY - (-1 * scale);
  points[3].x = centerX + (-1 * scale);
  points[3].y = centerY - (-1 * scale);

  // green
  uint32_t green;
  green = 255 << 24;
  green = green | 0 << 16;
  green = green | 255 << 8;
  green = green | 0;

  // draw points
  for (int i = 0; i < 4; i++) {
    displayBuffer[points[i].y * width + points[i].x] = green;
  }

  draw_line(displayBuffer, width, points[0], points[1]);
  draw_line(displayBuffer, width, points[1], points[2]);
  draw_line(displayBuffer, width, points[2], points[3]);
  draw_line(displayBuffer, width, points[3], points[0]);
}

void draw_line(uint32_t* displayBuffer, int width, Point2D p1, Point2D p2) {
  // calculate step count
  int dx, dy, steps;
  dx = abs(p2.x - p1.x);
  dy = abs(p2.y - p1.y);
  steps = (dx > dy) ? dx : dy;

  uint32_t sideColor = (255 << 24) | 126 << 16 | 126 << 8;

  for (int i = 0; i <= steps; i++) {
    float t = (float)i / steps;
    int x = p1.x + (int)(t * (p2.x - p1.x));
    int y = p1.y + (int)(t * (p2.y - p1.y));
    displayBuffer[y * width + x] = sideColor;
  }
}
