#ifndef SHAPES_H
#define SHAPES_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

typedef struct
{
    int x, y;
    unsigned long color;
    int shape;
} Shape;

#define MAX_SHAPES 100

void draw_shapes(Display *display, Window window, GC gc, Shape shapes, int shape_count);
void handle_keypress(XEvent event, Display *display, int screen, unsigned long *current_color,
int *current_shape, int *shape_count, Window window);
void handle_buttonpress(XEvent event, Shape shapes[], int *shape_count, unsigned long
current_color, int current_shape);

#endif