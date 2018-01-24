#ifndef PORT
#define PORT

#include<stdio.h>  
#include "image.h"
#include "procedures.h"

FILE* ouvert_fic(char *nom,char *code);


void lecture_ent_grey(FILE *ident,int *lar,int *hau,char** info);
void save_coupe(unsigned char **buf,int larg, int haut, char *fich);
void save_coupe(unsigned short **buf,int larg, int haut, char *fich);
BOOL read_coupe(FILE *id,int Larg,int Haut,unsigned char** &buf);
void read_dimension(FILE *id, int *larg, int* haut);
BOOL read_box_coupe(FILE *id,int Larg,int Haut,unsigned char **buf,BOX bp);
void InitPGM(GImage* &Ima,FILE *ident,BOX bp);
void InitPGM(GImage* &Ima,FILE *ident);
BOOL read_ROIcoupe(FILE *id,int Larg,int Haut,unsigned char** &buf,BOX bp);
void save_RLE(char *nom, unsigned short int **Buf, int Larg, int Haut);
void lecture_RLE(char *path, unsigned short int** &Buff,int Larg, int Haut);
#endif
