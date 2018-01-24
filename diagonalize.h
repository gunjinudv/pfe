#ifndef __DIAGSVD
#define __DIAGSVD

/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include <math.h> */
/* #include "nrutil.h" */
/* #include "svdcmp.h" */
/* #include "svbksb.h" */
/* #include "matrix.h" */



int Diagonalize(double **mcov, int n, double **mtr, double *vp); 
int compute_main_axes2D(double **mp, int N, double** &mtr, double* &vp);
int compute_main_axes3D(double **mp, int N, double** &mtr, double* &vp);

#endif
