#ifndef FFT_H_
#define FFT_H_


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "SPutil.h"


int calc_log(int n);
int calc_pow2(int n);
COMPLEX calc_multi(COMPLEX c1, COMPLEX c2);
int calc_rbit(int digit, int n);
COMPLEX calc_W(int n, int k);
COMPLEX calc_mW(int n, int k);
COMPLEX *block_FFT(int block_size, COMPLEX *input);
COMPLEX *block_iFFT(int block_size, COMPLEX *input);
COMPLEX *gen_block(int n, int block_size, COMPLEX *input);
void copy_part(int n, int block_size, COMPLEX *input, COMPLEX *aim);

COMPLEX *FFT(int n, COMPLEX *input);
COMPLEX *iFFT(int n, COMPLEX *input);

COMPLEX *FFT_2(int height, int width, COMPLEX *input);
COMPLEX *iFFT_2(int height, int width, COMPLEX *input);


#endif
