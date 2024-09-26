#include "shapes.h"

void draw_shapes(Display *display, Window window, GC gc, Shape shapes[], int shape_count) {
    for (int i = 0; i < shape_count; i++) {
        XSetForeground(display, gc, shapes[i].color);
        if (shapes[i].shape == 0) {  // Коло
            XDrawArc(display, window, gc, shapes[i].x - 25, shapes[i].y - 25, 50, 50, 0, 360 * 64);
        } else if (shapes[i].shape == 1) {  // Квадрат
            XDrawRectangle(display, window, gc, shapes[i].x - 25, shapes[i].y - 25, 50, 50);
        }
    }
}

void handle_keypress(XEvent event, Display *display, int screen, unsigned long *current_color, int *current_shape, int *shape_count, Window window) {
    KeySym key = XLookupKeysym(&event.xkey, 0);

    if (key == XK_r) {
        *current_color = 0xFF0000;  // Червоний
    } else if (key == XK_g) {
        *current_color = 0x00FF00;  // Зелений
    } else if (key == XK_b) {
        *current_color = 0x0000FF;  // Синій
    } else if (key == XK_k) {
        *current_color = BlackPixel(display, screen);  // Чорний
    } else if (key == XK_w) {
        *current_color = WhitePixel(display, screen);  // Білий
    } else if (key == XK_q) {
        XClearWindow(display, window);  // Очищення вікна
        *shape_count = 0;  // Очищаємо збережені фігури
    } else if (key == XK_s) {
        *current_shape = 1;  // Вибір квадрату
    } else if (key == XK_c) {
        *current_shape = 0;  // Вибір кола
    }
}

void handle_buttonpress(XEvent event, Shape shapes[], int *shape_count, unsigned long current_color, int current_shape) {
    if (event.xbutton.button == Button1 && *shape_count < MAX_SHAPES) {
        shapes[*shape_count].x = event.xbutton.x;
        shapes[*shape_count].y = event.xbutton.y;
        shapes[*shape_count].color = current_color;
        shapes[*shape_count].shape = current_shape;
        (*shape_count)++;
    }
}
