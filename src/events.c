#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shapes.h"
#include "events.h"
#include "select_color.h"

Shape shapes[100];  // Масив для збереження фігур
int shape_count = 0;  // Лічильник фігур
ShapeType current_shape = CIRCLE;

void handleExpose(Display *display, Window window, GC gc, Shape *shapes, int shape_count) {
    XClearWindow(display, window);  // Очищення вікна
    drawShapes(display, window, gc, shapes, shape_count);  // Малюємо всі фігури
}

void handleKeyPress(Display *display, XKeyEvent *event, unsigned long *current_color, 
                    Shape *shapes, int *shape_count, Window window, GC gc) {
    for (int i = 0; i < sizeof(colorMappings[0]) / sizeof(colorMappings[0]); i++){
        if(event->keycode == XKeysymToKeycode(display, colorMappings[i].key)){
            *current_color = (colorMappings[i].color.red << 16) |
                             (colorMappings[i].color.green << 8) |
                            (colorMappings[i].color.blue);
            break;
        }
    }
    
    KeySym key = XLookupKeysym(event, 0);

    if (key == XK_r) {
        *current_color = colorMappings->color.red;  // Червоний
    } else if (key == XK_g) {
        *current_color = colorMappings->color.green;  // Зелений
    } else if (key == XK_b) {
        *current_color = colorMappings->color.blue;  // Синій
    } else if (key == XK_k) {
        *current_color = BlackPixel(display, DefaultScreen(display));  // Чорний
    } else if (key == XK_w) {
        *current_color = WhitePixel(display, DefaultScreen(display));  // Білий
    } else if (key == XK_c) {
        XClearWindow(display, window);  // Очищення вікна
        *shape_count = 0;  // Очищаємо збережені фігури
    } else if (key == XK_f) {
        is_filled = !is_filled;
    } 

    if (key == XK_s) {
        saveShapes(shapes, *shape_count, "shapes.dat");
    } else if (key == XK_l) {
        *shape_count = loadShapes(shapes, 100, "shapes.dat");
        XClearWindow(display, window);  // Очищаємо вікно перед перемальовуванням
        handleExpose(display, window, gc, shapes, *shape_count);
    }
    
    if (event->keycode == XKeysymToKeycode(display, XK_y)) { // Приклад: натискання 'c' для вибору кольору
        selectColor(display, window, current_color);
        handleExpose(display, window, gc, shapes, *shape_count);
    }
}

void drawCurrentShapeName(Display *display, Window window, GC gc, ShapeType shape_type){
    char *shape_name;

    switch(shape_type){
        case CIRCLE: shape_name = "<Circle>"; break;
        case RECTANGLE: shape_name = "<Rectangle>"; break;
        case ELLIPSE: shape_name = "<Ellipse>"; break;
        default: shape_name = "<Unknown>"; break;
    }

    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));
    XDrawString(display, window, gc, 10, 20, shape_name, strlen(shape_name));
}

void handleButtonPress(Display *display, Window window, GC gc, Shape *shapes, 
                       int *shape_count, XButtonEvent *event, unsigned long current_color) {
    // Вибір фігури за допомогою колесика миші
    if (event->button == Button4) {  // Колесико вверх
        current_shape = (current_shape + 1) % 3;  // Перемикання між 0, 1, 2
    } else if (event->button == Button5) {  // Колесико вниз
        current_shape   = (current_shape - 1 + 3) % 3;  // Перемикання між 0, 1, 2
    }

    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));
    XFillRectangle(display, window, gc, 0, 0, 200, 30);

    drawShapes(display, window, gc, shapes, *shape_count);

    char shape_info[50];
    if (current_shape == CIRCLE) {
        strcpy(shape_info, "<Circle>");
    } else if (current_shape == RECTANGLE) {
        strcpy(shape_info, "<Rectangle>");
    } else if (current_shape == ELLIPSE) {
        strcpy(shape_info, "<Ellipse>");
    }

    // Малювання фігури лівою кнопкою миші
    if (event->button == Button1) {
        int width = 100, height = 100;  // Ширина та висота для фігур

        if (current_shape == CIRCLE) {
            addShape(shapes, shape_count, event->x, event->y, current_color, CIRCLE, width, height);
        } else if (current_shape == RECTANGLE) {
            addShape(shapes, shape_count, event->x, event->y, current_color, RECTANGLE, width, height);
        } else if (current_shape == ELLIPSE) {
            addShape(shapes, shape_count, event->x, event->y, current_color, ELLIPSE, width, height);
        }

        //Printing text about shape type:
        XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
        XDrawString(display, window, gc, 10, 20, shape_info, strlen(shape_info));

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
