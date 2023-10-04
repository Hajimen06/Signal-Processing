#include "SPutil.h"

void d_graph(int n, double *input, int max_value, int graph_size) {
    for (int i = 0; i < n; ++i) {
        printf("  (%4d) == %10.3f ", i, input[i]);
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
        printf("  (%4d) == %10.3f ", i, to_graph[i]);
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

void d_print(int n, double *input, int mode) {
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            printf("%f\n", input[i]);
        }
    }
    else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            printf("  (%3d) == %10.3f\n", i, input[i]);
        }
    }
}

void c_print(int n, COMPLEX *input, int mode) {
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            printf("%f %f\n", input[i].rn, input[i].in);
        }
    }
    else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            printf("  (%3d) == %10.3f + j(%10.3f)\n", i, input[i].rn,
                   input[i].in);
        }
    }
}

double *d_cin(int line_no) {
    double *output = (double *)malloc(sizeof(double) * line_no);
    for (int i = 0; i < line_no; ++i) {
        scanf("%lf", &output[i]);
    }
    return output;
}

COMPLEX *c_cin(int line_no) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * line_no);
    for (int i = 0; i < line_no; ++i) {
        scanf("%lf", &output[i].rn);
        scanf("%lf", &output[i].in);
    }
    return output;
}

COMPLEX *c_cin_aut(int line_no) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * line_no);
    for (int i = 0; i < line_no; ++i) {
        scanf("%lf", &output[i].rn);
        output[i].in = 0;
    }
    return output;
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

double *d_file_reader_2(int height, int width, char *file_name) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        puts("ERROR : d_file_reader_2 - fopen");
        return NULL;
    }

    double *output = (double *)malloc(sizeof(double) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fscanf(fp, "%lf", &output[get_label(i, j, width)]);
        }
    }
    fclose(fp);
    return output;
}

COMPLEX *c_file_reader_2(int height, int width, char *file_name) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        puts("ERROR : c_file_reader_2 - fopen");
        return NULL;
    }

    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fscanf(fp, "%lf", &output[get_label(i, j, width)].rn);
            fscanf(fp, "%lf", &output[get_label(i, j, width)].in);
        }
    }
    fclose(fp);
    return output;
}

COMPLEX *cd_file_reader_2(int height, int width, char *file_name) {
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        puts("ERROR : cd_file_reader_2 - fopen");
        return NULL;
    }

    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fscanf(fp, "%lf", &output[get_label(i, j, width)].rn);
            output[get_label(i, j, width)].in = 0;
        }
    }
    fclose(fp);
    return output;
}

double *d_csv_reader(int *line_no, char *file_name) {
    FILE *in_file;
    if ((in_file = fopen(file_name, "r")) == NULL) {
        puts("ERROR : d_csv_reader - fopen");
        return NULL;
    }

    fscanf(in_file, "%d", line_no);
    printf("line_no == %d\n", *line_no);
    double *output = (double *)malloc(sizeof(double) * (*line_no));

    int l;
    for (int i = 0; i < *line_no; ++i) {
        fscanf(in_file, "%d,%lf", &l, &output[i]);
    }

    fclose(in_file);
    return output;
}

int d_csv_writer(int line_no, double *input, char *file_name) {
    FILE *out_file;
    if ((out_file = fopen(file_name, "w")) == NULL) {
        puts("ERROR : d_csv_writer - fopen");
        return 0;
    }

    fprintf(out_file, "%d\n", line_no);

    for (int i = 0; i < line_no; ++i) {
        fprintf(out_file, "%d,%le\n", i, input[i]);
    }

    fclose(out_file);
    return 1;
}

COMPLEX *c_csv_reader(int *line_no, char *file_name) {
    FILE *in_file;
    if ((in_file = fopen(file_name, "r")) == NULL) {
        puts("ERROR : c_csv_reader - fopen");
        return NULL;
    }

    fscanf(in_file, "%d", line_no);
    printf("line_no == %d\n", *line_no);
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * (*line_no));

    int l;
    for (int i = 0; i < *line_no; ++i) {
        fscanf(in_file, "%d,%lf", &l, &output[i].rn);
        output[i].in = 0;
    }

    fclose(in_file);
    return output;
}

