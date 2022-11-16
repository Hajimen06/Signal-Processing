#include "../FFT.h"

int main() {
    int size = 128;
    COMPLEX *data = (COMPLEX *)malloc(sizeof(COMPLEX) * size);
    for (int i = 0; i < size; ++i) {
        if (i < size / 2)
            data[i].rn = -1;
        else
            data[i].rn = 1;
        data[i].in = 0;
    }

    COMPLEX *ffted = FFT(size, data);

    COMPLEX *ahp = DFT_highpass(size, ffted, 11);
    //COMPLEX *ahp = DFT_lowpass(size, ffted, 5);
    COMPLEX *aiffted = iFFT(size, ahp);
    c_graph(size, aiffted, 1.5, 30);


    free(data);
    free(ffted);
    free(ahp);
    free(aiffted);
}
