// select_color.h
#ifndef SELECT_COLOR_H
#define SELECT_COLOR_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

typedef struct {
    int red;
    int green;
    int blue;
} Color;

typedef struct {
    KeySym key;
    Color color;
} KeyColorMapping;

extern KeyColorMapping colorMappings[];  // def without point

void selectColor(Display *display, Window window, unsigned long *current_color);
int isValidColor(int red, int green, int blue);


#endif //SELECT_COLOR