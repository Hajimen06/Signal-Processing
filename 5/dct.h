#ifndef DCT_H_
#define DCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int dct(double *x,int n)
{
	int i,j,k;
	double s,nrm,*ct,*tmp;

	if( (ct=(double *)calloc(n<<2,sizeof(double))) == NULL )
		return 0;

	if( (tmp=(double *)calloc(n,sizeof(double))) == NULL ){
		free(ct);
		return 0;
	}

	for(i=0;i<n;++i)
		tmp[i] = x[i];
	for(i=0;i<(n<<2);++i)
		ct[i] = cos( M_PI * (double)i/(double)(n<<1) );

	nrm = sqrt( 2.0 / (double)n );
	for(j=0;j<n;++j){
		s = 0.0;
		for(i=0;i<n;++i){
			k = ( (i<<1) + 1 ) * j;
			k %= n<<2;
			s += tmp[i] * ct[k];
		}
		if( j == 0 )
			s /= sqrt(2.0);
			x[j] = nrm * s;
	}

	free(tmp);
	free(ct);
	return 1;
}


int idct(double *x,int n)
{
	int i,j,k;
	double s,nrm,*ct,*tmp,data;

	if( (ct=(double *)calloc(n<<2,sizeof(double))) == NULL )
		return 0;

	if( (tmp=(double *)calloc(n,sizeof(double))) == NULL ){
		free(ct);
		return 0;
	}

	for(i=0;i<n;++i)
		tmp[i] = x[i];
	for(i=0;i<(n<<2);++i)
		ct[i] = cos( M_PI * (double)i/(double)(n<<1) );

	nrm = sqrt( 2.0 / (double)n );
	for(j=0;j<n;++j){
		s = 0.0;
		for(i=0;i<n;++i){
			k = ( (j<<1) + 1 ) * i;
			k %= n<<2;
			data = tmp[i] * ct[k];
			if( i == 0 )
				data /= sqrt(2.0);

			s += data;
		}
			x[j] = nrm * s;
	}

	free(tmp);
	free(ct);
	return 1;
}
#endif
