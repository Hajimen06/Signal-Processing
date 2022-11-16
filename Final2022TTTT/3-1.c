#include "../FFT.h"

int main() {
    int line_no;
    COMPLEX *data = cd_file_reader(&line_no, "Signal3.txt");

    COMPLEX *ffted = FFT(line_no, data);
    double *power = DFT_power(line_no, ffted);
    //d_print(line_no, power, 1);
    d_graph(line_no, power, 1000000, 30);


    free(data);
    free(ffted);
    free(power);
}
