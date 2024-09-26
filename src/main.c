#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shapes.h"  // Включаємо заголовок shapes.h
#include "events.h"

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;
    char coord_str[50];
    int last_x = 0, last_y = 0;

    Shape shapes[100];  // Масив фігур
    int shape_count = 0;  // Лічильник фігур

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Не вдається відкрити дисплей\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 600, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XMapWindow(display, window);
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask);

    GC gc = DefaultGC(display, screen);
    unsigned long current_color = BlackPixel(display, screen);

    while (1) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            handleExpose(display, window, gc, shapes, shape_count);
        }

        if (event.type == KeyPress) {
            handleKeyPress(display, &event.xkey, &current_color, shapes, &shape_count, window, gc);
        }

        if (event.type == ButtonPress) {
            handleButtonPress(display, window, gc, shapes, &shape_count, &event.xbutton, current_color);
        }

        if (event.type == MotionNotify) {
            handleMotionNotify(display, window, gc, &event.xmotion, coord_str, &last_x, &last_y, shapes, shape_count);
        }
    }

    XCloseDisplay(display);
    return 0;
}
