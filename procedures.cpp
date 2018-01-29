#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>
#include "image.h"
#include "voxel.h"
#include "inout.h"
#include "procedures.h"
#include "memalloc.h"

#include "diagonalize.h"
#include "matrix.h"

#include "coordinates.h"


extern double PSZ;
extern double ZSZ;
extern double r_cyl, l_cyl;

int* coef_mask_26()
{
int *msk=NULL;

if((msk = (int*)calloc(26,sizeof(int)))==NULL)
   {
     fprintf(stderr,"ERROR: coef_mask_26 : alloc error !\n");
     exit(1);
   }
   
 msk[0]=msk[2]=msk[6]=msk[8]=11;
 msk[1]=msk[3]=msk[5]=msk[7]=msk[9]=msk[11]=7;
 msk[4]=msk[10]=msk[12]=5;
 for(int i=13;i<26;i++)
	msk[i]=msk[25-i];

	return(msk);
}

COORD * define_neigh()
{
 COORD *vois=NULL; 


 if((vois = (COORD*)calloc(8,sizeof(COORD)))==NULL)
   {
     fprintf(stderr,"ERROR: define_neigh : alloc error !\n");
     exit(1);
   }

 
  vois[0].i = -1;
  vois[0].j = -1;
  vois[1].i = -1;
  vois[1].j = 0;
  vois[2].i = -1;
  vois[2].j = 1;
  vois[3].i = 0;
  vois[3].j = 1;
  vois[4].i = 1; 
  vois[4].j = 1;
  vois[5].i = 1;
  vois[5].j = 0;
  vois[6].i = 1;
  vois[6].j = -1;
  vois[7].i = 0;
  vois[7].j = -1;

  return(vois);

}

void free_neigh(COORD *vois)
{

  

  free(vois);
}


