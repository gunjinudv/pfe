#ifndef PROJECT_SEG_CATALYS_3DMORPHO_H
#define PROJECT_SEG_CATALYS_3DMORPHO_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "image.h"
#include "voxel.h"
#include "inout.h"
#include "morpho.h"
#include "memalloc.h"
#include "distmap.h"

void erod_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe);
void dilat_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe);
void open_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe);
void close_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe);

#endif //PROJECT_SEG_CATALYS_3DMORPHO_H
