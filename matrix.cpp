//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
//#include <conio.h>
#include <stdlib.h>

#define MaxInt 15000;
#define MinInt -15000;



double ** alocamd(unsigned int dx,unsigned int dy);
double *alocavd(unsigned int n);
void dalocd(double ** m,unsigned int dx);
void freevd(double *v);

//operations aves matrices ...

void mult_mat(double **a,double **b,double **c,
unsigned int ma,unsigned int na,unsigned int mb,unsigned int nb)
// fonction realisant la multiplications de deux matrices de doubles
{

unsigned int i,j,k;

if(na!=mb)
  {
    fprintf(stderr,"\nMatrix dimensions must agree\n");exit(1);
  }

for(i=0;i<ma;i++)
  for(j=0;j<nb;j++)
	 {
	 c[i][j]=0;
	 for(k=0;k<na;k++)
		 c[i][j]=c[i][j]+a[i][k]*b[k][j];
	 }
}



void mult_mvd(double **a,double *b,double *c,
unsigned int ma,unsigned int na,unsigned int mb)
// fonction realisant la multitplications d'une
// matrice avec un vecteur (en double)

{
 unsigned int i,k;
 if(na!=mb)
  {
  fprintf(stderr,"\nMatrix dimensions must agree\n");exit(1);
  }
  for(i=0;i<ma;i++)
	 {
	 c[i]=0;
	 for(k=0;k<na;k++)
		 c[i]=c[i]+a[i][k]*b[k];
	 }
}



void add_mat(double **a,double **b,double **c,
unsigned int m,unsigned int n)
// fonction realisant l'adition  de deux matrices de doubles
{

unsigned int i,j;

for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 c[i][j]=a[i][j]+b[i][j];
}

void add_mat_ct(double **a,double ct,double **c,
unsigned int m,unsigned int n)
// fonction realisant l'adition  d'une  matrice de doubles
// avec une matrice ayant tous les elements egaux a const;
{

unsigned int i,j;

for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 c[i][j]=a[i][j]+ct;
}


void sub_mat(double **a,double **b,double **c,
unsigned int m,unsigned int n)
// fonction realisant la difference  de deux matrices de doubles
{

unsigned int i,j;

for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 c[i][j]=a[i][j]-b[i][j];
}


void sub_mat_i(int **a,int **b,int **c,
unsigned int m,unsigned int n)
// fonction realisant la difference  de deux matrices de doubles
{

unsigned int i,j;

for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 c[i][j]=a[i][j]-b[i][j];
}


void ch_sig_mat(double **a,double **b,
unsigned int m,unsigned int n)
// fonction realisant l'inversion de signe  d'une matrice de doubles
{

unsigned int i,j;

for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 b[i][j]=(-a[i][j]);
}


int min_mi(int **x,unsigned int M,unsigned int N)
// calcul de l'element minimal d'une matrice (entier)
{
unsigned int i,j;
int m=MaxInt;
for(i=0;i<M;i++)
  for(j=0;j<N;j++)
    if(x[i][j]<m) m=x[i][j];
return m;
}


int max_mi(int **x,unsigned int M,unsigned int N)
// calcul de l'element maximal d'une matrice (entier)
{
unsigned int i,j;
int m=MinInt;
for(i=0;i<M;i++)
  for(j=0;j<N;j++)
    if(x[i][j]>m) m=x[i][j];
return m;
}



void zero_vd(double *h,int n)
// initialisation du vecteur double h avec 0.0;
{
int i;
for(i=0;i<n;i++)
  h[i]=0.0;
}


void zero_vc(char *h,int n)
// initialisation du vecteur double h avec 0.0;
{
int i;
for(i=0;i<n;i++)
  h[i]=(char)0;
}

void zero_vi(int *h,int n)
// initialisation du vecteur int h avec 0;
{
int i;
for(i=0;i<n;i++)
  h[i]=0;
}


void zero_vuc(unsigned char *h,int n)
// initialisation du vecteur unsigned char  h avec 0;
{
int i;
for(i=0;i<n;i++)
  h[i]=(unsigned char)0;
}



//int max_mi(int **x,unsigned int M,unsigned int N)


void abs_mati(int **x, int **y, unsigned int m, unsigned int n)
{
int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
    y[i][j]=abs(100*(int)log((double)x[i][j]));
}

void transmd(double **a,unsigned int m,unsigned int n)
//calcul de la transpose de la matrice "a"
// au retour de la fonction la matrice "a"
// devient egale a sa transpose.
{
double buf;unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 {
	   fprintf(stderr,"\nmatrxi: transmd!!!"); exit(1);
	 buf=a[i][j];
	 a[i][j]=a[j][i];
	 a[j][i]=buf;
	 }
}


