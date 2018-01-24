#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lissage.h"

//Dans le main, initialiser la struct de donnees avant l'appel de la procedure


/*
Data2D vol;
vol.hauteur = H;//hauteur de ton image
vol.largeur = L;//larg image
vol.res_x=1.0;
vol.res_y=1.0;//la resolution peut etre differente si ton image en x et y n'a pas les memes dimensions - par exemple, tu peux appliquer cette proc a lisser directement l'image non-binnee, en mettant vol.res_y = 0.5;
*/

//procedures de lissage

void smooth_data_2D(unsigned char** &buf,Data2D vol,int rad,double sigma)
//rad est la taille de la demi-fenetre, sigma est l'ecart type du gaussien
//buf est ta matrice image
{

  int i,j,k,n;
  short *line=NULL;
  double val, *kx=NULL, *ky=NULL, *kz=NULL;

  if(buf == NULL)
    {
      fprintf(stderr,"smooth_data: buffer null !\n");
      exit(1);
    }

  //calcul kernels Gaussien
  //fprintf(stderr,"res_x=%g,res_y=%g,res_z=%g,sigma=%g\n",vol.res_x,vol.res_y,vol.res_z,sigma);
  //  w(x) = 1/(sqrt(2*PI)*sigma) * exp(-x*x/2*sigma*sigma)
  kx = (double*) calloc(2*rad+1,sizeof(double));
  ky = (double*) calloc(2*rad+1,sizeof(double));
 
  
  kx[rad] = ky[rad] = 1.0;
  for(i=0;i<=rad;i++)
    {
      val = ((double)i*i*vol.res_x*vol.res_x)/(2.0*sigma*sigma);
      kx[rad -i] = kx[rad+i] = 1.0/exp(val);
      val = ((double)i*i*vol.res_y*vol.res_y)/(2.0*sigma*sigma);
      ky[rad -i] = ky[rad+i] = 1.0/exp(val);
      
     
    }
  //normalisation
  val = 0.0;
  for(i=-rad;i<=rad;i++)
    val += kx[rad+i];
  // fprintf(stderr,"\nvalx=%g\n",val);
  if(val != 0.0)
    {
      for(i=-rad;i<=rad;i++)
	{
	  kx[rad+i] = kx[rad+i]/val;
	  // fprintf(stderr,"kx[%d]=%g ",i,kx[rad+i]);
	}
    }
  // fprintf(stderr,"\n");
  val = 0.0;
  for(i=-rad;i<=rad;i++)
    val += ky[rad+i];
  //fprintf(stderr,"\nvaly=%g\n",val);
  if(val != 0.0)
    {
      for(i=-rad;i<=rad;i++)
	{
	  ky[rad+i] /= val;
	  //fprintf(stderr,"ky[%d]=%g ",i,ky[rad+i]);
	}
    }
  //fprintf(stderr,"\n");
  
 
  //filtrage en x (i) - dir verticale
  line = (short*)calloc(vol.hauteur,sizeof(short));
 
    for(j=0;j<vol.largeur;j++)
      {
	for(i=0;i<vol.hauteur;i++)
	  {
	    val = 0.0;
	    for(n=-rad;n<=rad;n++)
	      {
		if(i+n < 0 || i+n >= vol.hauteur)
		  continue;
		val += kx[n+rad]*buf[i+n][j];
	      }
	    line[i] = (short)val;
	  }
	for(i=0;i<vol.hauteur;i++)
	  buf[i][j] = line[i];
      }
  free(line); line=NULL;

  //filtrage en y (j)
  line = (short*)calloc(vol.largeur,sizeof(unsigned char));
  
    for(i=0;i<vol.hauteur;i++)
      {
	for(j=0;j<vol.largeur;j++)
	  {
	    val = 0.0;
	    for(n=-rad;n<=rad;n++)
	      {
		if(j+n < 0 || j+n >= vol.largeur)
		  continue;
		val += ky[n+rad]*buf[i][j+n];
	      }
	    line[j] = (short)val;
	  }
	for(j=0;j<vol.largeur;j++)
	  buf[i][j] = line[j];
      }
  free(line); line=NULL;

 
  free(kx);
  free(ky);
  free(kz);
}

