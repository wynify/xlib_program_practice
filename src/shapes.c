#include "shapes.h"
#include <X11/Xlib.h>

int is_filled = 0;

void drawShapes(Display *display, Window window, GC gc, Shape *shapes, int shape_count) {
    for (int i = 0; i < shape_count; i++) {
        XSetForeground(display, gc, shapes[i].color);
        switch (shapes[i].type) {
            case CIRCLE:
                if(is_filled){
                XFillArc(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2,
                         shapes[i].width, shapes[i].height, 0, 360 * 64);
                } else {
                XDrawArc(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2,
                         shapes[i].width, shapes[i].height, 0, 360 * 64);
                }
                break;
            case RECTANGLE:
                if(is_filled){
                XFillRectangle(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2,
                               shapes[i].width, shapes[i].height);
                } else {
                XDrawRectangle(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2,
                               shapes[i].width, shapes[i].height);     
                }
                break;
            case ELLIPSE:
                if(is_filled){
                XFillArc(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 4,
                         shapes[i].width, shapes[i].height, 0, 360 * 64);
                } else {
                XDrawArc(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 4,
                         shapes[i].width, shapes[i].height, 0, 360 * 64);
                }
                break;
        }
    }
}

void addShape(Shape *shapes, int *shape_count, int x, int y, unsigned long color, ShapeType type, int width, int height) {
    shapes[*shape_count].x = x;
    shapes[*shape_count].y = y;
    shapes[*shape_count].color = color;
    shapes[*shape_count].type = type;
    shapes[*shape_count].width = width;
    shapes[*shape_count].height = height;
    (*shape_count)++;
}

/*
#include <X11/Xlib.h>
#include "shapes.h"

void drawShape(Display *display, Window window, GC gc, Shape *shapes, int shape_count) {
    for (int i = 0; i < shape_count; i++)
    {
        XSetForeground(display, gc, shapes[i].color);
        switch(shapes[i].type){
            case CIRCLE:
                XDrawArc(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2, 
                         shapes[i].width, shapes[i].height, 0, 360 * 64);
                    break;
            case RECTANGLE:
                XDrawRectangle(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2,
                               shapes[i].width, shapes[i].height);
                break;
            case ELLIPSE:
                XDrawArc(display, window, gc, shapes[i].x - shapes[i].width / 2, shapes[i].y - shapes[i].height / 2,
                         shapes[i].width, shapes[i].height, 0, 360 * 64);
                break;
        }
    }
}

void addShape(Shape *shapes, int *shape_count, int x, int y, unsigned long color, ShapeType type, int width, int height){
    shapes[*shape_count].x = x;
    shapes[*shape_count].y = y;
    shapes[*shape_count].type = type;
    shapes[*shape_count].color = color;
    shapes[*shape_count].width = width;
    shapes[*shape_count].height = height;
    (*shape_count)++;
}
*/