#include "circle.h"
#include "save_shapes.c"
#include <X11/Xlib.h>

void drawCircles(Display *display, Window window, GC gc, Circle *circles, int circle_count) {
    for (int i = 0; i < circle_count; i++) {
        XSetForeground(display, gc, circles[i].color);
        XDrawArc(display, window, gc, circles[i].x - 25, circles[i].y - 25, 50, 50, 0, 360 * 64);
    }
}

void addCircle(Circle *circles, int *circle_count, int x, int y, unsigned long color) {
    circles[*circle_count].x = x;
    circles[*circle_count].y = y;
    circles[*circle_count].color = color;
    (*circle_count)++;
}

