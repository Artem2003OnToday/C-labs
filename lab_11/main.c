#include "include/lab_11.h"
#include <stdio.h>

int main() {
    Rectangle rect = create_rectangle_from_console();

    printf("площадь прямоугольника: %f\n", get_square(rect));
    printf("периметр прямоугольника: %f\n", get_perimeter(rect));
}