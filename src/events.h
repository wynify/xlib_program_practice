#ifndef EVENTS_H
#define EVENTS_H

#include "shapes.h"
#include <X11/Xlib.h>


void handleExpose(Display *display, Window window, GC gc, Shape *shapes, int shape_count);
void handleKeyPress(Display *display, XKeyEvent *event, unsigned long *current_color, Shape *shapes, int *shape_count, Window window, GC gc);
void handleButtonPress(Display *display, Window window, GC gc, Shape *shapes, int *shape_count, XButtonEvent *event, unsigned long current_color);
void handleMotionNotify(Display *display, Window window, GC gc, XMotionEvent *event, char *coord_str, int *last_x, int *last_y, Shape *shapes, int shape_count);

#endif
