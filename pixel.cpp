#include<stdio.h>
#include<stdlib.h>
#include"pixel.h"

PIXEL::PIXEL(int k,int l)
{
  
  i=k;
  j=l;
  prec=NULL;
  suiv=NULL;
}

PIXEL::~PIXEL()
{

}


GPIXEL::GPIXEL(int k,int l, int v)
{
  
  i=k;
  j=l;
  val = v;
  prec=NULL;
  suiv=NULL;
}

GPIXEL::~GPIXEL()
{

}





void inpixel(PIXEL *p,PIXEL * &first,PIXEL * &last)
{
   
  
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
  
  else
    {
      last->suiv=p;
      p->suiv=NULL;
      p->prec=last;
      last=p;
      return;
    }
 
 
    
}

void in_pix_before_pix(PIXEL* &in_pix,PIXEL *pix,PIXEL* &first, PIXEL* &last)
{
  if(first==NULL)
    {
      if(pix != first)
	{
	  fprintf(stderr,"ERROR:in_pix_before_pix: non-concordance dans la liste !\n");
	  exit(1);
	}
      first=in_pix;
      first->suiv=NULL;
      first->prec=NULL;
      last=in_pix;
      last->prec=NULL;
      last->suiv=NULL;
      return;
    }
  else if(pix==first)
    {
      in_pix->suiv=first;
      in_pix->prec=first->prec;
      first->prec=in_pix;
      first=in_pix;
      return;
    }
  else
    {
      in_pix->prec=pix->prec;
      in_pix->suiv=pix;
      pix->prec->suiv=in_pix;
      pix->prec=in_pix;
    }
}

void in_pix_after_pix(PIXEL* &in_pix,PIXEL *pix,PIXEL* &first, PIXEL* &last)
{
  if(first==NULL)
    {
      if(pix != first)
	{
	  fprintf(stderr,"ERROR:in_pix_after_pix: non-concordance dans la  liste !\n");
	  exit(1);
	}
      first=in_pix;
      first->suiv=NULL;
      first->prec=NULL;
      last=in_pix;
      last->prec=NULL;
      last->suiv=NULL;
      return;
    }
  else if(pix==last)
    {
      in_pix->suiv=last->suiv;
      last->suiv=in_pix;
      in_pix->prec=last;
      last=in_pix;
      return;
    }
  else
    {
      in_pix->prec=pix;
      in_pix->suiv=pix->suiv;
      in_pix->suiv->prec=in_pix;
      pix->suiv=in_pix;
    }
}

void in_liste_after_pix(PIXEL* &inl_first,PIXEL* &inl_last,PIXEL *pix,PIXEL* &first, PIXEL* &last)
{
  if(inl_first==NULL)
    {
      fprintf(stderr,"ERROR:in_liste_after_pix:liste a introduir nulle !\n");
      exit(1);
    }
  if(first==NULL)
    {
      
      if(pix != first)
	{
	  fprintf(stderr,"ERROR:in_liste_after_pix: non-concordance dans la liste principale !\n");
	  exit(1);
	}
      first=inl_first;
      last=inl_last;
      inl_first=NULL;
      inl_last=NULL;
      return;
    }
  else if(pix==last)
    {
      
      last->suiv=inl_first;
      inl_first->prec=last;
      last=inl_last;
      inl_first=NULL;
      inl_last=NULL;
      return;
    }
  else
    {
      inl_first->prec=pix;
      inl_last->suiv=pix->suiv;
      inl_last->suiv->prec=inl_last;
      pix->suiv=inl_first;
      inl_first=NULL;
      inl_last=NULL;
    }
}
  
      
void outpixel(PIXEL * &p,PIXEL * &first,PIXEL * &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      delete p;
      p=NULL;
      if(first==NULL) last=NULL;
      else 
	{
	  first->prec=NULL;
	}
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

void freeliste_pixel(PIXEL * &first,PIXEL* &last)
{
  PIXEL *p=NULL;

  if(first==NULL) return;
  
  do
    {
      p=first;
      outpixel(p,first,last);
    }while(first != NULL);
}
      
void extractpixel(PIXEL* &p,PIXEL * &first,PIXEL * &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      p->suiv = NULL;
      p->prec=NULL;
      if(first==NULL) last=NULL;
      else first->prec=NULL;
      return;
     
    }
  if(p==last)
    {
      last=last->prec;
      p->prec = NULL;
      p->suiv = NULL;
      if(last==NULL) first=NULL;
      else last->suiv=NULL;
      return;
    }
  p->prec->suiv=p->suiv;
  p->suiv->prec=p->prec;
  p->prec=NULL;
  p->suiv=NULL;
}
 
void affiche_liste_pixel(PIXEL *first)
{
 
  PIXEL *p=NULL;
    
  if(first==NULL)
    {
      fprintf(stderr,"liste vide\n");
      return;
    }
  p=first;
  do
    {
     
      fprintf(stderr,"(i=%d,j=%d) ",p->i,p->j);
      p=p->suiv;
    }while(p != NULL);
  fprintf(stderr,"\n");
}

BOUCLE::BOUCLE(PIXEL *startb, PIXEL *endb)
{
  start = startb;
  end = endb;
  Npts = 0;
  prec = NULL;
  suiv = NULL;
}

BOUCLE::~BOUCLE()
{

}

void inboucle(BOUCLE *p,BOUCLE* &first,BOUCLE* &last)
{
   
  
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
  
  else
    {
      last->suiv=p;
      p->suiv=NULL;
      p->prec=last;
      last=p;
      return;
    }   
}

