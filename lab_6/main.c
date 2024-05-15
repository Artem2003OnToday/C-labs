#include <stdio.h>
#include <stdlib.h>

int main() {
    { // 1
        const int n = 4;
        char arr[n];
        char *a = arr;

        for (int i = 0; i < n; i++) {
            a[i] = 'a' + i;
        }

        for (int i = 0; i < n; i++) {
            printf("%c ", *(a + i));
        }
        printf("\n");
    }
    { // 2
        const int n = 4;
        char *ptr = (char*)malloc(n * sizeof(char));
        
        for (int i = 0; i < n; i++) {
            ptr[i] = 'a' + i;
        }

        for (int i = 0; i < n; i++) {
            printf("%c ", *(ptr + i));
        }
        printf("\n");

        free(ptr);
    }
}
