#ifndef IMAHEADER
#define IMAHEADER
 
#include<stdio.h>
#define False 0
#define True 1
//#define NULL 0

#define max(x,y) (x >= y ? x : y)
#define min(x,y) (x <= y ? x : y)

typedef struct{
unsigned char r,g,b;
}color;

typedef struct{
  int imin,imax,jmin,jmax;
}BOX;

typedef unsigned char BOOL;


class GImage
{

public :
int Larg,Haut;
unsigned char **Buf;
BOOL Bin;
GImage *Associe;

GImage(int larg, int haut);
~GImage();
void Error(int i);
void ImageCopy(GImage *Ima);
void lecture_image_grey(FILE *ident);
void lecture_image_grey(FILE *ident,BOX box);
void save_image_grey(FILE *ident,char** info);
void Init(unsigned char **buf);
void Copyto(unsigned char** &buf);// pas de test de dimensions !
};

class KImage
{
public :
int Larg,Haut;
color **Buf;
BOOL Bin;
KImage *Associe;

KImage(int larg, int haut);
  //GreyCopy(GImage *Ima);
~KImage();
void Error(int i);
void ImageCopy(KImage *Ima);
void ImageGCopy(GImage *Ima);
void save_image_color(FILE *ident,char** info);
void lecture_image_color(FILE *ident);
};


class XImage
{

public :
int Larg,Haut;
unsigned short **Buf;


XImage(int larg, int haut);
~XImage();
/*void Error(int i);
void ImageCopy(GImage *Ima);
void lecture_image_grey(FILE *ident);
void save_image_grey(FILE *ident,char** info);
void Init(unsigned char **buf);
void Copyto(unsigned char** &buf);// pas de test de dimensions !*/
};



void CopyGImage(GImage* &Iout, GImage *Iin);
void CopyKImage(KImage* &Iout, KImage *Iin);
void prepare(GImage* &Ima,GImage *Mask);
BOOL imageoverflow(int i,int j,int haut,int larg);
BOOL imageoverflow(int i,int j,GImage *Ima);
BOOL imagediffer(GImage *Ima,GImage *Iin);
void InitCoronalMsk(unsigned char*** buf,GImage* &Iin,int i,int haut,int larg,int Ncp,GImage *Msk);//Msk est une image axiale - initialisation uniquement dans la partie non-zero du Msk
void InitCoronal(unsigned char*** buf,GImage* &Iin,int i,int haut,int larg,int Ncp);
void InitSagittalMsk(unsigned char*** buf,GImage* &Iin,int j,int haut,int larg,int Ncp,GImage *Msk);
void InitSagittal(unsigned char*** buf,GImage* &Iin,int j,int haut,int larg,int Ncp);
void CopyCoronal(GImage* Iin,unsigned char*** &buf,int i,int haut,int larg,int Ncp);
void CopySagittal(GImage* Iin,unsigned char*** &buf,int j,int haut,int larg,int Ncp);

#endif
