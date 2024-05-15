#ifndef LAB_11_H_
#define LAB_11_H_

typedef struct {
    double x, y;
} Point;

typedef struct Rectangle {
    Point a, b;
} Rectangle;

double get_square(const Rectangle r);

double get_perimeter(const Rectangle r);

Rectangle create_rectangle_from_console();

#endif
