#ifndef CSVUTIL_H_
#define CSVUTIL_H_


#include <stdlib.h>
#include <stdio.h>

int csv_reader(double **input, char *file_name);
int csv_writer(int line_no, double *input, char *file_name);


#endif
