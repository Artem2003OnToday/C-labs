#include <ctype.h>
#include <stdio.h>

void calc(char *s) {
    int digit = 0;
    int upper = 0;
    int lower = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        digit += isdigit(s[i]);
        upper += isupper(s[i]);
        lower += islower(s[i]);
    }

    printf("digit = %d, upper = %d, lower = %d\n", digit, upper, lower);
}

int main() {
    { // 1
        char s[100];
        scanf("%s", s);

        calc(s);
    }
    { // 2
        int duration, subscription_fee, another_fee;
        int free_duration = 499;
        scanf("%d%d%d", &duration, &subscription_fee, &another_fee);

        if (1. * subscription_fee / free_duration > another_fee) {
            printf("something went wrong, another_fee must be more than subscription_fee / free_duration");
            return 0;
        }

        int res = 0.;
        if (free_duration >= duration) {
            res = subscription_fee;
        }
        if (duration - free_duration > 0) {
            res += (duration - free_duration) * another_fee;
        }

        printf("final cost is %d\n", res);
    }
}