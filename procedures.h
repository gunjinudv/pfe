#ifndef PROCEDURE
#define PROCEDURE
#include "voxel.h"
#include "image.h"
#include "coordinates.h"

// #define min(x,y) (x < y ? x : y)
// #define max(x,y) (x > y ? x : y)

typedef struct{
  int i,j,k;
}coord;


typedef struct{
  int i,j;
}COORD;

// typedef struct{
  // int imin,imax,jmin,jmax;
// }BOX;

typedef struct{
  int imin,imax,jmin,jmax,kmin,kmax;
}BOX3D;

class VOIS{

public:

coord *crd;
int Nbvois;

VOIS(int connex);
~VOIS();
};

int* coef_mask_26();

void flash_buffer_X(char *nom,unsigned char ***buf,int X,int Y,int Z,double Omax);
void flash_buffer_X(char *nom,unsigned int ***buf,int X,int Y,int Z,double Omax);
void flash_buffer_neg_X(char *nom,unsigned char ***buf,int X,int Y,int Z,double Omax);

COORD * define_neigh();
void free_neigh(COORD *vois);
void permute(double* &a,int i,int j);
double prin_comp_analisys(VOXEL* in_first, double** &mat_vp, double* &val_pr,double &moyx,double &moyy,double &moyz);
int getMaxPos(double *vp,int size);
void draw_cylindre(unsigned char*** &buf, COORDINATES *pt, double rad,double len, int H, int L, int N);

#endif
