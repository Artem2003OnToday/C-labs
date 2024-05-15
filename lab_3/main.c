#include <stdio.h>

int num_to_10(int x) {
    int res = 0, p = 1;
    while (x) {
        res += (x % 10) * p;
        p *= 8;
        x /= 10;
    }
    return res;
}

int num_to_8(int x) {
    int res[100];
    int i = 0;


    while (x) {
        res[i++] = x % 8;
        x /= 8;
    }

    int ans = 0;
    for (--i; i >= 0; i--) {
        ans = ans * 10 + i;
    }
    return ans;
}

int main() {
    printf("print number at 8 numeral system: ");
    int x;
    scanf("%d", &x);

    printf("x at 8 = %d, x at 10 = %d\n", x, num_to_10(x));
    printf("x at 8 = %d, left on 1 = %d\n", x, (x << 1));
    printf("x at 8 = %d, not x = %d\n", x, !x);

    printf("print another at 8 numeral system: ");
    int y;
    scanf("%d", &y);

    printf("res = %d", num_to_8(num_to_10(x) & num_to_10(y)));
}
