#include "SPutil.h"

void d_graph(int n, double *input, int max_value, int graph_size) {
    for (int i = 0; i < n; ++i) {
        printf("  (%3d) == %10.3f ", i, input[i]);
        int convert = input[i] / max_value * graph_size;
        int bool = 0;
        for (int j = -1 * graph_size; j < graph_size; ++j) {
            if (bool) {
                if (j == convert) {
                    printf("*");
                    bool = 0;
                }
                else if (j == 0) {
                    printf("|");
                    bool = 0;
                }
                else {
                    printf("*");
                }
                continue;
            }

            if (j == convert) {
                printf("*");
                switch (bool) {
                    case 1:
                        bool = 0;
                        break;
                    case 0:
                        bool = 1;
                        break;
                }
                if (j == 0 && convert == 0) bool = 0;
            }
            else if (j == 0) {
                printf("|");
                switch (bool) {
                    case 1:
                        bool = 0;
                        break;
                    case 0:
                        bool = 1;
                        break;
                }
            }
            else if (!bool) {
                printf(" ");
            }
        }
        puts("");
    }
}

void c_graph(int n, COMPLEX *input, int max_value, int graph_size) {
    double *to_graph = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        to_graph[i] = input[i].rn;
    }

    for (int i = 0; i < n; ++i) {
        printf("  (%3d) == %10.3f ", i, to_graph[i]);
        int convert = to_graph[i] / max_value * graph_size;
        int bool = 0;
        for (int j = -1 * graph_size; j < graph_size; ++j) {
            if (bool) {
                if (j == convert) {
                    printf("*");
                    bool = 0;
                }
                else if (j == 0) {
                    printf("|");
                    bool = 0;
                }
                else {
                    printf("*");
                }
                continue;
            }

            if (j == convert) {
                printf("*");
                switch (bool) {
                    case 1:
                        bool = 0;
                        break;
                    case 0:
                        bool = 1;
                        break;
                }
                if (j == 0 && convert == 0) bool = 0;
            }
            else if (j == 0) {
                printf("|");
                switch (bool) {
                    case 1:
                        bool = 0;
                        break;
                    case 0:
                        bool = 1;
                        break;
                }
            }
            else if (!bool) {
                printf(" ");
            }
        }
        puts("");
    }
    free(to_graph);
}

void c_print(int n, COMPLEX *input) {
    for (int i = 0; i < n; ++i) {
        printf("  (%3d) == %10.3f + j(%10.3f)\n", i, input[i].rn, input[i].in);
    }
}

double *d_file_reader(int *line_no, char *file_name) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        puts("ERROR : d_file_reader - fopen");
        return 0;
    }

    *line_no = 0;
    double *input = (double *)malloc(sizeof(double) * MAX_DATA_SIZE);
    while (fscanf(fp, "%lf", &input[*line_no]) == 1)
        ++*line_no;

    fclose(fp);
    return input;
}

COMPLEX *c_file_reader(int *line_no, char *file_name) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        puts("ERROR : c_file_reader - fopen");
        return 0;
    }

    *line_no = 0;
    COMPLEX *input = (COMPLEX *)malloc(sizeof(COMPLEX) * MAX_DATA_SIZE);
    while (fscanf(fp, "%lf %lf", &input[*line_no].rn, &input[*line_no].in) == 2)
        ++*line_no;

    fclose(fp);
    return input;
}

COMPLEX *cd_file_reader(int *line_no, char *file_name) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        puts("ERROR : cd_file_reader - fopen");
        return 0;
    }

    *line_no = 0;
    COMPLEX *input = (COMPLEX *)malloc(sizeof(COMPLEX) * MAX_DATA_SIZE);
    while (fscanf(fp, "%lf", &input[*line_no].rn) == 1) {
        input[*line_no].in = 0;
        ++*line_no;
    }

    fclose(fp);
    return input;
}

double *DCT(int n, double *input) {
    double *output = malloc(sizeof(double) * n);
    for (int k = 0; k < n; ++k) {
        output[k] = 0;
        for (int i = 0; i < n; ++i) {
            output[k] += input[i] * cos((2 * i + 1) * k * M_PI / (2 * n));
        }
    }
    return output;
}

double *iDCT(int n, double *input) {
    double *output = malloc(sizeof(double) * n);
    for (int k = 0; k < n; ++k) {
        output[k] = input[0] / 2;
        for (int i = 1; i < n; ++i) {
            output[k] += input[i] * cos((2 * k + 1) * i * M_PI / (2 * n));
        }
        output[k] = output[k] * 2 / n;
    }
    return output;
}

double *DCT_lowpass(int n, double *input, int value) {
    double *output = malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        if (i < value)
            output[i] = input[i];
        else
            output[i] = 0;
    }
    return output;
}

double *DCT_highpass(int n, double *input, int value) {
    double *output = malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        if (value < i)
            output[i] = input[i];
        else
            output[i] = 0;
    }
    return output;
}

