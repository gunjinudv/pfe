#ifndef COORDINATESHEADER
#define COORDINATESHEADER
#include<stdio.h>
#include "voxel.h"


class COORDINATES
{
public:
	int vol;
	double max_vp, max_dir[3];
	double x, y, z;
	COORDINATES *prec;
	COORDINATES *suiv;

	COORDINATES(double i,double j,double k, double vp, double *vectp, int v);
	~COORDINATES();
};

void incoordinates(COORDINATES *p,COORDINATES * &first,COORDINATES * &last);
void delcoordinates(COORDINATES* &p,COORDINATES * &first,COORDINATES * &last);//ne pas l'appeler avec first(last) a la place de p; il faut: q=first; delcoordinates(q,first,last);
void freelistcoordinates(COORDINATES * &first,COORDINATES* &last);
void extractcoordinates(COORDINATES* &p,COORDINATES * &first,COORDINATES * &last);//ne pas l'appeler avec first(last) a la place de p; il faut: q=first; extractcoordinates(q,first,last);




#endif