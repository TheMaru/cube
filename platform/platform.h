#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

int platform_create_window(int width, int height);
uint32_t* platform_get_buffer(void);
void platform_display_buffer(void);
int platform_should_close(void);

#endif
