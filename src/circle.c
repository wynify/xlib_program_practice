#include "circle.h"
#include <X11/Xlib.h>

void drawCircles(Display *display, Window window, GC gc, Circle *circles, int circle_count) {
    for (int i = 0; i < circle_count; i++) {
        XSetForeground(display, gc, circles[i].color);
        XDrawArc(display, window, gc, circles[i].x - 25, circles[i].y - 25, 50, 50, 0, 360 * 64);
    }
}

void addCircle(Circle *circles, int *circle_count, int x, int y, unsigned long color) {
    circles[*circle_count].x = x;
    circles[*circle_count].y = y;
    circles[*circle_count].color = color;
    (*circle_count)++;
}

void saveCircles(Circle *circles, int circle_count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(&circle_count, sizeof(int), 1, file);
        fwrite(circles, sizeof(Circle), circle_count, file);
        fclose(file);
    }
}

int loadCircles(Circle *circles, int max_circles, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return 0;
    }

    int circle_count;
    fread(&circle_count, sizeof(int), 1, file);
    if (circle_count > max_circles) {
        circle_count = max_circles;
    }
    fread(circles, sizeof(Circle), circle_count, file);
    fclose(file);
    return circle_count;
}