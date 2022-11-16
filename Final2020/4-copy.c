#include "../FFT.h"

int main() {
    int line_no;
    COMPLEX *data = cd_file_reader(&line_no, "signal4.txt");
    printf("%d\n", line_no);

    COMPLEX *dcted = FFT(line_no, data);

    COMPLEX *hp = DFT_highpass(line_no, dcted, 19);
    COMPLEX *lp = DFT_lowpass(line_no, hp, 205);
    //c_print(line_no, lp, 1);

    COMPLEX *idcted = iFFT(line_no, lp);
    c_print(line_no, idcted, 1);

    free(data);
    free(dcted);
    free(hp);
    free(lp);
    free(idcted);
}
