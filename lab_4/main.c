#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);

    printf("1 - внутри, 0 - снаружи: %d\n", (1 <= x && x <= 10));

    int y;
    scanf("%d", &y);

    printf("res = %d", ((y >> 1) & 1));
}
