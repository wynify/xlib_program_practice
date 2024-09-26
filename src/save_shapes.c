/*#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"


void saveShape(Shape *shapes, int shapes_count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(&shapes_count, sizeof(int), 1, file);
        fwrite(shapes, sizeof(Shape), shapes_count, file);
        fclose(file);
    }
}

int loadCircles(Shape *shapes, int max_shapes, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return 0;
    }

    int shapes_count;
    fread(&shapes_count, sizeof(int), 1, file);
    if (shapes_count > max_shapes) {
        shapes_count = max_shapes;
    }
    fread(shapes, sizeof(Shape), shapes_count, file);
    fclose(file);
    return shapes_count;
}*/