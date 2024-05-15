#include <stdio.h>
#include <math.h>

#define pow2(x) ((x) * (x))
#define PI 3.14159265358979323846

double to_radian(double grad) {
    return grad / 180 * PI;
}

double calc_1(double alp) {
    return 2 * pow2(sin(3 * PI - 2 * alp)) * pow2(cos(5 * PI + 2 * alp));
}

double calc_2(double alp) {
    return 1./4. - 1./4. * sin(5. / 2. - 8 * alp);
}

int main() {
    double alp = 0.;
    scanf("%lf", &alp);

    printf("z1 = %f, z2 = %f", calc_1(alp), calc_2(alp));
}
