#ifndef SHAPES_H
#define SHAPES_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

// Структура для збереження даних про фігури
typedef struct {
    int x, y;  // Координати центру фігури
    unsigned long color;  // Колір фігури
    int shape;  // Форма: 0 - коло, 1 - квадрат
} Shape;

#define MAX_SHAPES 100  // Максимальна кількість фігур

void draw_shapes(Display *display, Window window, GC gc, Shape shapes[], int shape_count);
void handle_keypress(XEvent event, Display *display, int screen, unsigned long *current_color, int *current_shape, int *shape_count, Window window);
void handle_buttonpress(XEvent event, Shape shapes[], int *shape_count, unsigned long current_color, int current_shape);

#endif // SHAPES_H
