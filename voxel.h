#ifndef VOXELHEADER
#define VOXELHEADER

#include<stdio.h>


class VOXEL
{
public:

  int i,j,k,eti;
  VOXEL *prec;
  VOXEL *suiv;

VOXEL(int x,int y,int z,int etiq);
~VOXEL();
};


class LVOX
{
public:

  VOXEL *first,*last;
  int eti;
  LVOX *prec,*suiv;
LVOX(VOXEL *f,VOXEL *l,int etiq);
~LVOX();
};
  


void invoxel(VOXEL *p,VOXEL * &first,VOXEL * &last);
void delvoxel(VOXEL* &p,VOXEL * &first,VOXEL * &last);//ne pas l'appeler avec first(last) a la place de p; il faut: q=first; delvoxel(q,first,last);
void freelistevoxel(VOXEL * &first,VOXEL* &last);
void extractvoxel(VOXEL* &p,VOXEL * &first,VOXEL * &last);//ne pas l'appeler avec first(last) a la place de p; il faut: q=first; extractvoxel(q,first,last);


void addlvox(LVOX *l,LVOX* &first,LVOX* &last);
void dellvox(LVOX* &p,LVOX* &first,LVOX* &last);
void freelvox(LVOX* &first,LVOX* &last);
void extractlvox(LVOX* &p,LVOX* &first,LVOX* &last);
void assert(VOXEL *p);
void heapsort(VOXEL* &fn,VOXEL* &ln,bool increasing);
#endif
