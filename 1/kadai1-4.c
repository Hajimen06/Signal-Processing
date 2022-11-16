#include <stdio.h>
#include <stdlib.h>

#include "../SPutil.h"

int main(int args, char **argv) {
    int line_no;
    double *input_1 = d_file_reader(&line_no, argv[1]);


    // DCT
    double *output_1 = DCT(line_no, input_1);


    // lowpass filter
    double *input_2 = DCT_lowpass(line_no, output_1, 20);


    // iDCT
    double *output_2 = iDCT(line_no, input_2);


    // graph
    d_graph(line_no, input_1, 180, 30);
    puts("");

    d_graph(line_no, output_2, 180, 30);
    puts("");

    free(input_1);
    free(output_1);
    free(output_2);
}
