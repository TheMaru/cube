# include "./platform/platform.h"
# include "render.h"
# include <stdint.h>

int main() {
  int width = 800, height = 600;
  int err = platform_create_window(width, height);

  if (err == 0) {
    uint32_t *displayBuffer = platform_get_buffer();

    while (!platform_should_close()) {
      render(displayBuffer, width, height);

      platform_display_buffer();
    }
  }
}
