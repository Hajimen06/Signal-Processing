#include "../FFT.h"

int main() {
    int line_no;
    double *data = d_file_reader(&line_no, "Signal2.txt");

    double *dcted = DCT(line_no, data);
    d_print(line_no, dcted, 1);

    double *idcted = iDCT(line_no, dcted);
    d_print(line_no, idcted, 1);


    free(data);
    free(dcted);
    free(idcted);
}
