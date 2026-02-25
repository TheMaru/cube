# include "render.h"
# include <stdint.h>
# include <stdlib.h>

typedef struct {
  float x;
  float y;
  float z;
} Point3D;

typedef struct {
  int x;
  int y;
} Point2D;

void draw_line(uint32_t* displayBuffer, int width, Point2D p1, Point2D p2) {
  // calculate step count
  int dx, dy, steps;
  dx = abs(p2.x - p1.x);
  dy = abs(p2.y - p1.y);
  steps = (dx > dy) ? dx : dy;

  uint32_t sideColor = (255 << 24) | (255 << 8);

  for (int i = 0; i <= steps; i++) {
    float t = (float)i / steps;
    int x = p1.x + (int)(t * (p2.x - p1.x));
    int y = p1.y + (int)(t * (p2.y - p1.y));
    displayBuffer[y * width + x] = sideColor;
  }
}

void render(uint32_t* displayBuffer, int width, int height) {
  int scale = 200;
  int centerX = width / 2;
  int centerY = height / 2;

  // define vertices in 3 axis
  Point3D cubeVertices[8] = {
    {-1, 1, 1},
    {1, 1, 1},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, 1, -1},
    {1, 1, -1},
    {1, -1, -1},
    {-1, -1, -1},
  };

  // project to 2 axis
  Point2D projectedCubeVertices[8];
  for (int i = 0; i < 8; i++) {
    projectedCubeVertices[i].x = centerX + (int)(cubeVertices[i].x * scale);
    projectedCubeVertices[i].y = centerY - (int)(cubeVertices[i].y * scale);
  }

  // green
  uint32_t pointColor = (255 << 24) | (126 << 16) | (126 << 8);

  // draw vertices
  for (int i = 0; i < 4; i++) {
    displayBuffer[projectedCubeVertices[i].y * width + projectedCubeVertices[i].x] = pointColor;
  }

  draw_line(displayBuffer, width, projectedCubeVertices[0], projectedCubeVertices[1]);
  draw_line(displayBuffer, width, projectedCubeVertices[1], projectedCubeVertices[2]);
  draw_line(displayBuffer, width, projectedCubeVertices[2], projectedCubeVertices[3]);
  draw_line(displayBuffer, width, projectedCubeVertices[3], projectedCubeVertices[0]);

  draw_line(displayBuffer, width, projectedCubeVertices[4], projectedCubeVertices[5]);
  draw_line(displayBuffer, width, projectedCubeVertices[5], projectedCubeVertices[6]);
  draw_line(displayBuffer, width, projectedCubeVertices[6], projectedCubeVertices[7]);
  draw_line(displayBuffer, width, projectedCubeVertices[7], projectedCubeVertices[4]);

  draw_line(displayBuffer, width, projectedCubeVertices[0], projectedCubeVertices[4]);
  draw_line(displayBuffer, width, projectedCubeVertices[1], projectedCubeVertices[5]);
  draw_line(displayBuffer, width, projectedCubeVertices[2], projectedCubeVertices[6]);
  draw_line(displayBuffer, width, projectedCubeVertices[3], projectedCubeVertices[7]);
}

