#include "shapes.h"


void draw_shapes(Display *dispay, Window window, GC gc, Shape shape[], int shape_count){
    for (int i = 0; i < shape_count; i++)
    {
        XSetForeground(dispay, gc, shape[i].color);
        if(shape[i].shape == 0){
            XDrawArc(dispay, window, gc, shape[i].x - 25, shape[i].y - 25, 50, 50, 0, 360 * 64);
        } else if (shape[i].shape == 1){
            XDrawRectangle(dispay, window, gc, shape[i].x - 25, shape[i].y - 25, 50, 50);
        }
    }
}

void handle_keypress(XEvent event, Display *display, int screen, unsigned long *current_color,
int *current_shape, int *shape_count, Window window){
    KeySym key = XLookupKeysym(&event.xkey, 0);

    if(key == XK_r){
        *current_color = 0xFF0000;
    } else if (key == XK_g) {
        *current_color = 0x00FF00;
    } else if (key == XK_b){
        *current_color = 0x0000FF;
    } else if (key == XK_w){
        *current_color = WhitePixel(display, screen);
    } else if (key == XK_w){
        *current_color = BlackPixel(display, screen);
    } else if (key == XK_q){
        XClearWindow(display, window);
        *shape_count = 0;
    } else if (key == XK_s){
        *current_shape = 1;
    } else if (key == XK_c){
        *current_shape = 0;
    }
}

void handler_buttonpress(XEvent event, Shape shapes[], int * shape_count, unsigned long current_color,
int current_shape) {
    if(event.xbutton.button == Button1 && *shape_count < MAX_SHAPES){
        shapes[*shape_count].x = event.xbutton.x;
        shapes[*shape_count].y = event.xbutton.y;
        shapes[*shape_count].color = current_color;
        shapes[*shape_count].shape = current_shape;
        (*shape_count)++;
    }
}