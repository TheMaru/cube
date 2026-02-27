# include "render.h"
# include <stdint.h>
# include <stdlib.h>
# include <math.h>

typedef struct {
  float x;
  float y;
  float z;
} Point3D;

typedef struct {
  int x;
  int y;
} Point2D;

static uint32_t* displayBuffer;
static int width;
static int height;
static uint32_t sideColor = (255 << 24) | (255 << 8);

static void draw_line_low(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int stepY = (y0 < y1) ? 1 : -1; 
  int error = 2 * dy - dx;
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    displayBuffer[y * width + x] = sideColor;
    error += 2 * dy;
    if ( error > dx) {
      y += stepY;
      error -= 2 * dx;
    }
  }
}

static void draw_line_high(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int stepX = (x0 < x1) ? 1 : -1; 
  int error = 2 * dx - dy;
  int x = x0;

  for (int y = y0; y <= y1; y++) {
    displayBuffer[y * width + x] = sideColor;
    error += 2 * dx;
    if ( error > dy) {
      x += stepX;
      error -= 2 * dy;
    }
  }
}

static void draw_line(Point2D p1, Point2D p2) {
  int dx, dy;
  dx = abs(p2.x - p1.x);
  dy = abs(p2.y - p1.y);
  
  if (dy < dx) {
    if (p1.x > p2.x) {
      draw_line_low(p2.x, p2.y, p1.x, p1.y);
    } else {
      draw_line_low(p1.x, p1.y, p2.x, p2.y);
    }
  } else {
    if (p1.y > p2.y) {
      draw_line_high(p2.x, p2.y, p1.x, p1.y);
    } else {
      draw_line_high(p1.x, p1.y, p2.x, p2.y);
    }
  }
}

void render(uint32_t* db, int w, int h, double angle) {
  int scale = 200;
  int centerX = w / 2;
  int centerY = h / 2;

  displayBuffer = db;
  width = w;
  height = h;

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

  // rotate 30° on y axis
  double angleY = 0.524 + angle;
  double cosY = cos(angleY);
  double sinY = sin(angleY);
  Point3D rotatedY[8];
  for (int i = 0; i < 8; i++) {
    float x = cubeVertices[i].x;
    float y = cubeVertices[i].y;
    float z = cubeVertices[i].z;
    rotatedY[i].x = x * cosY - z * sinY;
    rotatedY[i].y = y;
    rotatedY[i].z = x * sinY + z * cosY;
  }

  double angleX = 0.349;
  double cosX = cos(angleX);
  double sinX = sin(angleX);
  Point3D rotatedYX[8];
  for (int i = 0; i < 8; i++) {
    float x = rotatedY[i].x;
    float y = rotatedY[i].y;
    float z = rotatedY[i].z;
    rotatedYX[i].x = x;
    rotatedYX[i].y = y * cosX - z * sinX;
    rotatedYX[i].z = y * sinX + z * cosX;
  }

  // project to 2 axis
  Point2D projectedCubeVertices[8];
  for (int i = 0; i < 8; i++) {
    projectedCubeVertices[i].x = centerX + (int)(rotatedYX[i].x * scale);
    projectedCubeVertices[i].y = centerY - (int)(rotatedYX[i].y * scale);
  }

  // green
  uint32_t pointColor = (255 << 24) | (126 << 16) | (126 << 8);

  // draw vertices
  for (int i = 0; i < 4; i++) {
    displayBuffer[projectedCubeVertices[i].y * width + projectedCubeVertices[i].x] = pointColor;
  }

  draw_line(projectedCubeVertices[0], projectedCubeVertices[1]);
  draw_line(projectedCubeVertices[1], projectedCubeVertices[2]);
  draw_line(projectedCubeVertices[2], projectedCubeVertices[3]);
  draw_line(projectedCubeVertices[3], projectedCubeVertices[0]);

  draw_line(projectedCubeVertices[4], projectedCubeVertices[5]);
  draw_line(projectedCubeVertices[5], projectedCubeVertices[6]);
  draw_line(projectedCubeVertices[6], projectedCubeVertices[7]);
  draw_line(projectedCubeVertices[7], projectedCubeVertices[4]);

  draw_line(projectedCubeVertices[0], projectedCubeVertices[4]);
  draw_line(projectedCubeVertices[1], projectedCubeVertices[5]);
  draw_line(projectedCubeVertices[2], projectedCubeVertices[6]);
  draw_line(projectedCubeVertices[3], projectedCubeVertices[7]);
}