VOIS::VOIS(int connex)
{
  Nbvois = connex;

  switch(connex)
    {
     case 4:
      if((crd = (coord*)calloc(4,sizeof(coord)))==NULL)
	{
	  fprintf(stderr,"Alloc voisinage 4-connexe: Espace insufisant !\n");
	  exit(1);
	}
      
      crd[0].k=0; crd[0].i=-1;crd[0].j=0;
      crd[1].k=0; crd[1].i=0;crd[1].j=-1;
      crd[2].k=0; crd[2].i=0;crd[2].j=1;
      crd[3].k=0; crd[3].i=1;crd[3].j=0;
      break;
    case 6:
      if((crd = (coord*)calloc(6,sizeof(coord)))==NULL)
	{
	  fprintf(stderr,"Alloc voisinage 6-connexe: Espace insufisant !\n");
	  exit(1);
	}
      crd[0].k=-1; crd[0].i=0;crd[0].j=0;
      crd[1].k=0; crd[1].i=-1;crd[1].j=0;
      crd[2].k=0; crd[2].i=0;crd[2].j=-1;
      crd[3].k=0; crd[3].i=0;crd[3].j=1;
      crd[4].k=0; crd[4].i=1;crd[4].j=0;
      crd[5].k=1; crd[5].i=0;crd[5].j=0;
      break;	
    case 18:
      if((crd = (coord*)calloc(18,sizeof(coord)))==NULL)
	{
	  fprintf(stderr,"Alloc voisinage 18-connexe: Espace insufisant !\n");
	  exit(1);
	}
      crd[0].k=-1; crd[0].i=-1;crd[0].j=0;
      crd[1].k=-1; crd[1].i=0;crd[1].j=-1;
      crd[2].k=-1; crd[2].i=0;crd[2].j=0;
      crd[3].k=-1; crd[3].i=0;crd[3].j=1;
      crd[4].k=-1; crd[4].i=1;crd[4].j=0;
      crd[5].k=0; crd[5].i=-1;crd[5].j=-1;
      crd[6].k=0; crd[6].i=-1;crd[6].j=0;
      crd[7].k=0; crd[7].i=-1;crd[7].j=1;
      crd[8].k=0; crd[8].i=0;crd[8].j=-1;
      crd[9].k=0; crd[9].i=0;crd[9].j=1;
      crd[10].k=0; crd[10].i=1;crd[10].j=-1;
      crd[11].k=0; crd[11].i=1;crd[11].j=0;
      crd[12].k=0; crd[12].i=1;crd[12].j=1;
      crd[13].k=1; crd[13].i=-1;crd[13].j=0;
      crd[14].k=1; crd[14].i=0;crd[14].j=-1;
      crd[15].k=1; crd[15].i=0;crd[15].j=0;
      crd[16].k=1; crd[16].i=0;crd[16].j=1;
      crd[17].k=1; crd[17].i=1;crd[17].j=0;
      break;

    case 26:
      if((crd = (coord*)calloc(26,sizeof(coord)))==NULL)
	{
	  fprintf(stderr,"Alloc voisinage 26-connexe: Espace insufisant !\n");
	  exit(1);
	}
      crd[0].k=-1; crd[0].i=-1;crd[0].j=-1;
      crd[1].k=-1; crd[1].i=-1;crd[1].j=0;
      crd[2].k=-1; crd[2].i=-1;crd[2].j=1;
      crd[3].k=-1; crd[3].i=0;crd[3].j=-1;
      crd[4].k=-1; crd[4].i=0;crd[4].j=0;
      crd[5].k=-1; crd[5].i=0;crd[5].j=1;
      crd[6].k=-1; crd[6].i=1;crd[6].j=-1;
      crd[7].k=-1; crd[7].i=1;crd[7].j=0;
      crd[8].k=-1; crd[8].i=1;crd[8].j=1;
      crd[9].k=0; crd[9].i=-1;crd[9].j=-1;
      crd[10].k=0; crd[10].i=-1;crd[10].j=0;
      crd[11].k=0; crd[11].i=-1;crd[11].j=1;
      crd[12].k=0; crd[12].i=0;crd[12].j=-1;
      crd[13].k=0; crd[13].i=0;crd[13].j=1;
      crd[14].k=0; crd[14].i=1;crd[14].j=-1;
      crd[15].k=0; crd[15].i=1;crd[15].j=0;
      crd[16].k=0; crd[16].i=1;crd[16].j=1;
      crd[17].k=1; crd[17].i=-1;crd[17].j=-1;
      crd[18].k=1; crd[18].i=-1;crd[18].j=0;
      crd[19].k=1; crd[19].i=-1;crd[19].j=1;
      crd[20].k=1; crd[20].i=0;crd[20].j=-1;
      crd[21].k=1; crd[21].i=0;crd[21].j=0;
      crd[22].k=1; crd[22].i=0;crd[22].j=1;
      crd[23].k=1; crd[23].i=1;crd[23].j=-1;
      crd[24].k=1; crd[24].i=1;crd[24].j=0;
      crd[25].k=1; crd[25].i=1;crd[25].j=1;
      break;

    default:
      fprintf(stderr,"Erreur voisinage: non-defini !\n");
      exit(1);
      break;

    }

}
      

VOIS::~VOIS()
{
  if(crd != NULL)
    free(crd);
}


void flash_buffer_X(char *nom,unsigned char ***buf,int X,int Y,int Z,double Omax)
{
  // sort l'image transversale, en semi-transparence, de buf
  int i,j,k;
  FILE *id;
  GImage *Ima=NULL;
  unsigned char val;
  double opac[256],Ipr,Icrt;
  char ** info=NULL;

	for(i=0;i<256;i++)
		opac[i] = Omax*(double)i/255.0;

  Ima=new GImage(Y,Z);
  
  for(k=1;k<Z-1;k++)
    for(j=0;j<Y;j++)
      {
	Ipr = (double)buf[k][X-1][j];
	for(i=X-1;i>0;i--)
	  {
		val = buf[k][i][j];
	    /*if((val = buf[k][i][j]) > 0)
	      //opac = 1.0 - (0.99*val)/255.0;
		  opac = Omax*(double)val/255.0;
	    else
	      opac = 0.0;
		  */
	    Icrt = (double)val*opac[val]+(1.0 - opac[val])*Ipr;
	    
	    if(Icrt > 255.0)
	      {
		Ipr = 255.0;
		//break;
	      }
	    else
	      Ipr = Icrt;
	    
	  } 
	
	Ima->Buf[k][j] = (unsigned char)Ipr;
      }

  id = ouvert_fic(nom,"wb");
  Ima->save_image_grey(id,info);
  fclose(id);
  delete Ima;
}

