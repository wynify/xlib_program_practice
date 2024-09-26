#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shapes.h"
#include "events.h"

Shape shapes[100];  // Масив для збереження фігур
int shape_count = 0;  // Лічильник фігур
ShapeType current_shape = CIRCLE;

void handleExpose(Display *display, Window window, GC gc, Shape *shapes, int shape_count) {
    drawShapes(display, window, gc, shapes, shape_count);  // Перемальовуємо всі фігури
}

void handleKeyPress(Display *display, XKeyEvent *event, unsigned long *current_color, 
                    Shape *shapes, int *shape_count, Window window, GC gc) {
    KeySym key = XLookupKeysym(event, 0);

    if (key == XK_r) {
        *current_color = 0xFF0000;  // Червоний
    } else if (key == XK_g) {
        *current_color = 0x00FF00;  // Зелений
    } else if (key == XK_b) {
        *current_color = 0x0000FF;  // Синій
    } else if (key == XK_k) {
        *current_color = BlackPixel(display, DefaultScreen(display));  // Чорний
    } else if (key == XK_w) {
        *current_color = WhitePixel(display, DefaultScreen(display));  // Білий
    } else if (key == XK_c) {
        XClearWindow(display, window);  // Очищення вікна
        *shape_count = 0;  // Очищаємо збережені фігури
    }
}

void handleButtonPress(Display *display, Window window, GC gc, Shape *shapes, 
                       int *shape_count, XButtonEvent *event, unsigned long current_color) {
    // Вибір фігури за допомогою колесика миші
    if (event->button == Button4) {  // Колесико вверх
        current_shape = (current_shape + 1) % 3;  // Перемикання між 0, 1, 2
    } else if (event->button == Button5) {  // Колесико вниз
        current_shape = (current_shape - 1 + 3) % 3;  // Перемикання між 0, 1, 2
    }

    // Малювання фігури лівою кнопкою миші
    if (event->button == Button1) {
        int width = 50, height = 50;  // Ширина та висота для фігур
        if (current_shape == CIRCLE) {
            addShape(shapes, shape_count, event->x, event->y, current_color, CIRCLE, width, height);
        } else if (current_shape == RECTANGLE) {
            addShape(shapes, shape_count, event->x, event->y, current_color, RECTANGLE, width, height);
        } else if (current_shape == ELLIPSE) {
            addShape(shapes, shape_count, event->x, event->y, current_color, ELLIPSE, width, height);
        }

        // Малювання всіх фігур після додавання нової
        drawShapes(display, window, gc, shapes, *shape_count);
    }
}

void handleMotionNotify(Display *display, Window window, GC gc, XMotionEvent *event, 
                        char *coord_str, int *last_x, int *last_y, Shape *shapes, int shape_count) {
    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));
    XFillRectangle(display, window, gc, *last_x, *last_y - 10, 100, 20);  // Очищаємо область для нового тексту

    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    sprintf(coord_str, "X: %d, Y: %d", event->x, event->y);
    XDrawString(display, window, gc, event->x, event->y, coord_str, strlen(coord_str));

    *last_x = event->x;
    *last_y = event->y;

    drawShapes(display, window, gc, shapes, shape_count);
}
