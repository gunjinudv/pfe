#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "memalloc.h"

void *** mat3Dalloc(unsigned int m_type,int Depth,int Haut,int Larg)
{
  int i,j,k;
  void ***buf=NULL;

 if((buf = (void***)calloc(Depth,sizeof(void**)))==NULL)
    {
      fprintf(stderr,"Allocation error ! Not enough memory space !\n");
      exit(1);
    }
  for(k=0;k<Depth;k++)
    {
      
      if((buf[k] = (void**)calloc(Haut,sizeof(void*)))==NULL)
	{
	  fprintf(stderr,"Allocation error : coupe %d ! Not enough memory space !\n",k);
	  exit(1);
	}
      for(i=0;i<Haut;i++)
	{
	  if((buf[k][i] = (void*)calloc(Larg,m_type))==NULL)
	    {
	      fprintf(stderr,"Allocation error : coupe %d line %d ! Not enough memory space !\n",k,i);
	      exit(1);
	    }
	}
    }  

  return buf;
}

void ** mat2Dalloc(unsigned int m_type,int Haut,int Larg)
{
  int i,j;
  void **buf=NULL;

 
      if((buf = (void**)calloc(Haut,sizeof(void*)))==NULL)
	{
	  fprintf(stderr," Not enough memory space !\n");
	  exit(1);
	}
      for(i=0;i<Haut;i++)
	{
	  if((buf[i] = (void*)calloc(Larg,m_type))==NULL)
	    {
	      fprintf(stderr,"Allocation error : line %d ! Not enough memory space !\n",i);
	      exit(1);
	    }
	}


return buf;
}

void  mat3Dfree(void*** &buf,int Depth,int Haut,int Larg)
{
  int i,j,k;
  for(k=0;k<Depth;k++)
    {
      for(i=0;i<Haut;i++)
	{
	  free(buf[k][i]);
	}
      free(buf[k]);
      
    }
  free(buf);
  buf = NULL;
}

void  mat2Dfree(void** &buf,int Haut,int Larg)
{
  int i,j;
  
  for(i=0;i<Haut;i++)
    {
      free(buf[i]);
    }
  
  
  free(buf);
  buf = NULL;
}
