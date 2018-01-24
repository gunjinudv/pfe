#ifndef MORPHO
#define MORPHO
#include "pixel.h"

void binarisation(GImage *Iin, GImage* &Iout, unsigned char seuil_bas, unsigned char seuil_haut);
BOOL nfobinarisation(GImage *Iin, GImage* &Iout, unsigned char seuil_bas, unsigned char seuil_haut);
void seuillage(GImage *Iin, GImage* &Iout, unsigned char seuil_bas, unsigned char seuil_haut);
BOOL erosioncarre(GImage *Iin, GImage* &Iout, int taille);
BOOL erosion4connex(GImage *Iin, GImage* &Iout, int taille);
void dilatationcarre(GImage *Iin, GImage* &Iout, int taille);
void dilatation4connex(GImage *Iin, GImage* &Iout, int taille); 
void recons(GImage *Iin, GImage * Mask, GImage* &Iout);
void difpos(GImage *I1, GImage *I2, GImage* &Iout);
void CConexion(GImage *Iin, GImage* &Iout);
void inversion(GImage *Iin, GImage* &Iout);
void Algebre(GImage *I1, GImage *I2, GImage* &Iout, char c);
void BoucheTrous(GImage *Iin, GImage* &Iout);
void BoucheTrous4C(GImage *Iin, GImage* &Iout);
int etiquettage(GImage *Iin,int **buf,unsigned char val);
int etiquettage_c(GImage *Iin,int** buf,unsigned char val);
int etiquettage_4connex(GImage *Iin,int **buf,unsigned char val);
int old_etiquettage(GImage *Iin,int **buf,unsigned char val);
int old_etiquettage_4connex(GImage *Iin,int **buf,unsigned char val);
void recons4connex(GImage *Iin, GImage * Mask, GImage* &Iout);
void minimum(GImage *Iin,GImage* &Iout);
void maximum(GImage *Iin,GImage* &Iout);
void particules(GImage *Iin,GImage* &Iout,unsigned char val,char *nb_keep);
void nderosioncarre(GImage *Iin, GImage* &Iout, int taille);//pas finie
void SMDCC_Y(GImage *Iin, GImage* &Iout, int taille);
void recons_gris(GImage *Iin, GImage * Mask, GImage* &Iout);
void construct_disk(double R,PIXEL* &f_cerc,PIXEL* &l_cerc,int *Npc);
void open_gdisk(GImage* &Ima,int R);
void close_gdisk(GImage* &Ima,int R);
void erod_gdisk(GImage* &Ima,int R);
void dilat_gdisk(GImage* &Ima,int R);
BOOL amincissement(GImage *Iin, GImage* &Iout, int taille);
void granulometrie_disk(GImage *Iin, GImage* &Iout);
void open_cd_disk(GImage *Iin, GImage* &Iout,int R);
void close_cd_disk(GImage *Iin, GImage* &Iout,int R);
#endif
