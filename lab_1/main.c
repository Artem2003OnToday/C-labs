#include <stdio.h>

int main() {
    int q;
    printf("выберите вариант ввода, 1 - число, 2 - строка: ");
    scanf("%d", &q);

    if (q == 1) {
        int x;
        printf("введите число: ");
        scanf("%d", &x);
    } else {
        char s[31];
        printf("ввыдите строку: ");
        scanf("%30s", s);
    }
}
