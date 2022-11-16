#include "../SPutil.h"

int main() {
    int line_no;
    double *data = d_file_reader(&line_no, "Signal1.txt");
    printf("%d\n", line_no);

    double *dcted = DCT(line_no, data);
    double *idcted = iDCT(line_no, dcted);

    // d_print(line_no, dcted, 1);
    d_print(line_no, idcted, 1);

    free(data);
    free(dcted);
    free(idcted);
}
