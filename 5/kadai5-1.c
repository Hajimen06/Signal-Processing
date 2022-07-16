#include <stdio.h>
#include <stdlib.h>
#include "../SPutil.h"
#include "../CSVutil.h"
//#include "dct.h"

int main(int args, char **argv) {
    if (args == 0) return 0;

    int line_no;
    double *csv;
    if ((line_no = csv_reader(&csv, argv[1])) == 0)  {
        return 0;
    }


    double *dct_out = DCT(line_no, csv);
    //dct(csv, line_no);
    puts("DCT done.");
    double *lowpass = DCT_lowpass(line_no, dct_out, 2000);
    //double *lowpass = DCT_lowpass(line_no, csv, 2000);
    puts("lowpass done.");
    double *idct_out = iDCT(line_no, lowpass);
    puts("iDCT done.");

    if(csv_writer(line_no, idct_out, argv[2]))
        puts("done.");
    else
        puts("failed");

    //free(dct_out);
    free(csv);
    free(lowpass);
    free(idct_out);
}
