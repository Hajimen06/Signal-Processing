#include <stdio.h>
#include <stdlib.h>

#include "../SPutil.h"

int main(int args, char **argv) {
    int line_no;
    COMPLEX *input_1 = cd_file_reader(&line_no, argv[1]);
    printf("line_no == %d\n", line_no);


    // DFT
    COMPLEX *output_1 = DFT(line_no, input_1);


    // high pass filter
    // 100 / 100 * i = 10 >>>> i = 10
    COMPLEX *input_2 = DFT_highpass(line_no, output_1, 10-1);
    c_graph(line_no, input_2, 1000, 30);


    // iDFT
    COMPLEX *output_2 = iDFT(line_no, input_2);

    // graph
    puts("f()");
    c_graph(line_no, output_2, 100, 30);

    free(input_1);
    free(output_1);
    free(input_2);
    free(output_2);
}
