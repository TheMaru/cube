# include "./platform/platform.h"
# include "render.h"
# include <stdint.h>

int main() {
  int width = 800, height = 600;
  int err = platform_create_window(width, height);

  if (err == 0) {
    uint32_t *displayBuffer = platform_get_buffer();
    long lastTime = platform_get_time();
    float speed = 0.785;
    double angle = 0;

    while (!platform_should_close()) {
      for (int i = 0; i < width * height; i++) {
        displayBuffer[i] = (uint32_t)(255 << 24);
      } 

      long currentTime = platform_get_time();
      double delta = (currentTime - lastTime) / 1e9;
      lastTime = currentTime;

      angle += speed * delta;
      render(displayBuffer, width, height, angle);

      platform_display_buffer();
    }
  }
}
