CC = clang
CFLAGS = -std=c99 -Wall
OBJCFLAGS = -fobjc-arc
FRAMEWORKS = -framework Cocoa -framework CoreGraphics

SOURCES = main.c render.c platform/platform_macos.m
TARGET = cube

$(TARGET): $(SOURCES) platform/platform.h render.h
			$(CC) $(CFLAGS) $(OBJCFLAGS) $(FRAMEWORKS) $(SOURCES) -o $(TARGET)

clean:
			rm -f $(TARGET)
