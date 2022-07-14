#ifndef SPutil_H_
#define SPutil_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 1000

typedef struct complex {
    double rn;
    double in;
} COMPLEX;


void d_graph(int n, double *input, int max_value, int graph_size);
void c_graph(int n, COMPLEX *input, int max_value, int graph_size);
void c_print(int n, COMPLEX *input);


double *d_file_reader(int *line_no, char *file_name);
COMPLEX *c_file_reader(int *line_no, char *file_name);
// 虚数部分を補う
COMPLEX *cd_file_reader(int *line_no, char *file_name);


double *DCT(int n, double *input);
double *iDCT(int n, double *input);
// valueの値は含めない
double *DCT_lowpass(int n, double *input, int value);
// valueの値は含めない
double *DCT_highpass(int n, double *input, int value);


COMPLEX *DFT(int N, COMPLEX *input);
COMPLEX *iDFT(int N, COMPLEX *input);
// valueの値は含めない
COMPLEX *DFT_lowpass(int n, COMPLEX *input, int value);
// valueの値は含めない
COMPLEX *DFT_highpass(int n, COMPLEX *input, int value);
double *DFT_power(int n, COMPLEX *input);


int get_label(int x, int y, int width);
// mode == 1 : format
double *d_cin_2(int height, int width);
void d_print_2(int height, int width, double *input, int mode);


double *d_get_array_v(int height, int width, double *input, int n);
double *d_get_array_h(int width, double *input, int n);
void d_copy_vertical(int height, int width, double *input, double *aim, int n);
void d_copy_horizontal(int width, double *input, double *aim, int n);
double *DCT_2(int heght, int width, double *input);
double *iDCT_2(int heght, int width, double *input);





#endif /* SPutil_H_ */
