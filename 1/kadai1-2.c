#include <math.h>
#include <stdio.h>

double f(int k) {
    double result = 0;
    for (int i = 0; i < k; ++i) {
        result += sin(i / 100.0 * M_PI);
    }
    return result;
}

int main() {
    printf("%f\n", f(30));
    printf("%f\n", f(50));
}
