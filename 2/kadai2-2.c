#include <stdlib.h>

#include "../SPutil.h"
#include "../FFT.h"

int main() {
    int q;
    puts("---Manual Calculator---");
    puts("Input number. (DFT : 0, iDFT : 1)");
    printf(">>");
    scanf("%d", &q);
    puts("");

    if (q == 0) {
        puts("---Calculate DFT---");

        int n;
        puts("1: Input number of values.");
        printf(">>");
        scanf("%d", &n);
        puts("");

        COMPLEX *input = (COMPLEX *)malloc(sizeof(COMPLEX) * n);
        puts("2: Input f(x) values to calculate.");
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &input[i].rn);
            scanf("%lf", &input[i].in);
        }
        puts("");

        //COMPLEX *output = DFT(n, input);
        COMPLEX *output = FFT(n, input);
        puts("Calculated.");
        for (int i = 0; i < n; ++i) {
            printf("%f %f\n", output[i].rn, output[i].in);
        }
        puts("Formed.");
        for (int i = 0; i < n; ++i) {
            printf("    F(%d) == %f + j(%f)\n", i, output[i].rn, output[i].in);
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

        COMPLEX *input = (COMPLEX *)malloc(sizeof(COMPLEX) * n);
        puts("2: Input F(x) values to calculate.");
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &input[i].rn);
            scanf("%lf", &input[i].in);
        }
        puts("");

        COMPLEX *output = iDFT(n, input);
        puts("Calculated.");
        for (int i = 0; i < n; ++i) {
            printf("%f %f\n", output[i].rn, output[i].in);
        }
        puts("Formed.");
        for (int i = 0; i < n; ++i) {
            printf("    f(%d) == %f + j(%f)\n", i, output[i].rn, output[i].in);
        }

        free(input);
        free(output);
    }
}
