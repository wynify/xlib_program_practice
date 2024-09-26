#include "events.h"
#include "circle.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleExpose(Display *display, Window window, GC gc, Circle *circles, int circle_count) {
    drawCircles(display, window, gc, circles, circle_count);
}

void handleKeyPress(Display *display, XKeyEvent *event, unsigned long *current_color, Circle *circles, int *circle_count, Window window, GC gc) {
    KeySym key = XLookupKeysym(event, 0);

    if (key == XK_s) {
        saveCircles(circles, *circle_count, "circles.dat");
    } else if (key == XK_l) {
        *circle_count = loadCircles(circles, 100, "circles.dat");
        XClearWindow(display, window);  // Очищення екрану перед перемальовуванням
        drawCircles(display, window, gc, circles, *circle_count);  // Перемальовування кіл
    } else if (key == XK_r) {
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
        *circle_count = 0;  // Очищаємо збережені кола
    }
}

void handleFileOperations(Circle *circles, int *circle_count) {
    saveCircles(circles, *circle_count, "circle.dat");
    *circle_count = loadCircles(circles, 100, "circle.dat");
}


void handleButtonPress(Display *display, Window window, GC gc, Circle *circles, int *circle_count, XButtonEvent *event, unsigned long current_color) {
    if (event->button == Button1 && *circle_count < 100) {
        XSetForeground(display, gc, current_color);
        XDrawArc(display, window, gc, event->x - 25, event->y - 25, 50, 50, 0, 360 * 64);

        addCircle(circles, circle_count, event->x, event->y, current_color);
    }
}

void handleMotionNotify(Display *display, Window window, GC gc, XMotionEvent *event, char *coord_str, int *last_x, int *last_y, Circle *circles, int circle_count) {
    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));
    XFillRectangle(display, window, gc, *last_x, *last_y - 10, 100, 20);  // Очищаємо область для нового тексту

    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    sprintf(coord_str, "X: %d, Y: %d", event->x, event->y);
    XDrawString(display, window, gc, event->x, event->y, coord_str, strlen(coord_str));

    *last_x = event->x;
    *last_y = event->y;

    drawCircles(display, window, gc, circles, circle_count);  // Перемальовуємо всі збережені кола
}
