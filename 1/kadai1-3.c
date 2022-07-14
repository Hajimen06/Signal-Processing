#include <stdio.h>
#include <stdlib.h>

#include "..\SPutil.h"

int main() {
    int q;
    puts("---Manual Calculator---");
    puts("Input number. (DCT : 0, iDCT : 1)");
    printf(">>");
    scanf("%d", &q);
    puts("");

    if (q == 0) {
        puts("---Calculate DCT---");

        int n;
        puts("1: Input number of values.");
        printf(">>");
        scanf("%d", &n);
        puts("");

        double *input = (double *)malloc(sizeof(double) * n);
        puts("2: Input f(x) values to calculate.");
        printf(">>");
        for (int i = 0; i < n; ++i)
            scanf("%lf", &input[i]);
        puts("");

        double *output = DCT(n, input);
        puts("Calculated.");
        for (int i = 0; i < n; ++i) {
            printf("%f\n", output[i]);
        }
        for (int i = 0; i < n; ++i) {
            printf("    C(%d) == %f\n", i, output[i]);
        }

        free(input);
        free(output);
    }
    else if (q == 1) {
        puts("---Calculate iDCT---");

        int n;
        puts("1: Input number of values.");
        printf(">>");
        scanf("%d", &n);
        puts("");

        double *input = (double *)malloc(sizeof(double) * n);
        puts("2: Input C(x) values to calculate.");
        printf(">>");
        for (int i = 0; i < n; ++i)
            scanf("%lf", &input[i]);
        puts("");

        double *output = iDCT(n, input);
        puts("Calculated.");
        for (int i = 0; i < n; ++i) {
            printf("%f\n", output[i]);
        }
        for (int i = 0; i < n; ++i) {
            printf("    f(%d) == %f\n", i, output[i]);
        }

        free(input);
        free(output);
    }
}
