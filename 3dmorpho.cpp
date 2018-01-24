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

void erod_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe)
{
    if(bin == NULL || bout==NULL)
    {
        fprintf(stderr,"ERROR:granulometrie_sphere:image d'entree/sortie nulle !\n");
        exit(1);
    }

    int i,j,k,n,rad;
    bool nonzero;

    unsigned short ***cde=NULL;
    cde = (unsigned short***)mat3Dalloc(sizeof(unsigned short),Nbcoupe,Haut,Larg);//buffer contenant le calcul de la carte de dist








    //erosion taille R
    rad=5*R;
    distance_map_short(bin,cde,Haut,Larg,Nbcoupe,3,false);//use a dbase = 5
    //distcart(Itmp,bdist,0);
    nonzero=false;
    for(k=0;k<Nbcoupe;k++)
        for(i=0;i<Haut;i++)
            for(j=0;j<Larg;j++)
            {
                if(cde[k][i][j]>rad)
                {
                    bout[k][i][j]=255;
                    nonzero=true;
                }
                else
                    bout[k][i][j]=0;
            }

    fprintf(stderr,"\n");
    mat3Dfree((void***&)cde,Nbcoupe,Haut,Larg);


}

void dilat_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe)
{
    if(bin == NULL || bout==NULL)
    {
        fprintf(stderr,"ERROR:granulometrie_sphere:image d'entree/sortie nulle !\n");
        exit(1);
    }

    int i,j,k,n,rad;
    bool nonzero;

    unsigned short ***cde=NULL;
    cde = (unsigned short***)mat3Dalloc(sizeof(unsigned short),Nbcoupe,Haut,Larg);//buffer contenant le calcul de la carte de dist





    //dilatation taille n
    //nonzero=false;
    distance_map_short(bin,cde,Haut,Larg,Nbcoupe,3,true);//use a dbase = 5
    //distcart(Itmp,bdist,255);
    rad=5*R;
    for(k=0;k<Nbcoupe;k++)
        for(i=0;i<Haut;i++)
            for(j=0;j<Larg;j++)
            {
                if(cde[k][i][j]<=rad)
                {
                    //nonzero=true;
                    bout[k][i][j]=255;
                }
                else
                    bout[k][i][j]=0;
            }







    fprintf(stderr,"\n");
    mat3Dfree((void***&)cde,Nbcoupe,Haut,Larg);


}

void open_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe)
{
    if(bin == NULL || bout==NULL)
    {
        fprintf(stderr,"ERROR:granulometrie_sphere:image d'entree/sortie nulle !\n");
        exit(1);
    }

    int i,j,k,n,rad;
    bool nonzero;

    unsigned short ***cde=NULL;
    cde = (unsigned short***)mat3Dalloc(sizeof(unsigned short),Nbcoupe,Haut,Larg);//buffer contenant le calcul de la carte de dist








    //erosion taille R
    rad=5*R;
    distance_map_short(bin,cde,Haut,Larg,Nbcoupe,3,false);//use a dbase = 5
    //distcart(Itmp,bdist,0);
    nonzero=false;
    for(k=0;k<Nbcoupe;k++)
        for(i=0;i<Haut;i++)
            for(j=0;j<Larg;j++)
            {
                if(cde[k][i][j]>rad)
                {
                    bout[k][i][j]=255;
                    nonzero=true;
                }
                else
                    bout[k][i][j]=0;
            }
    if(nonzero)
    {
        //dilatation taille n
        distance_map_short(bout,cde,Haut,Larg,Nbcoupe,3,true);//use a dbase = 5
        //distcart(Itmp,bdist,255);
        for(k=0;k<Nbcoupe;k++)
            for(i=0;i<Haut;i++)
                for(j=0;j<Larg;j++)
                {
                    if(cde[k][i][j]<=rad)
                        bout[k][i][j]=255;
                    else
                        bout[k][i][j]=0;
                }
    }

    fprintf(stderr,"\n");
    mat3Dfree((void***&)cde,Nbcoupe,Haut,Larg);


}

void close_cd_sphere(unsigned char*** bin, unsigned char*** &bout,double R,int Haut,int Larg,int Nbcoupe)
{
    if(bin == NULL || bout==NULL)
    {
        fprintf(stderr,"ERROR:granulometrie_sphere:image d'entree/sortie nulle !\n");
        exit(1);
    }

    int i,j,k,n,rad;
    bool nonzero;

    unsigned short ***cde=NULL;
    cde = (unsigned short***)mat3Dalloc(sizeof(unsigned short),Nbcoupe,Haut,Larg);//buffer contenant le calcul de la carte de dist





    //dilatation taille n
    nonzero=false;
    distance_map_short(bin,cde,Haut,Larg,Nbcoupe,3,true);//use a dbase = 5
    //distcart(Itmp,bdist,255);
    rad=(int)floor(5.0*R);
    for(k=0;k<Nbcoupe;k++)
        for(i=0;i<Haut;i++)
            for(j=0;j<Larg;j++)
            {
                if(cde[k][i][j]<=rad)
                {
                    nonzero=true;
                    bout[k][i][j]=255;
                }
                else
                    bout[k][i][j]=0;
            }


    if(nonzero)
    {
        //erosion taille R

        distance_map_short(bout,cde,Haut,Larg,Nbcoupe,3,false);//use a dbase = 5
        //distcart(Itmp,bdist,0);

        for(k=0;k<Nbcoupe;k++)
            for(i=0;i<Haut;i++)
                for(j=0;j<Larg;j++)
                {
                    if(cde[k][i][j]>rad)
                    {
                        bout[k][i][j]=255;

                    }
                    else
                        bout[k][i][j]=0;
                }

    }




    fprintf(stderr,"\n");
    mat3Dfree((void***&)cde,Nbcoupe,Haut,Larg);


}

