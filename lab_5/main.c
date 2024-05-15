#include <stdio.h>

int main() {
    { // 1
        int n = 7;
        int a[n];
        for (int i = 1; i <= n; i++) {
            a[i - 1] = 10 * i;
        }

        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    { // 2
        int a[2][2] = {{1, 2}, {3, 4}};
        int b[2][2] = {{1, 1}, {2, 1}};
        int c[2][2] = {{0, 0}, {0, 0}};

        int n = 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int* res = &c[i][j];
                for (int k = 0; k < n; k++) {
                    *res += a[i][k] * b[k][j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }
}
