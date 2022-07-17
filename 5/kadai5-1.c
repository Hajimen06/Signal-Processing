#include <stdio.h>
#include <stdlib.h>
#include "../SPutil.h"
#include "../FFT.h"


int main(int args, char **argv) {
    if (args == 0) return 0;

    int line_no;
    COMPLEX *csv;
    if ((csv = c_csv_reader(&line_no, argv[1])) == NULL)  {
        return 0;
    }


    COMPLEX *fft_out = FFT(line_no, csv);
    puts("FFT done.");

    COMPLEX *lowpass = DFT_lowpass(line_no, fft_out, 2000);
    puts("lowpass done.");

    COMPLEX *ifft_out = iFFT(line_no, lowpass);
    puts("iFFT done.");


    if(c_csv_writer(line_no, ifft_out, "ifft.csv"))
        puts("done.");
    else
        puts("failed");


    free(csv);
    free(fft_out);
    free(lowpass);
    free(ifft_out);
}
