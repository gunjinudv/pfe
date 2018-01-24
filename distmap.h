#ifndef __DISTMAP
#define __DISTMAP
#include <limits.h>
//#include "axebtree.h"

#define MAXINT (UINT_MAX - 1000)
#define MAXSHRT (USHRT_MAX - 1000)

  struct melement
  {
    int i,j,k,value;
  };//mask elementla

class AMask //demi-masque attribuant des valeurs aux voisins en fonction de la connexite
{
public:
  int NE;//number of mask elements
  struct melement *mask;
  bool support;//whether support specified mask type
  AMask(int mtype);
  ~AMask();
  //  private:
  int dbase;//distance base
};

class BMask
  {
  public:
    int NE;//number of mask elements
    struct melement *mask;
    bool support;//whether support specified mask type
    BMask(int mtype);
    ~BMask();
    //  private:
    int dbase;//distance base
  };

class CMask
  {
  public:
    int NE;//number of mask elements
    struct melement *mask;
    bool support;//whether support specified mask type
    CMask(int mtype);
    ~CMask();
    //  private:
    int dbase;//distance base
  };

int distance_map(unsigned char ***buf0,unsigned int*** &buf1,int height,int width,int length, int mtype,bool non_zero_val);
int distance_map_short(unsigned char ***buf0,unsigned short*** &buf1,int height,int width,int length, int mtype,bool non_zero_val);
int distance_map_short(unsigned short ***buf0,unsigned short*** &buf1,int height,int width,int length, int mtype,bool non_zero_val);
int distance_map_short(unsigned short*** &buf1,int height,int width,int length, int mtype);
void limit_dilatation_cdist(unsigned char*** b_in,unsigned char*** &b_out,int Haut,int Larg,int Ncps,double radius);
void limit_erosion_cdist(unsigned char*** b_in,unsigned char*** &b_out,int Haut,int Larg,int Ncps,double radius);
int approx_distance_map(unsigned char ***buf0,unsigned char*** &buf1,int height,int width,int length, int mtype,bool non_zero_val);
int approx_distance_cal(unsigned char ***buf0,unsigned char*** &buf1,int height,int width,int length, int mtype,VOXEL *fref,VOXEL *lref);
int approx_distance_map(unsigned char*** &buf1,int height,int width,int length, int mtype,unsigned char valref, bool same_val);
int topologic_distance_map(unsigned char ***buf0,unsigned short*** &buf1,int height,int width,int length, int mtype);
int geodesic_distance_map(unsigned char ***buf0,unsigned int*** &bcd,int height,int width,int length,VOXEL *fref, VOXEL *lref);//carte de dist par rapport aux points  "ref" a l'interieur de composantes non-nulles
int geodesic_distance_map(unsigned char ***buf0,unsigned short*** &bcd,int height,int width,int length,VOXEL *fref, VOXEL *lref);//meme que precedente mais bcd est ushort
//int geodesic_distance_map(unsigned char ***buf0,unsigned int*** &bcd,int height,int width,int length,FNOD *fref, FNOD *lref,int masktype);
int geodesic_distance_map(unsigned char ***buf0,unsigned int*** &bcd,int height,int width,int length,VOXEL *fref, VOXEL *lref,int masktype);
//void setaxiscd(TNOD *nod,unsigned int*** &bcd);
#endif
