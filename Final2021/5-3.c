#include "../FFT.h"

double f5(double t) {
    return 10 * sin(12.34 * M_PI * t) +
           2 * cos(56.78 * M_PI * t + 8.901 * M_PI);
}

int main() {
    int line_no = 64;
    COMPLEX *data = (COMPLEX *)malloc(sizeof(COMPLEX) * line_no);

    for (int i = 0; i < line_no; ++i) {
        data[i].rn = f5(i / 41.0);
        data[i].in = 0;
    }

    COMPLEX *ffted = FFT(line_no, data);
    double *power = DFT_power(line_no, ffted);

    d_graph(line_no, power, 65000, 30);


    free(data);
    free(ffted);
    free(power);
}
