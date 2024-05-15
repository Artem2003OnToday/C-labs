#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char* concatenate(char *a, char *b) {
    unsigned long a_size = strlen(a);
    unsigned long b_size = strlen(b);
    char *c = (char*)malloc((a_size + b_size + 1) * sizeof(char));
    for (int i = 0; i < a_size; i++) {
        c[i] = a[i];
    }
    for (int i = 0; i < b_size; i++) {
        c[a_size + i] = b[i];
    }
    return c;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool compare(char *a, char *b) { // like operator <
    unsigned long a_size = strlen(a);
    unsigned long b_size = strlen(b);
    for (int i = 0; i < min(a_size, b_size); i++) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return a_size < b_size;
}

void copy_string(char *a, char *b) {


    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

unsigned long strsize(char *a) {
    unsigned long i = 0;
    while (a[i] != '\0') {
        i++;
    }
    return i;
}

int find_last(char *a, char c) {
    int last = -1;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == c) {
            last = i;
        }
    }

    return last;
}

int main() {
    { // 1
        char a[100], b[100];
        scanf("%s%s", a, b);
        printf("%s\n", concatenate(a, b));
    }
    { // 2
        char a[100], b[100];
        scanf("%s%s", a, b);
        printf("%d\n", compare(a, b));
    }
    { // 3
        char a[100], b[100];
        scanf("%s%s", a, b);
        copy_string(a, b);

        printf("%s, %s\n", a, b);
    }
    { // 4
        char a[100];
        scanf("%s", a);

        printf("%lu, %lu\n", strsize(a), strlen(a));
    }
    { // 5
        char a[100], c;
        scanf("%s\n%c", a, &c);

        printf("%d", find_last(a, c));
    }
}
