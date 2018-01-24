#include<stdio.h>
#include<stdlib.h>
#include "coordinates.h"
#include "voxel.h"

COORDINATES::COORDINATES(double i,double j,double k, double vp, double *vectp, int v)
{
	x=i;
	y=j;
	z=k;
	max_vp=vp;
	
	for (int n=0;n<3; n++)
	{
		max_dir[n]=vectp[n];
	}
	
	//max_dir[0]=vectp[0];
	//max_dir[1]=vectp[1];
	//max_dir[2]=vectp[2];
	vol=v;
	prec=NULL;
	suiv=NULL;

}

COORDINATES::~COORDINATES()
{
}


void incoordinates(COORDINATES *p,COORDINATES * &first,COORDINATES * &last)
{
  COORDINATES *q;
  q=first;
  
  if(first==NULL)
    {
      first=p;
      first->suiv=NULL;
      first->prec=NULL;
      last=p;
      last->prec=NULL;
      last->suiv=NULL;
      return;
    }
  /*if(p->val < first->val)
    { 
    p->suiv=first;
    p->prec=NULL;
    first->prec=p;
    first=p;
    return;
    }*/
  //if(p->val >= last->val)
  // {
  last->suiv=p;
  p->suiv=NULL;
  p->prec=last;
  last=p;
  return;
      //  }
  /* 
     do
     {
     q=q->suiv;
     }while(p->val >= q->val);
     p->suiv=q;
     p->prec=q->prec;
     q->prec->suiv=p;
     q->prec=p;*/
    
}

void delcoordinates(COORDINATES* &p,COORDINATES * &first,COORDINATES * &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      delete p;
      p=NULL;
      if(first==NULL) last=NULL;
      else first->prec=NULL;
      return;     
    }

  if(p==last)
    {
      last=last->prec;
      delete p;
      p=NULL;
      if(last==NULL) first=NULL;
      else last->suiv=NULL;
      return;
    }
  p->prec->suiv=p->suiv;
  p->suiv->prec=p->prec;
  delete p;
  p=NULL;
}

void extractcoordinates(COORDINATES* &p,COORDINATES * &first,COORDINATES * &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      p->suiv = NULL;
      if(first==NULL) last=NULL;
      else first->prec=NULL;
      return;
     
    }
  if(p==last)
    {
      last=last->prec;
      p->prec = NULL;
      if(last==NULL) first=NULL;
      else last->suiv=NULL;
      return;
    }
  p->prec->suiv=p->suiv;
  p->suiv->prec=p->prec;
  p->prec=NULL;
  p->suiv=NULL;
}

void freelistcoordinates(COORDINATES * &first,COORDINATES* &last)
{
  COORDINATES *p=NULL;

  if(first==NULL) return;
  
  do
    {
      p=first;
      delcoordinates(p,first,last);
    }while(first != NULL);
}