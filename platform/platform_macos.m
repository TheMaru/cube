#include "platform.h"                                                                                                                                                             
#import <Cocoa/Cocoa.h>

static uint32_t *buffer = NULL;
static int buf_width = 0;
static int buf_height = 0;
static NSWindow *window = nil;
static NSImageView *imageView = nil;
static int should_close = 0;

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@end

@implementation AppDelegate
- (void)windowWillClose:(NSNotification *)notification {
    should_close = 1;
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}
@end

int platform_create_window(int width, int height) {
    buf_width = width;
    buf_height = height;

    buffer = malloc(sizeof(uint32_t) * width * height);
    if (!buffer) return 1;

    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];

    NSRect frame = NSMakeRect(0, 0, width, height);
    window = [[NSWindow alloc]
        initWithContentRect:frame
                  styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
                    backing:NSBackingStoreBuffered
                      defer:NO];

    [window setTitle:@"Cube"];
    [window setDelegate:appDelegate];
    [window center];

    // NSImageView is the simplest way to display a pixel buffer.
    // Each frame we'll create an image from our buffer and set it here.
    imageView = [[NSImageView alloc] initWithFrame:frame];
    [window setContentView:imageView];

    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp finishLaunching];

    return 0;
}

uint32_t* platform_get_buffer(void) {
    return buffer;
}

void platform_display_buffer(void) {
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef ctx = CGBitmapContextCreate(
        buffer,
        buf_width,
        buf_height,
        8,                // bits per component (each R/G/B/A channel)
        buf_width * 4,    // bytes per row (4 bytes per pixel)
        colorSpace,
        kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little
    );
    CGImageRef cgImage = CGBitmapContextCreateImage(ctx);

    NSImage *image = [[NSImage alloc]
        initWithCGImage:cgImage
                   size:NSMakeSize(buf_width, buf_height)];
    [imageView setImage:image];

    CGImageRelease(cgImage);
    CGContextRelease(ctx);
    CGColorSpaceRelease(colorSpace);

    NSEvent *event;
    while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                       untilDate:nil
                                          inMode:NSDefaultRunLoopMode
                                         dequeue:YES])) {
        [NSApp sendEvent:event];
    }
}

int platform_should_close(void) {
    return should_close;
}
