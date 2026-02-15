#include <stdint.h>

void render(uint32_t* displayBuffer, int width, int height) {
  int w, h;
  uint8_t b, a;
  uint32_t color;

  b = 0, a = 255;

  for (h = 0; h < height; h++) {
    for (w = 0; w < width; w++) {
      uint8_t r = (w * 255) / width;
      uint8_t g = (h * 255) / height;
      // color = a << 24;
      // color = color | r << 16;
      // color = color | g << 8;
      // color = color | b;
      color = (a << 24) | (r << 16) | (g << 8) | b;
      displayBuffer[(h * width) + w] = color;
    }
  }
}
