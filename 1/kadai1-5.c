#include <stdio.h>
#include <stdlib.h>

#include "../SPutil.h"

int main(int args, char **argv) {
    int line_no;
    double *input_1 = d_file_reader(&line_no, argv[1]);


    // DCT
    double *output_1 = DCT(line_no, input_1);


    // ryousika
    for (int i = 0; i < line_no; ++i) {
        output_1[i] = floor(output_1[i] / 20.0 + 0.5) * 20;
    }


    // iDCT
    double *input_2 = output_1;
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
