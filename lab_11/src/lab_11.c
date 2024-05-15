#include "../include/lab_11.h"
#include "../include/lab_11.h"
#include <math.h>
#include <stdio.h>

double get_square(const Rectangle r) {
    return fabs(r.a.x - r.b.x) * fabs(r.a.y - r.b.y);
}

double get_perimeter(const Rectangle r) {
    return 2 * fabs(r.a.x - r.b.x) + 2 * fabs(r.a.y - r.b.y);
}

Rectangle create_rectangle_from_console() {
    Rectangle rect;
    printf("You need to write 2 points for your rectangle: ");
    scanf("%lf%lf%lf%lf", &rect.a.x, &rect.a.y, &rect.b.x, &rect.b.y);
    return rect;
}
