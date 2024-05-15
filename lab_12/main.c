#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect data, need your name");
        return 1;
    }

    const char* name = argv[1];
    FILE *f = fopen(name, "r");
    if (f == NULL) {
        printf("Cannot open file, %s", name);
        return 1;
    }

    int sz = 256, i = 0;
    char buffer[sz];
    while (fgets(buffer, sz, f) != NULL) {
        if (i % 2 == 0) {
            printf("%s", buffer);
        }
        i++;
    }

    fclose(f);
}