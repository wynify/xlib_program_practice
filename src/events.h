#ifndef EVENTS_H
#define EVENTS_H

#include <X11/Xlib.h>
#include "circle.h"

// Функції для обробки подій
void handleExpose(Display *display, Window window, GC gc, Circle *circles, int circle_count);
void handleKeyPress(Display *display, XKeyEvent *event, unsigned long *current_color, Circle *circles, int *circle_count, Window window, GC gc);
void handleButtonPress(Display *display, Window window, GC gc, Circle *circles, int *circle_count, XButtonEvent *event, unsigned long current_color);
void handleMotionNotify(Display *display, Window window, GC gc, XMotionEvent *event, char *coord_str, int *last_x, int *last_y, Circle *circles, int circle_count);
void handleFileOperations(Circle *circles, int *circle_count);
#endif