COMPLEX *DFT(int N, COMPLEX *input) {
    COMPLEX *output = malloc(sizeof(COMPLEX) * N);
    for (int k = 0; k < N; ++k) {
        output[k].rn = 0.0;
        output[k].in = 0.0;

        for (int n = 0; n < N; ++n) {
            COMPLEX e;
            e.rn = cos(2 * M_PI * k * n / N);
            e.in = -sin(2 * M_PI * k * n / N);

            output[k].rn += input[n].rn * e.rn - input[n].in * e.in;
            output[k].in += input[n].rn * e.in + input[n].in * e.rn;
        }
    }
    return output;
}

COMPLEX *iDFT(int N, COMPLEX *input) {
    COMPLEX *output = malloc(sizeof(COMPLEX) * N);
    for (int n = 0; n < N; ++n) {
        output[n].rn = 0.0;
        output[n].in = 0.0;

        for (int k = 0; k < N; ++k) {
            COMPLEX e;
            e.rn = cos(2 * M_PI * k * n / N);
            e.in = sin(2 * M_PI * k * n / N);

            output[n].rn += input[k].rn * e.rn - input[k].in * e.in;
            output[n].in += input[k].rn * e.in + input[k].in * e.rn;
        }
        output[n].rn /= N;
        output[n].in /= N;
    }
    return output;
}

COMPLEX *DFT_lowpass(int n, COMPLEX *input, int value) {
    COMPLEX *output = malloc(sizeof(COMPLEX) * n);
    for (int i = 0; i < n; ++i) {
        if (i < value || n - value < i) {
            output[i] = input[i];
        }
        else {
            output[i].rn = 0;
            output[i].in = 0;
        }
    }
    return output;
}

COMPLEX *DFT_highpass(int n, COMPLEX *input, int value) {
    COMPLEX *output = malloc(sizeof(COMPLEX) * n);
    for (int i = 0; i < n; ++i) {
        if (value < i && i < n - value) {
            output[i] = input[i];
        }
        else {
            output[i].rn = 0;
            output[i].in = 0;
        }
    }
    return output;
}

double *DFT_power(int n, COMPLEX *input) {
    double *output = malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        output[i] = pow(input[i].rn, 2) + pow(input[i].in, 2);
    }
    return output;
}

int get_label(int x, int y, int width) { return x * width + y; }

double *d_cin_2(int height, int width) {
    double *input = (double *)malloc(sizeof(double) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            scanf("%lf", &input[get_label(i, j, width)]);
        }
    }
    return input;
}

void d_print_2(int height, int width, double *input, int mode) {
    puts("\nprint");
    if (mode == 0) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                printf("%7.2f  ", input[get_label(i, j, width)]);
            }
            puts("");
        }
    }
    if (mode == 1) {
        printf("###");
        for (int i = 0; i < width; ++i) {
            printf("%9d", i);
        }
        puts("");
        for (int i = 0; i < height; ++i) {
            printf("%3d", i);
            for (int j = 0; j < width; ++j) {
                printf("  %7.2f", input[get_label(i, j, width)]);
            }
            puts("");
        }
    }
}

double *d_get_array_v(int height, int width, double *input, int n) {
    double *output = (double *)malloc(sizeof(double) * height);
    for (int i = 0; i < height; ++i) {
        output[i] = input[get_label(i, n, width)];
    }
    return output;
}

double *d_get_array_h(int width, double *input, int n) {
    double *output = (double *)malloc(sizeof(double) * width);
    for (int i = 0; i < width; ++i) {
        output[i] = input[get_label(n, i, width)];
    }
    return output;
}

void d_copy_vertical(int height, int width, double *input, double *aim, int n) {
    for (int i = 0; i < height; ++i) {
        aim[get_label(i, n, width)] = input[i];
    }
}

void d_copy_horizontal(int width, double *input, double *aim, int n) {
    for (int i = 0; i < width; ++i) {
        aim[get_label(n, i, width)] = input[i];
    }
}

double *DCT_2(int height, int width, double *input) {
    double *output = (double *)malloc(sizeof(double) * height * width);

    for (int i = 0; i < width; ++i) {
        double *v_input = d_get_array_v(height, width, input, i);
        double *DCTed = DCT(height, v_input);
        d_copy_vertical(height, width, DCTed, output, i);
        free(v_input);
        free(DCTed);
    }

    for (int i = 0; i < height; ++i) {
        double *h_input = d_get_array_h(width, output, i);
        double *DCTed = DCT(width, h_input);
        d_copy_horizontal(width, DCTed, output, i);
        free(h_input);
        free(DCTed);
    }
    return output;
}

double *iDCT_2(int height, int width, double *input) {
    double *output = (double *)malloc(sizeof(double) * height * width);

    for (int i = 0; i < width; ++i) {
        double *v_input = d_get_array_v(height, width, input, i);
        double *iDCTed = iDCT(height, v_input);
        d_copy_vertical(height, width, iDCTed, output, i);
        free(v_input);
        free(iDCTed);
    }

    for (int i = 0; i < height; ++i) {
        double *h_input = d_get_array_h(width, output, i);
        double *iDCTed = iDCT(width, h_input);
        d_copy_horizontal(width, iDCTed, output, i);
        free(h_input);
        free(iDCTed);
    }
    return output;
}
