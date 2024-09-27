#ifndef EVENTS_H
#define EVENTS_H

#include <X11/Xlib.h>
#include "shapes.h"  // Переконайтеся, що ви імплементуєте фігури

void handleExpose(Display *display, Window window, GC gc, Shape *shapes, int shape_count);
void handleKeyPress(Display *display, XKeyEvent *event, unsigned long *current_color, Shape *shapes, int *shape_count, Window window, GC gc);
void handleButtonPress(Display *display, Window window, GC gc, Shape *shapes, int *shape_count, XButtonEvent *button_event, unsigned long current_color);
void handleMotionNotify(Display *display, Window window, GC gc, XMotionEvent *motion_event, char *coord_str, int *last_x, int *last_y, Shape *shapes, int shape_count);

#endif