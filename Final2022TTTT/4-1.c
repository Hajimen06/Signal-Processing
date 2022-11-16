#include "../FFT.h"

int main() {
    int line_no;
    COMPLEX *data = cd_file_reader(&line_no, "Signal4.txt");

    //c_graph(line_no, data, 1, 30);

    COMPLEX *ffted = FFT(line_no, data);
    COMPLEX *hp = DFT_highpass(line_no, ffted, 11);
    //c_print(line_no, hp, 1);

    COMPLEX *iffted = iFFT(line_no, hp);
    //c_print(line_no, iffted, 1);
    c_graph(line_no, iffted, 1, 30);





    free(data);
    free(ffted);
    free(hp);
    free(iffted);
}