int c_csv_writer(int line_no, COMPLEX *input, char *file_name) {
    FILE *out_file;
    if ((out_file = fopen(file_name, "w")) == NULL) {
        puts("ERROR : c_csv_writer - fopen");
        return 0;
    }

    fprintf(out_file, "%d\n", line_no);

    for (int i = 0; i < line_no; ++i) {
        fprintf(out_file, "%d,%le\n", i, input[i].rn);
    }

    fclose(out_file);
    return 1;
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

COMPLEX *c_cin_2(int height, int width) {
    COMPLEX *input = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            scanf("%lf", &input[get_label(i, j, width)].rn);
            scanf("%lf", &input[get_label(i, j, width)].in);
        }
    }
    return input;
}

COMPLEX *c_cin_2_aut(int height, int width) {
    COMPLEX *input = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            scanf("%lf", &input[get_label(i, j, width)].rn);
            input[get_label(i, j, width)].in = 0;
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
    else if (mode == 1) {
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
    else if (mode == 2) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                printf("%.3f  ", input[get_label(i, j, width)]);
            }
            puts("");
        }
    }
}

void c_print_2(int height, int width, COMPLEX *input, int mode) {
    puts("\nprint");
    if (mode == 0) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                printf("%9.2f", input[get_label(i, j, width)].rn);
                printf(" %9.2f   ", input[get_label(i, j, width)].in);
            }
            puts("");
        }
    }
    else if (mode == 1) {
        printf("###");
        for (int i = 0; i < width; ++i) {
            printf("%22d", i);
        }
        puts("");
        for (int i = 0; i < height; ++i) {
            printf("%3d", i);
            for (int j = 0; j < width; ++j) {
                printf("%8.2f", input[get_label(i, j, width)].rn);
                printf(" + j(%8.2f)", input[get_label(i, j, width)].in);
            }
            puts("");
        }
    }
    else if (mode == 2) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                printf("%.3f", input[get_label(i, j, width)].rn);
                printf(" %.3f    ", input[get_label(i, j, width)].in);
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

COMPLEX *c_get_array_v(int height, int width, COMPLEX *input, int n) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height);
    for (int i = 0; i < height; ++i) {
        output[i] = input[get_label(i, n, width)];
    }
    return output;
}

COMPLEX *c_get_array_h(int width, COMPLEX *input, int n) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * width);
    for (int i = 0; i < width; ++i) {
        output[i] = input[get_label(n, i, width)];
    }
    return output;
}

void c_copy_vertical(int height, int width, COMPLEX *input, COMPLEX *aim,
                     int n) {
    for (int i = 0; i < height; ++i) {
        aim[get_label(i, n, width)] = input[i];
    }
}

void c_copy_horizontal(int width, COMPLEX *input, COMPLEX *aim, int n) {
    for (int i = 0; i < width; ++i) {
        aim[get_label(n, i, width)] = input[i];
    }
}

COMPLEX *DFT_2(int height, int width, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);

    for (int i = 0; i < width; ++i) {
        COMPLEX *v_input = c_get_array_v(height, width, input, i);
        COMPLEX *DFTed = DFT(height, v_input);
        c_copy_vertical(height, width, DFTed, output, i);
        free(v_input);
        free(DFTed);
    }

    for (int i = 0; i < height; ++i) {
        COMPLEX *h_input = c_get_array_h(width, output, i);
        COMPLEX *DFTed = DFT(width, h_input);
        c_copy_horizontal(width, DFTed, output, i);
        free(h_input);
        free(DFTed);
    }
    return output;
}

COMPLEX *iDFT_2(int height, int width, COMPLEX *input) {
    COMPLEX *output = (COMPLEX *)malloc(sizeof(COMPLEX) * height * width);

    for (int i = 0; i < width; ++i) {
        COMPLEX *v_input = c_get_array_v(height, width, input, i);
        COMPLEX *iDFTed = iDFT(height, v_input);
        c_copy_vertical(height, width, iDFTed, output, i);
        free(v_input);
        free(iDFTed);
    }

    for (int i = 0; i < height; ++i) {
        COMPLEX *h_input = c_get_array_h(width, output, i);
        COMPLEX *iDFTed = iDFT(width, h_input);
        c_copy_horizontal(width, iDFTed, output, i);
        free(h_input);
        free(iDFTed);
    }
    return output;
}
