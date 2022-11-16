#include "../FFT.h"

int main(int args, char **argv) {

    // input
    int line_no;
    COMPLEX *input = cd_file_reader(&line_no, argv[1]);

    COMPLEX *f_256 = (COMPLEX *)malloc(sizeof(COMPLEX) * 256);
    COMPLEX *l_256 = (COMPLEX *)malloc(sizeof(COMPLEX) * 256);

    for (int i = 0; i < 256; ++i) {
        f_256[i] = input[i];
    }

    for (int i = 0; i < 256; ++i) {
        l_256[i] = input[line_no - 256 + i];
    }


    // FFT
    COMPLEX *f_FFT = FFT(256, f_256);
    COMPLEX *l_FFT = FFT(256, l_256);


    // power
    double *f_pow = DFT_power(256, f_FFT);
    double *l_pow = DFT_power(256, l_FFT);

    d_graph(256, f_pow, 10000, 30);
    puts("next.");
    d_graph(256, l_pow, 10000, 30);


    free(input);
    free(f_256);
    free(l_256);
    free(f_FFT);
    free(l_FFT);
    free(f_pow);
    free(l_pow);
}
/*
100 / 256 * 26 = 10.15
100 / 256 * 51 = 19.92
*/