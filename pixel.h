#ifndef PIXELHEADER
#define PIXELHEADER

#include<stdio.h>

class PIXEL
{
public:
  
  int i,j;
  PIXEL *prec;
  PIXEL *suiv;
  



PIXEL(int i,int j);
~PIXEL();
};

class BOUCLE
{
public:

  PIXEL *start, *end;
  int Npts;
  BOUCLE *prec, *suiv;

BOUCLE(PIXEL *startb, PIXEL *endb);
~BOUCLE();
};

class GPIXEL
{
public:
  
  int i,j,val;
  GPIXEL *prec;
  GPIXEL *suiv;
  



GPIXEL(int i,int j,int v);
~GPIXEL();
};



void inpixel(PIXEL *p,PIXEL * &first,PIXEL * &last);
void outpixel(PIXEL * &p,PIXEL * &first,PIXEL * &last);
void extractpixel(PIXEL* &p,PIXEL * &first,PIXEL * &last);
void freeliste_pixel(PIXEL * &first,PIXEL* &last);
void affiche_liste_pixel(PIXEL *first);
void in_pix_before_pix(PIXEL* &in_pix,PIXEL *pix,PIXEL* &first, PIXEL* &last);
void in_pix_after_pix(PIXEL* &in_pix,PIXEL *pix,PIXEL* &first, PIXEL* &last);
void in_liste_after_pix(PIXEL* &inl_first,PIXEL* &inl_last,PIXEL *pix,PIXEL* &first, PIXEL* &last);

void ingpixel(GPIXEL *p,GPIXEL * &first,GPIXEL * &last);
void outgpixel(GPIXEL * &p,GPIXEL * &first,GPIXEL * &last);
void extractgpixel(GPIXEL* &p,GPIXEL * &first,GPIXEL * &last);
void freeliste_gpixel(GPIXEL * &first,GPIXEL* &last);
void affiche_liste_gpixel(GPIXEL *first);
void in_gpix_before_gpix(GPIXEL* &in_pix,GPIXEL *pix,GPIXEL* &first, GPIXEL* &last);
void in_gpix_after_gpix(GPIXEL* &in_pix,GPIXEL *pix,GPIXEL* &first, GPIXEL* &last);
void in_liste_after_gpix(GPIXEL* &inl_first,GPIXEL* &inl_last,GPIXEL *pix,GPIXEL* &first, GPIXEL* &last);

void inboucle(BOUCLE *b, BOUCLE* &first,BOUCLE* &last);
void outboucle(BOUCLE *b, BOUCLE* &first,BOUCLE* &last);
void freeboucle(BOUCLE* &first,BOUCLE* &last);


#endif
