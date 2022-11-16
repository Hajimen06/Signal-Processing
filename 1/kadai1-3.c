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

        puts("2: Input f(x) values to calculate.");
        puts(">>");

        double *input = d_cin(n);

        double *output = DCT(n, input);

        puts("Calculated.");
        d_print(n, output, 0);
        d_print(n, output, 1);


        free(input);
        free(output);
    }
    else if (q == 1) {
        puts("---Calculate iDCT---");

        int n;
        puts("1: Input number of values.");
        printf(">>");
        scanf("%d", &n);

        puts("2: Input C(x) values to calculate.");
        puts(">>");

        double *input = d_cin(n);

        double *output = iDCT(n, input);

        puts("Calculated.");
        d_print(n, output, 0);
        d_print(n, output, 1);

        free(input);
        free(output);
    }
}
