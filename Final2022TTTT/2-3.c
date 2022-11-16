#include "../FFT.h"

int main() {
    int line_no;
    COMPLEX *data = cd_file_reader(&line_no, "Signal2.txt");

    COMPLEX *ffted = DFT(line_no, data);
    c_print(line_no, ffted, 1);

    COMPLEX *iffted = iDFT(line_no, ffted);
    c_print(line_no, iffted, 1);


    free(data);
    free(ffted);
    free(iffted);
}
