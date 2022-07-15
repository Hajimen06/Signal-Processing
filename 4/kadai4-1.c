#include "../SPutil.h"

int main() {
    int m;
    puts("input mode, (0: DCT_2, 1: iDCT_2)");
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
    double *input = d_cin_2(height, width);


    double *result;
    // DCT
    if (m == 0) {
        result = DCT_2(height, width, input);
    }
    if (m == 1) {
        result = iDCT_2(height, width, input);
    }

    d_print_2(height, width, result, 0);


    free(input);
    free(result);
}
