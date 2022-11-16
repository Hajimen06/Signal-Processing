#include "FFT.h"

int calc_log(int n) {
    int result = 0;
    while (1 < n) {
        n = n >> 1;
        ++result;
    }
    return result;
}

int calc_pow2(int n) {
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result *= 2;
    }
    return result;
}

COMPLEX calc_multi(COMPLEX c1, COMPLEX c2) {
    COMPLEX result;
    result.rn = c1.rn * c2.rn - c1.in * c2.in;
    result.in = c1.rn * c2.in + c1.in * c2.rn;
    return result;
}

int calc_rbit(int digit, int n) {
    int result = 0;
    for (int i = 0; i < digit; ++i) {
        if (n % 2) {
            result <<= 1;
            result += 1;
        }
        else {
            result <<= 1;
        }
        n >>= 1;
    }
    return result;
}

COMPLEX calc_W(int n, int k) {
    COMPLEX result;
    result.rn = cos(2.0 * k * M_PI / n);
    result.in = -sin(2.0 * k * M_PI / n);
    return result;
}

COMPLEX calc_mW(int n, int k) {
    COMPLEX result;
    result.rn = cos(2.0 * k * M_PI / n);
    result.in = sin(2.0 * k * M_PI / n);
    return result;
}

COMPLEX *block_FFT(int block_size, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * block_size);

    for (int i = 0; i < block_size / 2; ++i) {
        output[i] = input[i];

        COMPLEX c = calc_multi(input[block_size / 2 + i], calc_W(block_size, i));
        output[i].rn += c.rn;
        output[i].in += c.in;

        output[block_size / 2 + i].rn = input[i].rn;
        output[block_size / 2 + i].in = input[i].in;
    }
    for (int i = block_size / 2; i < block_size; ++i) {
        COMPLEX c = calc_multi(input[i], calc_W(block_size, i));
        output[i].rn += c.rn;
        output[i].in += c.in;
    }
    return output;
}

COMPLEX *block_iFFT(int block_size, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * block_size);

    for (int i = 0; i < block_size / 2; ++i) {
        output[i] = input[i];

        COMPLEX c = calc_multi(input[block_size / 2 + i], calc_mW(block_size, i));
        output[i].rn += c.rn;
        output[i].in += c.in;

        output[block_size / 2 + i].rn = input[i].rn;
        output[block_size / 2 + i].in = input[i].in;
    }
    for (int i = block_size / 2; i < block_size; ++i) {
        COMPLEX c = calc_multi(input[i], calc_mW(block_size, i));
        output[i].rn += c.rn;
        output[i].in += c.in;
    }
    return output;
}

COMPLEX *gen_block(int n, int block_size, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * block_size);
    for (int i = 0; i < block_size; ++i) {
        output[i] = input[block_size * n + i];
    }
    return output;
}

void copy_part(int n, int block_size, COMPLEX *input, COMPLEX *aim) {
    for (int i = 0; i < block_size; ++i) {
        aim[block_size * n + i] = input[i];
    }
}

COMPLEX *FFT(int n, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * n);
    int log_2 = calc_log(n);

    // exchange order
    for (int i = 0; i < n; ++i) {
        output[i] = input[calc_rbit(log_2, i)];
    }

    //
    for (int i = 0; i < log_2; ++i) {
        int block_num = calc_pow2(log_2 - 1 - i);
        int block_size = calc_pow2(i + 1);
        for (int j = 0; j < block_num; ++j) {
            COMPLEX *temp_block = gen_block(j, block_size, output);
            COMPLEX *temp_result = block_FFT(block_size, temp_block);
            copy_part(j, block_size, temp_result, output);

            free(temp_block);
            free(temp_result);
        }
    }
    return output;
}

COMPLEX *iFFT(int n, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * n);
    int log_2 = calc_log(n);

    // exchange order
    for (int i = 0; i < n; ++i) {
        output[i] = input[calc_rbit(log_2, i)];
    }

    //
    for (int i = 0; i < log_2; ++i) {
        int block_num = calc_pow2(log_2 - 1 - i);
        int block_size = calc_pow2(i + 1);
        for (int j = 0; j < block_num; ++j) {
            COMPLEX *temp_block = gen_block(j, block_size, output);
            COMPLEX *temp_result = block_iFFT(block_size, temp_block);
            copy_part(j, block_size, temp_result, output);

            free(temp_block);
            free(temp_result);
        }
    }

    for (int i = 0; i < n; ++i) {
        output[i].rn /= n;
        output[i].in /= n;
    }
    return output;
}

COMPLEX *FFT_2(int height, int width, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);

    for (int i = 0; i < width; ++i) {
        COMPLEX *v_input = c_get_array_v(height, width, input, i);
        COMPLEX *DFTed = FFT(height, v_input);
        c_copy_vertical(height, width, DFTed, output, i);
        free(v_input);
        free(DFTed);
    }

    for (int i = 0; i < height; ++i) {
        COMPLEX *h_input = c_get_array_h(width, output, i);
        COMPLEX *DFTed = FFT(width, h_input);
        c_copy_horizontal(width, DFTed, output, i);
        free(h_input);
        free(DFTed);
    }
    return output;
}

COMPLEX *iFFT_2(int height, int width, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);

    for (int i = 0; i < width; ++i) {
        COMPLEX *v_input = c_get_array_v(height, width, input, i);
        COMPLEX *iDFTed = iFFT(height, v_input);
        c_copy_vertical(height, width, iDFTed, output, i);
        free(v_input);
        free(iDFTed);
    }

    for (int i = 0; i < height; ++i) {
        COMPLEX *h_input = c_get_array_h(width, output, i);
        COMPLEX *iDFTed = iFFT(width, h_input);
        c_copy_horizontal(width, iDFTed, output, i);
        free(h_input);
        free(iDFTed);
    } 
    return output;
}