void outboucle(BOUCLE *p,BOUCLE* &first,BOUCLE* &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      delete p;
      if(first==NULL) last=NULL;
      else 
	{
	  first->prec=NULL;
	}
      return;
     
    }
  if(p==last)
    {
      last=last->prec;
      delete p;
      if(last==NULL) first=NULL;
      else last->suiv=NULL;
      return;
    }
  p->prec->suiv=p->suiv;
  p->suiv->prec=p->prec;
  delete p;
}

void freeboucle(BOUCLE* &first,BOUCLE* &last)
{
  BOUCLE *p=NULL;

  if(first==NULL) return;
  
  do
    {
      p=first;
      outboucle(p,first,last);
    }while(first != NULL);
}

// GPIXEL procedures

void ingpixel(GPIXEL *p,GPIXEL * &first,GPIXEL * &last)
{
   
  
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
  
  else
    {
      last->suiv=p;
      p->suiv=NULL;
      p->prec=last;
      last=p;
      return;
    }
 
 
    
}

void in_gpix_before_gpix(GPIXEL* &in_pix,GPIXEL *pix,GPIXEL* &first, GPIXEL* &last)
{
  if(first==NULL)
    {
      if(pix != first)
	{
	  fprintf(stderr,"ERROR:in_gpix_before_gpix: non-concordance dans la liste !\n");
	  exit(1);
	}
      first=in_pix;
      first->suiv=NULL;
      first->prec=NULL;
      last=in_pix;
      last->prec=NULL;
      last->suiv=NULL;
      return;
    }
  else if(pix==first)
    {
      in_pix->suiv=first;
      in_pix->prec=first->prec;
      first->prec=in_pix;
      first=in_pix;
      return;
    }
  else
    {
      in_pix->prec=pix->prec;
      in_pix->suiv=pix;
      pix->prec->suiv=in_pix;
      pix->prec=in_pix;
    }
}

void in_gpix_after_gpix(GPIXEL* &in_pix,GPIXEL *pix,GPIXEL* &first, GPIXEL* &last)
{
  if(first==NULL)
    {
      if(pix != first)
	{
	  fprintf(stderr,"ERROR:in_gpix_after_gpix: non-concordance dans la  liste !\n");
	  exit(1);
	}
      first=in_pix;
      first->suiv=NULL;
      first->prec=NULL;
      last=in_pix;
      last->prec=NULL;
      last->suiv=NULL;
      return;
    }
  else if(pix==last)
    {
      in_pix->suiv=last->suiv;
      last->suiv=in_pix;
      in_pix->prec=last;
      last=in_pix;
      return;
    }
  else
    {
      in_pix->prec=pix;
      in_pix->suiv=pix->suiv;
      in_pix->suiv->prec=in_pix;
      pix->suiv=in_pix;
    }
}

void in_liste_after_gpix(GPIXEL* &inl_first,GPIXEL* &inl_last,GPIXEL *pix,GPIXEL* &first, GPIXEL* &last)
{
  if(inl_first==NULL)
    {
      fprintf(stderr,"ERROR:in_liste_after_gpix:liste a introduire nulle !\n");
      exit(1);
    }
  if(first==NULL)
    {
      
      if(pix != first)
	{
	  fprintf(stderr,"ERROR:in_liste_after_gpix: non-concordance dans la liste principale !\n");
	  exit(1);
	}
      first=inl_first;
      last=inl_last;
      inl_first=NULL;
      inl_last=NULL;
      return;
    }
  else if(pix==last)
    {
      
      last->suiv=inl_first;
      inl_first->prec=last;
      last=inl_last;
      inl_first=NULL;
      inl_last=NULL;
      return;
    }
  else
    {
      inl_first->prec=pix;
      inl_last->suiv=pix->suiv;
      inl_last->suiv->prec=inl_last;
      pix->suiv=inl_first;
      inl_first=NULL;
      inl_last=NULL;
    }
}
  
      
void outgpixel(GPIXEL * &p,GPIXEL * &first,GPIXEL * &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      delete p;
      p=NULL;
      if(first==NULL) last=NULL;
      else 
	{
	  first->prec=NULL;
	}
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

void freeliste_gpixel(GPIXEL * &first,GPIXEL* &last)
{
  GPIXEL *p=NULL;

  if(first==NULL) return;
  
  do
    {
      p=first;
      outgpixel(p,first,last);
    }while(first != NULL);
}
      
void extractgpixel(GPIXEL* &p,GPIXEL * &first,GPIXEL * &last)
{
  
  if(first==NULL) return;

  if(p==first)
    {
      first=first->suiv;
      p->suiv = NULL;
      p->prec=NULL;
      if(first==NULL) last=NULL;
      else first->prec=NULL;
      return;
     
    }
  if(p==last)
    {
      last=last->prec;
      p->prec = NULL;
      p->suiv = NULL;
      if(last==NULL) first=NULL;
      else last->suiv=NULL;
      return;
    }
  p->prec->suiv=p->suiv;
  p->suiv->prec=p->prec;
  p->prec=NULL;
  p->suiv=NULL;
}
 
void affiche_liste_gpixel(GPIXEL *first)
{
 
  GPIXEL *p=NULL;
    
  if(first==NULL)
    {
      fprintf(stderr,"liste vide\n");
      return;
    }
  p=first;
  do
    {
     
      fprintf(stderr,"(i=%d,j=%d:val=%d) ",p->i,p->j,p->val);
      p=p->suiv;
    }while(p != NULL);
  fprintf(stderr,"\n");
}