void flash_buffer_X(char *nom,unsigned int ***buf,int X,int Y,int Z,double Omax)
{
  // sort l'image transversale, en semi-transparence, de buf
  int i,j,k;
  FILE *id;
  GImage *Ima=NULL;
  unsigned char val;
  double opac[256],Ipr,Icrt;
  char ** info=NULL;

	for(i=0;i<256;i++)
		opac[i] = Omax*(double)i/255.0;

  Ima=new GImage(Y,Z);
  
  for(k=1;k<Z-1;k++)
    for(j=0;j<Y;j++)
      {
	Ipr = (double)buf[k][X-1][j];
	for(i=X-1;i>0;i--)
	  {
		val = max(1,min(255, buf[k][i][j]/10)); 
	    /*if((val = buf[k][i][j]) > 0)
	      //opac = 1.0 - (0.99*val)/255.0;
		  opac = Omax*(double)val/255.0;
	    else
	      opac = 0.0;
		  */
	    Icrt = (double)val*opac[val]+(1.0 - opac[val])*Ipr;
	    
	    if(Icrt > 255.0)
	      {
		Ipr = 255.0;
		//break;
	      }
	    else
	      Ipr = Icrt;
	    
	  } 
	
	Ima->Buf[k][j] = (unsigned char)Ipr;
      }

  id = ouvert_fic(nom,"wb");
  Ima->save_image_grey(id,info);
  fclose(id);
  delete Ima;
}

void flash_buffer_neg_X(char *nom,unsigned char ***buf,int X,int Y,int Z,double Omax)
{
  // sort l'image transversale, en semi-transparence, de buf
  int i,j,k;
  FILE *id;
  GImage *Ima=NULL;
  unsigned char val;
  double opac[256],Ipr,Icrt;
  char ** info=NULL;

	for(i=0;i<256;i++)
		opac[i] = Omax*(double)i/255.0;

  Ima=new GImage(Y,Z);
  
  for(k=1;k<Z-1;k++)
    for(j=0;j<Y;j++)
      {
	Ipr = (double)(255 - buf[k][X-1][j]);
	for(i=X-1;i>0;i--)
	  {
		val = 255 - buf[k][i][j];
	    /*if((val = buf[k][i][j]) > 0)
	      //opac = 1.0 - (0.99*val)/255.0;
		  opac = Omax*(double)val/255.0;
	    else
	      opac = 0.0;
		  */
	    Icrt = (double)val*opac[val]+(1.0 - opac[val])*Ipr;
	    
	    if(Icrt > 255.0)
	      {
		Ipr = 255.0;
		//break;
	      }
	    else
	      Ipr = Icrt;
	    
	  } 
	
	Ima->Buf[k][j] = (unsigned char)Ipr;
      }

  id = ouvert_fic(nom,"wb");
  Ima->save_image_grey(id,info);
  fclose(id);
  delete Ima;
}


void permute(double* &a,int i,int j)
  {
    double t;
    t = a[i];
    a[i] = a[j];
    a[j] = t;
  }



