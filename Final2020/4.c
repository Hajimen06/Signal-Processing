#include "../FFT.h"

int main() {
    int line_no;
    double *data = d_file_reader(&line_no, "signal4.txt");
    printf("%d\n", line_no);

    double *dcted = DCT(line_no, data);

    double *hp = DCT_highpass(line_no, dcted, 19);
    double *lp = DCT_lowpass(line_no, hp, 205);
    //d_print(line_no, lp, 1);

    double *idcted = iDCT(line_no, lp);
    d_print(line_no, idcted, 1);

    free(data);
    free(dcted);
    free(hp);
    free(lp);
    free(idcted);
}