void transmc(char **a,unsigned int m,unsigned int n)
{
char buf;unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 {
	 buf=a[i][j];
	 a[i][j]=a[j][i];
	 a[j][i]=buf;
	 }
}

void transmi(int **a,unsigned int m,unsigned int n)
{
int buf;unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 {
	 buf=a[i][j];
	 a[i][j]=a[j][i];
	 a[j][i]=buf;
	 }
}

void transml(long **a,unsigned int m,unsigned int n)
{
long buf;unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 {
	 buf=a[i][j];
	 a[i][j]=a[j][i];
	 a[j][i]=buf;
	 }
}

void transmf(float **a,unsigned int m,unsigned int n)
{
float buf;unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 {
	 buf=a[i][j];
	 a[i][j]=a[j][i];
	 a[j][i]=buf;
	 }
}




void get_col(int **x,int *v, int M, int indx_col)
{
int i;
for(i=0;i<M;i++)
  v[i] = x[i][indx_col];
}

void put_col(int **x,int *v, int M, int indx_col)
{
int i;
for(i=0;i<M;i++)
  x[i][indx_col] =  v[i];
}



void egal_dc(double **a,char **b,unsigned int m,unsigned int n)
// fonction realisant l'operation: a:=b, avec conversion de
// char en double ;
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(double)b[i][j];

}

void egal_cd(char **a,double **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(char)b[i][j];

}

void egal_ucd(unsigned char **a,double **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(unsigned char)b[i][j];

}

void egal_id(int **a,double **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(int)b[i][j];

}


void egal_duc(double **a,unsigned char **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(double)b[i][j];

}


void egal_ic(int **a,char **b,unsigned int m,unsigned int n)
// fonction realisant l'operation: a:=b, avec conversion de
// char en double ;
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(int)b[i][j];

}

void egal_ci(char **a,int **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(char)b[i][j];

}

void egal_uci(unsigned char **a,int **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(unsigned char)b[i][j];

}

void egal_uci_tronc(unsigned char **a,int **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
    if(abs(b[i][j])<0) a[i][j]=(unsigned char)0;
    else if(abs(b[i][j])>255) a[i][j]=(unsigned char)255;
    else 
      a[i][j]=(unsigned char)abs(b[i][j]);
}

void egal_iuc(int **a,unsigned char **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=(int)b[i][j];

}

// egalite de deux matrices de meme type

void eg_dd(double **a,double **b,unsigned int m,unsigned int n)
// fonction realisant l'operation: a:=b, avec conversion de
// char en double ;
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=b[i][j];

}


void eg_dd_v(double *v,double *u,unsigned int n)
{
unsigned int i;
for(i=0;i<n;i++) v[i]=u[i];
}

void eg_cc(char **a,char **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=b[i][j];

}

void eg_ucuc(unsigned char **a,unsigned char **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=b[i][j];

}

void eg_ff(float **a,float **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=b[i][j];

}


void eg_ii(int **a,int **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=b[i][j];

}

void eg_ll(long **a,long **b,unsigned int m,unsigned int n)
{
unsigned int i,j;
for(i=0;i<m;i++)
  for(j=0;j<n;j++)
	 a[i][j]=b[i][j];

}

//allocations des matrices ...

double ** alocamd(unsigned int dx,unsigned int dy)

