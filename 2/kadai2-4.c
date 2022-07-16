#include <stdio.h>
#include <stdlib.h>

#include "../SPutil.h"
#include "../FFT.h"

int main(int args, char **argv) {
    int line_no;
    COMPLEX *input_1 = c_file_reader(&line_no, argv[1]);

    // DFT
    printf("line_no == %d\n", line_no);
    //COMPLEX *output_1 = DFT(line_no, input_1);
    COMPLEX *output_1 = FFT(line_no, input_1);

    // power
    double *to_graph = DFT_power(line_no, output_1);

    // graph
    d_graph(line_no / 2 + 1, to_graph, 4000, 30);

    free(input_1);
    free(output_1);
}
// 10 / (10 * 25) * 20 = 4 / 5