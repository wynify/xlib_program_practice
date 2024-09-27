#include <stdio.h>
#include <string.h>

#include "select_color.h"
#include "shapes.h"

KeyColorMapping colorMappings[] = {
    {XK_r, {255, 0, 0}},   // Червоний
    {XK_g, {0, 255, 0}},   // Зелений
    {XK_b, {0, 0, 255}},   // Синій
    {XK_k, {0, 0, 0}},     // Чорний
    {XK_w, {255, 255, 255}} // Білий
};


void drawColorInputWindow(Display *display, Window window) {
    GC gc = DefaultGC(display, DefaultScreen(display));
    XClearWindow(display, window);

    // Текст для полів вводу
    const char *labels[3] = {"Red (0-255): ", "Green (0-255): ", "Blue (0-255): "};
    for (int i = 0; i < 3; i++) {
        XDrawString(display, window, gc, 50, 50 + (i * 30), labels[i], strlen(labels[i]));
    }

    // Задайте область для вводу значень
    XFlush(display);
}

void selectColor(Display *display, Window window, unsigned long *current_color) {
    int red = 0, green = 0, blue = 0;

    // Виклик функції для відображення полів вводу
    drawColorInputWindow(display, window);

    // Зчитування значень RGB з вводу (примітивно для демонстрації)
    printf("RED: (0-255): ");
    scanf("%d", &red);
    printf("GREEN (0-255): ");
    scanf("%d", &green);
    printf("BLUE (0-255): ");
    scanf("%d", &blue);

    // Перевірка вхідних значень
    if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) {
        printf("RGB int's must be in range from 0 to 255.\n");
        return;
    }

    // Зберігання кольору
    *current_color = (red << 16) | (green << 8) | blue;

    // Виведення вибраного кольору
    printf("Вибраний колір: R=%d, G=%d, B=%d\n", red, green, blue);
}

int isValidColor(int red, int green, int blue) {
    return (red >= 0 && red <= 255) && (green >= 0 && green <= 255) && (blue >= 0 && blue <= 255);
}