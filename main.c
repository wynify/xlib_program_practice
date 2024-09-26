#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "shapes.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

int main()
{
    Display *display;
    Window window;
    XEvent event;
    
    int screen;
    Shape shapes[MAX_SHAPES];
    int shape_count = 0;
    unsigned long current_color;
    int current_shape = 0;

    display = XOpenDisplay(NULL);
    if(display == NULL){
        printf("Can't open display\n");
        exit(1);
    }


    screen = DefaultScreen(display);
    current_color = BlackPixel(display, screen);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 600, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));
    XMapWindow(display, window);
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask);

    GC gc = DefaultGC(display, screen);

    while (1) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            printf("Expose event detected\n");
            draw_shapes(display, window, gc, shapes, shape_count);
        }

        if (event.type == KeyPress) {
            handle_keypress(event, display, screen, &current_color, &current_shape, &shape_count, window);
        }

        if (event.type == ButtonPress) {
            handle_buttonpress(event, shapes, &shape_count, current_color, current_shape);
        }
    }

    XCloseDisplay(display);
    return 0;
}

