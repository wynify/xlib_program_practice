#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdio.h>
#include <X11/Xlib.h>

// Структура для збереження даних про кола
typedef struct {
    int x, y;  // Координати центру кола
    unsigned long color;  // Колір кола
} Circle;

// Функції для роботи з колами
void drawCircles(Display *display, Window window, GC gc, Circle *circles, int circle_count);
void addCircle(Circle *circles, int *circle_count, int x, int y, unsigned long color);

//Save load shapes
void saveCircles(Circle *circles, int circle_count, const char *filename);
int loadCircles(Circle *circles, int max_circles, const char *filename);


#endif

