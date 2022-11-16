#include <stdio.h>
#include <stdlib.h>

#include "../SPutil.h"

int main(int args, char **argv) {

    // input
    int line_no;
    COMPLEX *input_1 = cd_file_reader(&line_no, argv[1]);
    printf("line_no == %d\n", line_no);


    // DFT
    COMPLEX *output_1 = DFT(line_no, input_1);


    // power
    // 500 / (500 * 2) * i = 2 >>>> i = 4
    // 500 / (500 * 2) * i = 4 >>>> i = 8
    // 500 / (500 * 2) * i = 15 >>>> i = 30
    // 500 / (500 * 2) * i = 17 >>>> i = 34
    // 500 / (500 * 2) * i = 61 >>>> i = 122
    // 500 / (500 * 2) * i = 63 >>>> i = 126
    double *value = DFT_power(line_no, output_1);


    double max = 0;
    for (int i = 0; i < line_no; ++i) {
        if ((4 <= i && i <= 8) || (30 <= i && i <= 34) ||
            (122 <= i && i <= 126)) {
            if(max < value[i]) max = value[i];
            printf("(%3d) == %f\n", i, value[i]);
        }
    }
    printf("   %f", max);

    free(input_1);
    free(output_1);
    free(value);
}
