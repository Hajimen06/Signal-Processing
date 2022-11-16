#include "../FFT.h"

int main() {
    int height = 2048, width = 2048;
    COMPLEX *data = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (0 <= i < 1024 && 0 <= j < 1024) {
                data[get_label(i, j, width)].rn = 1;
                data[get_label(i, j, width)].in = 0;
            }
            else if (1024 <= i < 2048 && 0 <= j < 1024) {
                data[get_label(i, j, width)].rn = -2;
                data[get_label(i, j, width)].in = 0;
            }
            else if (0 <= i < 1024 && 1024 <= j < 2048) {
                data[get_label(i, j, width)].rn = -3;
                data[get_label(i, j, width)].in = 0;
            }
            else if (1024 <= i < 2048 && 1024 <= j < 2048) {
                data[get_label(i, j, width)].rn = 4;
                data[get_label(i, j, width)].in = 0;
            }
        }
    }

    COMPLEX *ffted = FFT_2(height, width, data);
    // printf("%f    %f\n", ffted[get_label(0, 0, width)].rn, ffted[get_label(0,
    // 0, width)].in);
    //printf("%f    %f\n", ffted[get_label(99, 99, width)].rn,
    // ffted[get_label(99, 99, width)].in);


    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%f   %f\n", ffted[get_label(i, j, width)].rn,
                   ffted[get_label(i, j, width)].in);
        }
    }

    free(data);
    free(ffted);
}
