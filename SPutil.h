#ifndef SPutil_H_
#define SPutil_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 10000

typedef struct complex {
    double rn;
    double in;
} COMPLEX;


// 2D座標用
int get_label(int x, int y, int width);



// 標準出力系 ************************************************************

// doubleのグラフ
void d_graph(int n, double *input, int max_value, int graph_size);
// COMPLEXのグラフ
void c_graph(int n, COMPLEX *input, int max_value, int graph_size);

// doubleの表示 mode == 1 : format
void d_print(int n, double *input, int mode);
// COMPLEXの表示 mode == 1 : format
void c_print(int n, COMPLEX *input, int mode);

// 2D doubleの表  mode == 1 : format
void d_print_2(int height, int width, double *input, int mode);
// 2D COMPLEXの表  mode == 1 : format
void c_print_2(int height, int width, COMPLEX *input, int mode);
// *******************************************************************



// 標準入力系 ********************************************************

// doubleを標準入力
double *d_cin(int line_no);
// COMPLEXを標準入力
COMPLEX *c_cin(int line_no);
// COMPLEXを標準入力 虚数は補完
COMPLEX *c_cin_aut(int line_no);

// 2D doubleを標準入力
double *d_cin_2(int height, int width);
// 2D COMPLEXを標準入力
COMPLEX *c_cin_2(int height, int width);
// 2D COMPLEXを標準入力 虚数は補完
COMPLEX *c_cin_2_aut(int height, int width);
// *******************************************************************



// ファイル系 ********************************************************

// doubleをファイルからread
double *d_file_reader(int *line_no, char *file_name);
// COMPLEXをファイルからread
COMPLEX *c_file_reader(int *line_no, char *file_name);
// COMPLEXをファイルからread 虚数は補完
COMPLEX *cd_file_reader(int *line_no, char *file_name);


// 2D doubleをファイルからread
double *d_file_reader_2(int height, int width, char *file_name);
// 2D COMPLEXをファイルからread
COMPLEX *c_file_reader_2(int height, int width, char *file_name);
// 2D COMPLEXをファイルからread 虚数は補完
COMPLEX *cd_file_reader_2(int height, int width, char *file_name);


// csv
double *d_csv_reader(int *line_no, char *file_name);
int d_csv_writer(int line_no, double *input, char *file_name);
// 虚数部分を補う
COMPLEX *c_csv_reader(int *line_no, char *file_name);
int c_csv_writer(int line_no, COMPLEX *input, char *file_name);
// ******************************************************************



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



// ********** 未使用
double *d_get_array_v(int height, int width, double *input, int n);
double *d_get_array_h(int width, double *input, int n);
void d_copy_vertical(int height, int width, double *input, double *aim, int n);
void d_copy_horizontal(int width, double *input, double *aim, int n);
// *****************
double *DCT_2(int height, int width, double *input);
double *iDCT_2(int height, int width, double *input);



// ********** 未使用
COMPLEX *c_get_array_v(int height, int width, COMPLEX *input, int n);
COMPLEX *c_get_array_h(int width, COMPLEX *input, int n);
void c_copy_vertical(int height, int width, COMPLEX *input, COMPLEX *aim, int n);
void c_copy_horizontal(int width, COMPLEX *input, COMPLEX *aim, int n);
// *****************
COMPLEX *DFT_2(int height, int width, COMPLEX *input);
COMPLEX *iDFT_2(int height, int width, COMPLEX *input);



#endif /* SPutil_H_ */
