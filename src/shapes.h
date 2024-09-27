// shapes.h
#ifndef SHAPES_H
#define SHAPES_H

#include <X11/Xlib.h>

typedef enum {
    CIRCLE,
    RECTANGLE,
    ELLIPSE
} ShapeType;

typedef struct {
    int x, y;            // Координати центру
    unsigned long color; // Колір
    ShapeType type;      // Тип фігури
    int width, height;   // Розміри
} Shape;

extern int is_filled; 

void drawShapes(Display *display, Window window, GC gc, Shape *shapes, int shape_count);
void addShape(Shape *shapes, int *shape_count, int x, int y, unsigned long color, ShapeType type, int width, int height);


#endif // SHAPES_H