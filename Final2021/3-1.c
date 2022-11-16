#include "../SPutil.h"

int main() {
    int height = 8, width = 8;
    double *data = d_file_reader_2(height, width, "Signal2.txt");

    double *dcted2 = DCT_2(height, width, data);
    d_print_2(height, width, dcted2, 2);

    double *idcted2 = iDCT_2(height, width, dcted2);
    d_print_2(height, width, idcted2, 2);

    free(data);
    free(dcted2);
    free(idcted2);
}