void smooth_data(unsigned char*** &buf,Data vol,int radx, int rady, int radz,double sigma)
{

  int i,j,k,n;
  unsigned char *line=NULL;
  double val, *kx=NULL, *ky=NULL, *kz=NULL;

  if(buf == NULL)
    {
      fprintf(stderr,"smooth_data: buffer null !\n");
      exit(1);
    }

  //calcul kernels Gaussiens
  //fprintf(stderr,"res_x=%g,res_y=%g,res_z=%g,sigma=%g\n",vol.res_x,vol.res_y,vol.res_z,sigma);
  //  w(x) = 1/(sqrt(2*PI)*sigma) * exp(-x*x/2*sigma*sigma)
  kx = (double*) calloc(2*radx+1,sizeof(double));
  ky = (double*) calloc(2*rady+1,sizeof(double));
  kz = (double*) calloc(2*radz+1,sizeof(double));
  
  kx[radx] = ky[rady] = kz[radz] = 1.0;
  for(i=0;i<=radx;i++)
    {
      val = ((double)i*i*vol.res_x*vol.res_x)/(2.0*sigma*sigma);
      kx[radx -i] = kx[radx +i] = 1.0/exp(val);
     
      
      /*fprintf(stderr,"kx[%d]=%g ",rad+i,kx[rad+i]);
      fprintf(stderr,"ky[%d]=%g ",rad+i,ky[rad+i]);
      fprintf(stderr,"kz[%d]=%g ",rad+i,kz[rad+i]);*/
    }
  for(i=0;i<=rady;i++)
    {
       val = ((double)i*i*vol.res_y*vol.res_y)/(2.0*sigma*sigma);
      ky[rady -i] = ky[rady +i] = 1.0/exp(val);
    }
  for(i=0;i<=radz;i++)
    {
      val = ((double)i*i*vol.res_z*vol.res_z)/(2.0*sigma*sigma);
      kz[radz -i] = kz[radz +i] = 1.0/exp(val);
    }
  //normalisation
  val = 0.0;
  for(i=-radx;i<=radx;i++)
    val += kx[radx+i];
  // fprintf(stderr,"\nvalx=%g\n",val);
  if(val != 0.0)
    {
      for(i=-radx;i<=radx;i++)
	{
	  kx[radx +i] = kx[radx+i]/val;
	  // fprintf(stderr,"kx[%d]=%g ",i,kx[rad+i]);
	}
    }
  // fprintf(stderr,"\n");
  val = 0.0;
  for(i=-rady;i<=rady;i++)
    val += ky[rady +i];
  //fprintf(stderr,"\nvaly=%g\n",val);
  if(val != 0.0)
    {
      for(i=-rady;i<=rady;i++)
	{
	  ky[rady +i] /= val;
	  //fprintf(stderr,"ky[%d]=%g ",i,ky[rad+i]);
	}
    }
  //fprintf(stderr,"\n");
  val = 0.0;
  for(i=-radz;i<=radz;i++)
    val += kz[radz+i];
  //fprintf(stderr,"\nvalz=%g\n",val);
  if(val != 0.0)
    {
      for(i=-radz;i<=radz;i++)
	{
	  kz[radz +i] /= val;
	  //fprintf(stderr,"kz[%d]=%g ",i,kz[rad+i]);
	}
    }
  fprintf(stderr,"\n");
  //filtrage en x (i)
  line = (unsigned char*)calloc(vol.hauteur,sizeof(unsigned char));
  for(k=0;k<vol.nbcoupes;k++)
    for(j=0;j<vol.largeur;j++)
      {
	for(i=0;i<vol.hauteur;i++)
	  {
	    val = 0.0;
	    for(n=-radx;n<=radx;n++)
	      {
		if(i+n < 0 || i+n >= vol.hauteur)
		  continue;
		val += kx[n+radx]*buf[k][i+n][j];
	      }
	    line[i] = (unsigned char)val;
	  }
	for(i=0;i<vol.hauteur;i++)
	  buf[k][i][j] = line[i];
      }
  free(line); line=NULL;

  //filtrage en y (j)
  line = (unsigned char*)calloc(vol.largeur,sizeof(unsigned char));
  for(k=0;k<vol.nbcoupes;k++)
    for(i=0;i<vol.hauteur;i++)
      {
	for(j=0;j<vol.largeur;j++)
	  {
	    val = 0.0;
	    for(n=-rady;n<=rady;n++)
	      {
		if(j+n < 0 || j+n >= vol.largeur)
		  continue;
		val += ky[n+rady]*buf[k][i][j+n];
	      }
	    line[j] = (unsigned char)val;
	  }
	for(j=0;j<vol.largeur;j++)
	  buf[k][i][j] = line[j];
      }
  free(line); line=NULL;

  //filtrage en z (k)
  line = (unsigned char*)calloc(vol.nbcoupes,sizeof(unsigned char));
 
  for(i=0;i<vol.hauteur;i++)
    for(j=0;j<vol.largeur;j++)
      {
	for(k=0;k<vol.nbcoupes;k++)
	  {
	    val = 0.0;
	    for(n=-radz;n<=radz;n++)
	      {
		if(k+n < 0 || k+n >= vol.nbcoupes)
		  continue;
		val += kz[n+radz]*buf[k+n][i][j];
	      }
	    line[k] = (unsigned char)val;
	  }
	for(k=0;k<vol.nbcoupes;k++)
	  buf[k][i][j] = line[k];
      }
  free(line); line=NULL;
  free(kx);
  free(ky);
  free(kz);
}
