#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pow2(x) ((x) * (x))

const int INF = -1e9;

int gcd(int a, int b) {
    return !a ? b : gcd(b % a, a);
}

long long lcm(int a, int b) {
    return 1ll * a * b / gcd(a, b);
}

struct Point {
    double x, y;
};

double distance(struct Point a, struct Point b) {
    return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y));
}

void make_sol(int n, struct Point *a) {
    double *b = (double*)malloc(n * (n - 1) * sizeof(double));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                b[i * n + j] = INF;
                continue;
            }
            b[i * n + j] = distance(a[i], a[j]);
        }
    }
}

int main() {
    { // 1
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", gcd(a, b));
        printf("%lld\n", lcm(a, b));
    }
    { // 2
        int n;
        scanf("%d", &n);
        struct Point a[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &a[i].x, &a[i].y);
        }

        make_sol(n, a);
    }
}