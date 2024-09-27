// shapes.h
#ifndef SHAPES_H
#define SHAPES_H

#include <X11/Xlib.h>

typedef enum {
    CIRCLE,
    RECTANGLE,
    TRIANGLE
} ShapeType;

typedef struct {
    int x, y;            // Координати центру
    unsigned long color; // Колір
    ShapeType type;      // Тип фігури
    int width, height;   // Розміри
    int base;
} Shape;



extern int is_filled;  

// Функції малювання
void drawShapes(Display *display, Window window, GC gc, Shape *shapes, int shape_count);
void drawShape(Display *display, Window window, GC gc, Shape shape);
void addShape(Shape *shapes, int *shape_count, int x, int y, unsigned long color, ShapeType type, int width, int height);

void saveShapes(Shape *shapes, int shape_count, const char *filename);
int  loadShapes(Shape *shapes, int max_shapes, const char *filename);


#endif // SHAPES_H