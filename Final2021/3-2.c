#include "../FFT.h"

int main() {
    int height = 8, width = 8;
    COMPLEX *data = cd_file_reader_2(height, width, "Signal2.txt");

    COMPLEX *ffted = FFT_2(height, width, data);
    c_print_2(height, width, ffted, 2);

    COMPLEX *iffted = iFFT_2(height, width, ffted);
    c_print_2(height, width, iffted, 2);

    free(data);
    free(ffted);
}
