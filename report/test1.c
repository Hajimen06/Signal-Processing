#include <time.h>

#include "../FFT.h"

int main() {

    // gen data
    int data_no = 4096;
    COMPLEX *data = (COMPLEX *)malloc(sizeof(COMPLEX) * data_no);
    for (int i = 0; i < data_no; ++i) {
        data[i].rn = i % 4 + i * i % 8;
        data[i].in = 0;
    }

    clock_t start, end;

    // DFT
    start = clock();
    COMPLEX *dftout = DFT(data_no, data);
    end = clock();
    printf("DFT : %.2f ms\n", (double)(end - start));

    // FFT
    start = clock();
    COMPLEX *fftout = FFT(data_no, data);
    end = clock();
    printf("FFT : %.2f ms\n", (double)(end - start));


    free(dftout);
    free(fftout);
}