{
 double **b;unsigned int i;
 //fprintf(stderr,"dy=%u, dx=%u",dy,dx);
 b=(double **)malloc((size_t)(dx*sizeof(double *)));
 if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(double *)malloc((size_t)(dy*sizeof(double)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
return b;
}



char ** alocamc(unsigned int dx,unsigned int dy)

{
 char **b;unsigned int i;
 b=(char **)malloc((size_t)(dx*sizeof(char *)));
 if (b==NULL)
 {
 fprintf(stderr,"\n eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(char *)malloc((size_t)(dy*sizeof(char)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
return b;
}


unsigned char ** alocamuc(unsigned int dx,unsigned int dy)

{
 unsigned char **b;unsigned int i;
 //fprintf(stderr,"alocamuc: \ndy=%u, dx =%u",dy,dx);
 b=(unsigned char **)malloc((size_t)(dx*sizeof(unsigned char *)));
 if (b==NULL)
 {
 fprintf(stderr,"\n eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(unsigned char *)malloc((size_t)(dy*sizeof(unsigned char)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
return b;
}

int ** alocami(unsigned int dx,unsigned int dy)

{
 int **b;unsigned int i;
 b=(int **)malloc((size_t)(dx*sizeof(int *)));
 if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(int *)malloc((size_t)(dy*sizeof(int)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
return b;
}

long ** alocaml(unsigned int dx,unsigned int dy)

{
 long **b;unsigned int i;
 b=(long **)malloc((size_t)(dx*sizeof(char *)));
 if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(long *)malloc((size_t)(dy*sizeof(long)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
return b;
}

float ** alocamf(unsigned int dx,unsigned int dy)

{
 float **b;unsigned int i;
 b=(float **)malloc((size_t)(dx*sizeof(float *)));
 if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(float *)malloc((size_t)(dy*sizeof(float)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
return b;
}

//allocations des vecteurs ...
double *alocavd(unsigned int n)
{
double *b=(double *)malloc((size_t)(n*sizeof(double)));
if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
//fprintf(stderr,"\nhello, how are you\n");
return b; 
}

char *alocavc(unsigned int n)
{
char *b=(char *)malloc((size_t)(n*sizeof(char)));
if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
return b; 
}

int *alocavi(unsigned int n)
{
int *b=(int *)malloc((size_t)(n*sizeof(int)));
if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
return b; 
}

long *alocavl(unsigned int n)
{
long *b=(long *)malloc((size_t)(n*sizeof(long)));
if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
return b; 
}

float *alocavf(unsigned int n)
{
float *b=(float *)malloc((size_t)(n*sizeof(float)));
if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
return b; 
}

// des-allocation des matrices
void dalocd(double ** m,unsigned int dx)
{
 unsigned int i;
 for(i=0;i<dx;i++)
	 free((double *)m[i]);
 free((double **)m);
}

void dalocc(char ** m,unsigned int dx)
{
 unsigned int i;
 for(i=0;i<dx;i++)
	 free((char *)m[i]);
 free((char **)m);
}

void dalocuc(unsigned char ** m,unsigned int dx)
{
 unsigned int i;
 for(i=0;i<dx;i++)
	 free((unsigned char *)m[i]);
 free((unsigned char **)m);
}

void daloci(int ** m,unsigned int dx)
{
 unsigned int i;
 for(i=0;i<dx;i++)
	 free((int *)m[i]);
 free((int **)m);
}

void dalocl(long ** m,unsigned int dx)
{
 unsigned int i;
 for(i=0;i<dx;i++)
	 free((long *)m[i]);
 free((long **)m);
}

void dalocf(float ** m,unsigned int dx)
{
 unsigned int i;
 for(i=0;i<dx;i++)
	 free((float *)m[i]);
 free((float **)m);
}
// des-allocations des vecteurs

void freevd(double *v)
{
free((double *) v);
}

void freevc(char *v)
{
free((char *) v);
}

void freevi(int *v)
{
free((int *) v);
}

void freevl(long *v)
{
free((long *) v);
}

void freevf(float *v)
{
free((float *) v);
}


double **** alocam_md(unsigned int dx,unsigned int dy, unsigned int mdx,
		      unsigned int mdy)

{
 double ****b;unsigned int i,j;
 //fprintf(stderr,stderr, "dy=%u, dx=%u",dy,dx);
 b=(double ****)malloc((size_t)(dx*sizeof(double ***)));
 if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(double ***)malloc((size_t)(dy*sizeof(double **)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
 for(i=0;i<dx;i++)
   for(j=0;j<dy;j++)
     b[i][j]=alocamd(mdx,mdy);
return b;
}


double *** alocam_vd(unsigned int dx,unsigned int dy, unsigned int nr_el)

{
 double ***b;unsigned int i,j;
 //fprintf(stderr,"dy=%u, dx=%u",dy,dx);
 b=(double ***)malloc((size_t)(dx*sizeof(double **)));
 if (b==NULL)
 {
 fprintf(stderr,"eroare de alocare");
 exit(1);
 }
 for(i=0;i<dx;i++)
	{
	b[i]=(double **)malloc((size_t)(dy*sizeof(double *)));
	if (b[i]==NULL)
	 {
	 fprintf(stderr,"eroare de alocare");
	 exit(1);
	 }
	}
 for(i=0;i<dx;i++)
   for(j=0;j<dy;j++)
     b[i][j]=alocavd(nr_el);
return b;
}


void daloc_md(double **** m,unsigned int dx, unsigned int dy, unsigned int mdx)
{
 unsigned int i,j;
 for(i=0;i<dx;i++)
   for(j=0;j<dy;j++)
      dalocd((double **)m[i][j],mdx);
 for(i=0;i<dx;i++)
  free((double ***)m[i]);
 free((double ****)m);
}


void daloc_vd(double *** m,unsigned int dx, unsigned int dy)
{
 unsigned int i,j;
 for(i=0;i<dx;i++)
   for(j=0;j<dy;j++)
      freevd((double *)m[i][j]);
 for(i=0;i<dx;i++)
  free((double **)m[i]);
 free((double ***)m);
}

void afis_matd(double **a,unsigned int m, unsigned int n)
{
unsigned int i,j;
fprintf(stderr,"\n");
for(i=0;i<m;i++) 
  {
    for(j=0;j<n;j++)
      printf("a[%u][%u] = %g ; ",i,j,a[i][j]);
    printf("\n");
  }
}
