#ifndef LISS
#define LISS

//partie a mettre dans un .h
typedef struct {
  int hauteur,largeur;//dimensions image
  double res_x,res_y;//resolution image : x= dir verticale; y = dir horiz; origine=coin gauche-haut de l'image
}Data2D;

typedef struct {
  int hauteur,largeur,nbcoupes;
  double Ih,Il,Iz;
  double res_x,res_y,res_z;
}Data;


void smooth_data_2D(unsigned char** &buf,Data2D vol,int rad,double sigma);
void smooth_data(unsigned char*** &buf,Data vol,int radx, int rady, int radz,double sigma);
#endif
