#include "../SPutil.h"
#include "../FFT.h"

int main() {
    int m;
    puts("input mode, (0: DFT_2, 1: iDFT_2)");
    printf(">>");
    scanf("%d", &m);

    int height, width;
    puts("input height");
    printf(">>");
    scanf("%d", &height);
    puts("input width");
    printf(">>");
    scanf("%d", &width);


    puts("input values");


    COMPLEX *input;
    COMPLEX *result;
    // DCT
    if (m == 0) {
        input = c_cin_2_aut(height, width);
        result = DFT_2(height, width, input);
        //result = FFT_2(height, width, input);
    }
    if (m == 1) {
        input = c_cin_2(height, width);
        result = iDFT_2(height, width, input);
        //result = iFFT_2(height, width, input);
    }

    c_print_2(height, width, result, 0);


    free(input);
    free(result);
}
