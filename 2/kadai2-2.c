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

        // input
        puts("input");
        COMPLEX *input = c_cin_aut(n);


        //COMPLEX *output = DFT(n, input);
        COMPLEX *output = FFT(n, input);
        puts("Calculated.");
        c_print(n, output, 0);
        c_print(n, output, 1);

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

        // input
        puts("input");
        COMPLEX *input = c_cin(n);


        // iDFT
        //COMPLEX *output = iDFT(n, input);
        COMPLEX *output = iFFT(n, input);

        puts("Calculated.");
        c_print(n, output, 0);
        c_print(n, output, 1);

        free(input);
        free(output);
    }
}
