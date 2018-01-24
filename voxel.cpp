#include<stdio.h>
#include<stdlib.h>
#include"voxel.h"


VOXEL::VOXEL(int x,int y,int z,int etiq)
{
  
  i=x;
  j=y;
  k=z;
  eti=etiq;
  prec=NULL;
  suiv=NULL;
}

VOXEL::~VOXEL()
{

}

void invoxel(VOXEL *p,VOXEL * &first,VOXEL * &last)
{
  VOXEL *q;
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

void delvoxel(VOXEL* &p,VOXEL * &first,VOXEL * &last)
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

void extractvoxel(VOXEL* &p,VOXEL * &first,VOXEL * &last)
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

void freelistevoxel(VOXEL * &first,VOXEL* &last)
{
  VOXEL *p=NULL;

  if(first==NULL) return;
  
  do
    {
      p=first;
      delvoxel(p,first,last);
    }while(first != NULL);
}
      
 
LVOX::LVOX(VOXEL *f,VOXEL *l,int etiq)
{
  first=f;
  last=l;
  eti=etiq;
  prec=NULL;
  suiv=NULL;
}
LVOX::~LVOX()
{

}


void addlvox(LVOX *l,LVOX* &first,LVOX* &last)
{

   if(first==NULL)
    {
      first=l;
      first->suiv=NULL;
      first->prec=NULL;
      last=l;
      last->prec=NULL;
      last->suiv=NULL;
      return;
    }
  
   last->suiv=l;
   l->suiv=NULL;
   l->prec=last;
   last=l;
}


void dellvox(LVOX* &p,LVOX* &first,LVOX* &last)
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

void freelvox(LVOX* &first,LVOX* &last)
{
  LVOX *p=NULL;
  
  if(first==NULL) return;
  
  do
    {
      p=first;
      dellvox(p,first,last);
    }while(first != NULL);
}

void extractlvox(LVOX* &p,LVOX* &first,LVOX* &last)
{
  //enleve p de la liste sans l'effacer
  if(first==NULL)
    {
      fprintf(stderr,"ERROR: extractlvox: liste vide !\n");
      exit(1);
    }
  
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
      p->prec=NULL;
      if(last==NULL) first=NULL;
      else last->suiv=NULL;
      return;
    }
  p->prec->suiv=p->suiv;
  p->suiv->prec=p->prec;
  p->prec = NULL;
  p->suiv = NULL;
}

void assert(VOXEL *p)
{
  if(p==NULL)
    {
      fprintf(stderr,"VOXEL allocation error! Not enough memory space\n");
      exit(1);
    }
}

void heapsort(VOXEL* &fn,VOXEL* &ln,bool increasing)
{
  //procedure adaptee a une liste VOXEL a partir de Numerical Receipts in C
  //sorting effectue a partir des champs de (fn)->adr->eti supposes mis a jour
  unsigned long N,i,ir,j,l;
  VOXEL **ra=NULL;
  VOXEL *rra=NULL;
  VOXEL *f;

  //transcription de la liste en vecteur
  N=0;  
  f=fn;
  while(f != NULL)
    {
      N++;
      f=f->suiv;
    }
  
  if(N<2)
    return;
  
  ra = (VOXEL**)calloc(N,sizeof(VOXEL*));
  if(ra==NULL)
    {
      fprintf(stderr,"heapsort: memory allocation error. Sorting not performed\n");
      return;
    }
  for(i=0;i<N;i++)
    {
      ra[i]=new VOXEL(0,0,0,0);
      assert(ra[i]);
    }

  f=fn;
  for(i=0;i<N && f!=NULL;i++)
    {
      ra[i]->i = f->i;
      ra[i]->j = f->j;
      ra[i]->k = f->k;
      ra[i]->eti = f->eti;
      f = f->suiv;
    }

  //test
//    for(i=0;i<N ;i++)
//      fprintf(stderr,"%d ",ra[i]->eti);
  //begin sorting increasing order
  
  l = N>>1;
  ir = N-1;
  
  while(1)//for( ; ;)
    {
      if(l>0)
	rra = ra[--l];
      else
	{
	  rra = ra[ir];
	  ra[ir] = ra[0];
	  if(--ir == 0)
	    {
	      ra[0]=rra;
	      break;
	    }
	}
      i=l;
      j=l+1;
      while(j <= ir)
	{
	  if(j < ir && ra[j]->eti < ra[j+1]->eti)
	    j++;
	  if(rra->eti < ra[j]->eti)
	    {
	      ra[i] = ra[j];
	      i=j;
	      j <<= 1;
	    }
	  else
	    j = ir+1;
	}
      ra[i] = rra;
    }
  //test
 //    fprintf(stderr,"\n");
//   for(i=0;i<N ;i++)
//     fprintf(stderr,"%d ",ra[i]->eti);

  //remise dans la liste
  if(increasing)
    {
      f=fn;
      for(i=0;i<N && f!=NULL;i++)
	{
	  f->i = ra[i]->i;
	  f->j = ra[i]->j;
	  f->k = ra[i]->k;
	  f->eti = ra[i]->eti;
	  f = f->suiv;
	}
    }
  else
    {
      f=ln;
      for(i=0;i<N && f!=NULL;i++)
	{
	  f->i = ra[i]->i;
	  f->j = ra[i]->j;
	  f->k = ra[i]->k;
	  f->eti = ra[i]->eti;
	  f = f->prec;
	}
    }
  for(i=0;i<N;i++)
    delete ra[i];
  free(ra);
}
