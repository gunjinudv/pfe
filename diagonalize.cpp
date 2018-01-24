//#include "StdAfx.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "nrutil.h"
#include "svdcmp.h"
#include "svbksb.h"
#include "matrix.h"



inline void ProduitVectoriel(double *v1, double *v2, int n, double *res); 
inline double ProduitScalar(double *v1, double *v2); 



int Diagonalize(double **mcov, int n, double **mtr, double *vp)
{
  int i, j; int testsvd;
  //  double **M = alocamd(3, 3); 
  //  double **v = alocamd(3, 3); 
  //  double w[3]; 
  double *w = dvector(1, 6);
  double **v = dmatrix(1, 6, 1, 6);
  double **M = dmatrix(1, 6, 1, 6);
 
  for(i=0;i<n;i++)	
    for(j=0;j<n;j++)
      M[i+1][j+1] = mcov[i][j];
  
  //fprintf(stderr, "AVANT SVD\n"); 
  testsvd = svdcmpd(M, n, n, w, v); 
  //fprintf(stderr, "APRES SVD\n"); 
  if(testsvd == 0)
    return 0; 
  
  for(i=0;i<n;i++)	
    for(j=0;j<n;j++)
      {
	mtr[i][j] = M[i+1][j+1];
      }
  for(i=0;i<n;i++) 
    vp[i] = w[i+1];

  /* for(i=0;i<n;i++)  
    fprintf(stderr, "%g ", w[i+1]); 
  
  //testing result
  
 double **mtest = alocamd(3, 3); 
  double **mtest1 = alocamd(3, 3);
  double **mtrt = alocamd(3, 3);
   
  for(i=0;i<n;i++)	
    for(j=0;j<n;j++)
      mtrt[i][j] = mtr[j][i]; // transpose
  //      mtrt[i][j] = mtr[i][j];

   // CORECTION 6 Systeme Droit 
  double v1[3], v2[3], v3[3]; double semn;
  ProduitVectoriel(mtrt[0], mtrt[1], 3, v1); 
  semn = ProduitScalar(v1, mtrt[2]); 
  if(semn < 0.0)
    for(i=0;i<n;i++)
      {mtrt[2][i] = -mtrt[2][i]; mtr[i][2] = -mtr[i][2];}

  
  // Fin CORECTION 6 Systeme Droit 


  mult_mat(mtrt, mcov, mtest, n, n, n, n);
  mult_mat(mtest, mtr, mtest1, n, n, n, n); 

  fprintf(stderr, "\nMatrice Transformation:\n"); 
  for(i=0;i<n;i++)  
    {
    for(j=0;j<n;j++)
      {
	fprintf(stderr, "%g ", mtrt[i][j]);	
      }
    fprintf(stderr, "\n");
    }
  fprintf(stderr, "\n");
  
  fprintf(stderr, "result DIAGONALIZE:\n");
  fprintf(stderr, "w: "); 
  for(i=0;i<n;i++)  
    fprintf(stderr, "%g ", w[i+1]);
  fprintf(stderr, "\nL:\n"); 
  for(i=0;i<n;i++)  
    {
    for(j=0;j<n;j++)
      {
	fprintf(stderr, "%g ", mtest1[i][j]);	
      }
    fprintf(stderr, "\n");
    }
  fprintf(stderr, "\n");
  
  dalocd(mtest1, 3);
  dalocd(mtest, 3);
  //  END testing result
*/ 

free_dmatrix(M,1,6,1,6);
  free_dmatrix(v,1,6,1,6);
  free_dvector(w,1,6);
  //  dalocd(v, 3);
  //  dalocd(M, 3);
  return 1; 
  
}


inline void ProduitVectoriel(double *v1, double *v2, int n, double *res)
{
  res[0] = v1[1]*v2[2] - v1[2]*v2[1];
  res[1] = v1[2]*v2[0] - v1[0]*v2[2];
  res[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

inline double ProduitScalar(double *v1, double *v2)
{
  return (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}


int compute_main_axes2D(double **mp, int N, double** &mtr, double* &vp)
{
  int i,j;
  

  if(mtr==NULL)
    mtr = alocamd(2, 2); 
  if(vp == NULL)
    vp = (double*) calloc(2,sizeof(double));

  //calcul matrice de covariance
  
  double **mpt = alocamd(N,2);
  double ** mcov = alocamd(2, 2); 

  for(i=0;i<N;i++)
    {
      mpt[i][0] = mp[0][i] ;
      mpt[i][1] = mp[1][i] ;
    }

  mult_mat(mp, mpt, mcov, 2, N, N, 2);
  
  for(i=0;i<2;i++)
	  for(j=0;j<2;j++)
		  mcov[i][j] /= (double)N;

/*	char Mess[10000];
	sprintf(Mess,"%g\t%g\n%g\t%g",mcov[0][0],mcov[0][1],mcov[1][0],mcov[1][1]);
	AfxMessageBox(Mess);*/
  
  Diagonalize(mcov, 2,  mtr, vp);
  
  /*sprintf(Mess,"%g\t%g\n%g\t%g\nVal propres:\n%g\t%g",mtr[0][0],mtr[0][1],mtr[1][0],mtr[1][1],vp[0],vp[1]);
	AfxMessageBox(Mess);*/
  
  dalocd(mcov, 2); 
  
  dalocd(mpt,N);

  return 0; 
}


int compute_main_axes3D(double **mp, int N, double** &mtr, double* &vp)
{
  int i,j;
  

  if(mtr==NULL)
    mtr = alocamd(3, 3); 
  if(vp == NULL)
    vp = (double*) calloc(3,sizeof(double));

  //calcul matrice de covariance
  
  double **mpt = alocamd(N,3);
  double ** mcov = alocamd(3, 3); 

  for(i=0;i<N;i++)
    {
      mpt[i][0] = mp[0][i] ;
      mpt[i][1] = mp[1][i] ;
      mpt[i][2] = mp[2][i] ;
    }

  mult_mat(mp, mpt, mcov, 3, N, N, 3);
  
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      mcov[i][j] /= (double)N;

/*	char Mess[10000];
	sprintf(Mess,"%g\t%g\n%g\t%g",mcov[0][0],mcov[0][1],mcov[1][0],mcov[1][1]);
	AfxMessageBox(Mess);*/
  
  Diagonalize(mcov, 3,  mtr, vp);
  
  /*sprintf(Mess,"%g\t%g\n%g\t%g\nVal propres:\n%g\t%g",mtr[0][0],mtr[0][1],mtr[1][0],mtr[1][1],vp[0],vp[1]);
	AfxMessageBox(Mess);*/
  
  dalocd(mcov, 3); 
  
  dalocd(mpt,N);

  return 0; 
}


