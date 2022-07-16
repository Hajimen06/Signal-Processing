#include "CSVutil.h"

int csv_reader(double **input, char *file_name) {
    double *p = *input;
    FILE *in_file;
    if ( (in_file = fopen(file_name, "r")) == NULL ) {
        puts("ERROR : csv_reader - fopen");
        return 0;
    }

    int line_no;
    fscanf(in_file, "%d", &line_no);
    printf("line_no == %d\n", line_no);
    p = (double *)malloc(sizeof(double)*line_no);

    int l;
    for (int i = 0; i < line_no; ++i) {
        fscanf(in_file, "%d,%lf", &l, &p[i]);
        //printf("%f\n", p[i]);
    }
    *input = p;

    fclose(in_file);
    return line_no;
}

int csv_writer(int line_no, double *input, char *file_name) {
    FILE *out_file;
    if ( (out_file = fopen(file_name, "w")) == NULL ) {
        puts("ERROR : csv_writer - fopen");
        return 0;
    }

    fprintf(out_file, "%d\n", line_no);

    for (int i = 0; i < line_no; ++i) {
        fprintf(out_file, "%d,%le\n", i, input[i]);
    }

    fclose(out_file);
    return 1;
}
