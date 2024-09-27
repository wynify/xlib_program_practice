// save_shapes.c
#include <stdio.h>
#include "shapes.h"

void saveShapes(Shape *shapes, int shape_count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error when save file");
        return;
    }
    fwrite(&shape_count, sizeof(int), 1, file);
    fwrite(shapes, sizeof(Shape), shape_count, file);
    fclose(file);
}

int loadShapes(Shape *shapes, int max_shapes, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    int shape_count;
    fread(&shape_count, sizeof(int), 1, file);
    fread(shapes, sizeof(Shape), shape_count, file);
    fclose(file);
    return shape_count;
}
