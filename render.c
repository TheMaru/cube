#include <stdint.h>

typedef struct {
  int x;
  int y;
} Point2D;

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
}
