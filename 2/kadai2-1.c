#include "../SPutil.h"

COMPLEX f(int k) {
    COMPLEX c, c1;
    if (k == 0) {
        c.rn = 2;
        c.in = 1;
        return c;
    }

    c = f(k - 1);
    c1.rn = 1 * c.rn - 2 * c.in;
    c1.in = 1 * c.in + 2 * c.rn;
    return c1;
}

int main() {
    int k;
    scanf("%d", &k);
    COMPLEX c = f(k);
    printf("f(%d) == %f + j(%f)\n", k, c.rn, c.in);
}