double prin_comp_analisys(VOXEL* in_first, double** &mat_vp, double* &val_pr,double &moyx,double &moyy,double &moyz)
{
	VOXEL *vox=NULL;
	int i;
	//double moyx=0.0, moyy=0.0, moyz=0.0;

    int N=0;
	vox = in_first;
	while(vox != NULL)
	{
	  N++;
	  moyx += (double)vox->i;
	  moyy += (double)vox->j;
	  moyz += (double)(-vox->k);
	  vox = vox->suiv;
	}
	double **mp = alocamd(3,N);    

	moyx = moyx/(double)N;
	moyy = moyy/(double)N;
	moyz = moyz/(double)N;
    
	i=0;
	vox = in_first;
	while(vox != NULL)
	{
		mp[0][i]  = ((double)vox->i-moyx);//*dcm->psize;
 		mp[1][i]  = ((double)vox->j-moyy);//*dcm->psize;
 		mp[2][i]  = ((double)(-vox->k)-moyz);//*dcm->zsize;
 
	 i++;
	 vox = vox->suiv;
	}
   
	compute_main_axes3D(mp,N, mat_vp, val_pr);
	
	/*for (i=0;i<3;i++)
	{
		val_pr[i]=3.0*sqrt(val_pr[i])/2.0;
	}
	*/
    
	double lp1, lp2, lp3;//estimation des longueurs des axes par les valeurs principales sous forme statistique 3*sigma = 3* sqrt(val_propre)
    
	//ordonnement  (attn: uniquement val propres; il faudrait faire la m�me chose pour les vect propres)
	/*
	if(val_pr[0] > val_pr[2])
	  permute(val_pr,0,2);
	if(val_pr[0] > val_pr[1])
	  permute(val_pr,0,1); 
	if(val_pr[1] > val_pr[2])
	  permute(val_pr,1,2);
	  */

	
	lp1 = 3.0*sqrt(val_pr[0])/2.0;//division par 2 pour le rayon
	lp2 = 3.0*sqrt(val_pr[1])/2.0;
	lp3 = 3.0*sqrt(val_pr[2])/2.0;
	
	val_pr[0]=lp1;
	val_pr[1]=lp2;
	val_pr[2]=lp3;

	return 0;
}



int getMaxPos(double *vp,int size)
{
	double max_vp=vp[0];
	int max_pos=0, i;

	for (i=1; i<size; i++)
	{
		if(vp[i]>max_vp)
		{
			max_vp=vp[i];
			max_pos=i;
		}
	}
	return max_pos;
}


void draw_cylindre(unsigned char*** &buf, COORDINATES *pt, double rad,double len, int H, int L, int N)
{

    double x0=pt->x;
    double y0=pt->y;
    double z0=pt->z;
    int i,j,k ;
    double dx,dy,dz ;
    dx=pt->max_dir[0] ;
    dy=pt->max_dir[1] ;
    dz=pt->max_dir[2] ;
    double norm;
    norm=sqrt(pow(dx,2)+pow(dy,2)+pow(dz,2));

    if(norm=!0.0)
    {
        dx=dx/norm;
        dy=dy/norm;
        dz=dz/norm;
    }

    double md ;
    double l ;
    l=len;
    md=max(fabs(dx),max(fabs(dy),fabs(dz)));

    double x,y,z ;
    for (int n=-l;n<=l;n++)
    {
        x=x0+n*dx/md ;
        y=y0+n*dy/md ;
        z=z0+n*dz/md ;

        if (x>=H || y>=L || -z>=N || x<0 || y<0 || z>0)
        {
            continue;
        }
        i=(int)floor(x+0.5);
        j=(int)floor(y+0.5);
        k=(int)floor(-z+0.5);

        if (i>=H || j>=L || k>=N || i<0 || j<0 || k<0)
        {
            continue;
        }
        buf[k][i][j]=100 ;

    }


    double r ;
    r=rad ;
    int d;
    d=1+(int)floor(sqrt(r*r+ l*l));
    double L1,L2,D;

    //fprintf(stderr,"d=%d\n",d);

    for (int u=-d;u<=d;u++)
    {
        for (int v=-d; v<=d; v++)
        {
            for (int w=-d; w<=d; w++)
            {
                x=x0+u ;
                y=y0+v ;
                z=z0+w ;

                if (x>=H || y>=L || -z>=N || x<0 || y<0 || z>0)
                {
                    continue;
                }

                L1=u*(dx)+ v*(dy)+w*(dz);
                L2=sqrt((double)u*u+(double)v*v+(double)w*w);
                D=sqrt(pow(L2,2)-pow(L1,2));


                if ((r-0.9)< D && D<(r+0.9))
                {
                    i=(int)floor(x+0.5);
                    j=(int)floor(y+0.5);
                    k=(int)floor(-z+0.5);

                    if (i>=H || j>=L || k>=N || i<0 || j<0 || k<0)
                    {
                        continue;
                    }
                    //fprintf(stderr,"point ...");
                    buf[k][i][j]=110 ;
                }
            }
        }
    }


}


