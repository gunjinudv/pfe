#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include"image.h"
#include"morpho.h"
#include"procedures.h"
#include"pixel.h"
#include "memalloc.h"
#include "distcart.h"

#define MIN(x,y)  (x <= y ? x : y ) 
#define MAX(x,y)  (x >= y ? x : y )  


void binarisation(GImage *Iin, GImage* &Iout, unsigned char seuil_bas, unsigned char seuil_haut)
{
  int i,j;
 
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:binarisation: image d'entree nulle !\n");
      exit(1);
    }

  if(Iout==NULL)
    {
      Iout=new GImage(Iin->Larg, Iin->Haut);
      //  if((Iout->Larg == Iin->Larg) && (Iout->Haut == Iin->Haut)) fprintf(stderr,"cucu\n");
    }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:binarisation: ");
      Iin->Error(1);
      exit(1);
    }

  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if((Iin->Buf[i][j] >= seuil_bas) && (Iin->Buf[i][j] <= seuil_haut))
	  Iout->Buf[i][j]=255;
	else
	  Iout->Buf[i][j]=0;
      }
  // fprintf(stderr,"cucu\n");
  
  Iout->Bin=True;

}

BOOL nfobinarisation(GImage *Iin, GImage* &Iout, unsigned char seuil_bas, unsigned char seuil_haut)
{
  int i,j;
  BOOL nonzero=False;
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:binarisation: image d'entree nulle !\n");
      exit(1);
    }

  if(Iout==NULL)
    {
      Iout=new GImage(Iin->Larg, Iin->Haut);
      //  if((Iout->Larg == Iin->Larg) && (Iout->Haut == Iin->Haut)) fprintf(stderr,"cucu\n");
    }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:binarisation: ");
      Iin->Error(1);
      exit(1);
    }

  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if((Iin->Buf[i][j] >= seuil_bas) && (Iin->Buf[i][j] <= seuil_haut))
	  {
	    Iout->Buf[i][j]=255;
	    nonzero=True;
	  }
	else
	  Iout->Buf[i][j]=0;
      }
  // fprintf(stderr,"cucu\n");
  
  Iout->Bin=True;
  return(nonzero);

}


void seuillage(GImage *Iin, GImage* &Iout, unsigned char seuil_bas, unsigned char seuil_haut)
{
  int i,j;

  if(Iin == NULL)
    {
      fprintf(stderr,"ERROR:seuillage: image d'entree nulle\n");
      exit(1);
    }
 
  if(Iout==NULL)
    Iout=new GImage(Iin->Larg, Iin->Haut);
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:seuillage: ");
      Iin->Error(1);
      exit(1);
    }

  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if((Iin->Buf[i][j] >= seuil_bas) && (Iin->Buf[i][j] <= seuil_haut))
	  Iout->Buf[i][j]=Iin->Buf[i][j];
	else
	  Iout->Buf[i][j]=0;
      }
  
}


BOOL erosioncarre(GImage *Iin, GImage* &Iout, int taille) /*renvoie True si l'image sortie est differente de zero*/
{
  int i,j,k,l;
  BOOL mark, renvoi=False;



  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:erosioncarre: image d'entree nulle !\n");
      exit(1);
    }
  
  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR:erosioncarre: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:erosioncarre: ");
      Iin->Error(1);
      exit(1);
    }
  
  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if(Iin->Buf[i][j] != 0)  
	  {
	    mark=False;
	    for(k = -taille;k<=taille;k++)
	      {
	
		if((i+k <0) || (i+k >= Iin->Haut)  || (mark==True)) continue;
		else
		  {
		    
		    for(l=-taille;l<=taille;l++)
		      {
			if((j+l<0) || (j+l >= Iin->Larg) || (mark==True)) continue;
			 
			else if(Iin->Buf[i+k][j+l]==0)
			      mark=True;
			   
			  
		      }
		  }
	      }
	    if(mark==True)
	      {
		Iout->Buf[i][j]=0;
		
	      }
	    else 
	      {
		Iout->Buf[i][j]=Iin->Buf[i][j];
		renvoi=True;
	      }
	  }
	else  Iout->Buf[i][j]=0;
      }

 
  return(renvoi);
}

BOOL erosion4connex(GImage *Iin, GImage* &Iout, int taille) /*renvoie True si l'image sortie est differente de zero*/
{
  int i,j,k,l;
  BOOL mark, renvoi=False;



  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:erosion4connex: image d'entree nulle !\n");
      exit(1);
    }
  
  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR:erosion4connex: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:erosion4connex: ");
      Iin->Error(1);
      exit(1);
    }
  
  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if(Iin->Buf[i][j] != 0)  
	  {
	    mark=False;
	    for(k = -taille;k<=taille;k++)
	      {
	
		if((i+k <0) || (i+k >= Iin->Haut)  || (mark==True)) continue;
		else
		  {
		    
		    for(l=-taille;l<=taille;l++)
		      {
			if((j+l<0) || (j+l >= Iin->Larg) || (k*l != 0)||(mark==True)) continue;
			 
			else if(Iin->Buf[i+k][j+l]==0)
			      mark=True;
			   
			  
		      }
		  }
	      }
	    if(mark==True)
	      {
		Iout->Buf[i][j]=0;
		
	      }
	    else 
	      {
		Iout->Buf[i][j]=Iin->Buf[i][j];
		renvoi=True;
	      }
	  }
	else  Iout->Buf[i][j]=0;
      }

 
  return(renvoi);
}


void dilatationcarre(GImage *Iin, GImage* &Iout, int taille) 
{
  int i,j,k,l;
  BOOL mark;



  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:dilatationcarre: image d'entree nulle !\n");
      exit(1);
    }
 
  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR:dilatationcarre: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:dilatationcarre: ");
      Iin->Error(1);
      exit(1);
    }

  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if(Iin->Buf[i][j] == 0)
	  {
	    mark=False;
	    for(k=-taille;k<=taille;k++)
	      {
		if((i+k <0) || (i+k >= Iin->Haut) || (mark==True)) continue;
		else
		  {
		    for(l=-taille;l<=taille;l++)
		      {
			if((j+l<0) || (j+l >= Iin->Larg) || (mark==True)) continue;
			else if(Iin->Buf[i+k][j+l]!=0)
			   mark=True;
		      }
		  }
	      }
	    if(mark==True)
	      Iout->Buf[i][j]=255;
	    else 
	      Iout->Buf[i][j]=0;
	    
	  }
	else
	  Iout->Buf[i][j]=255;
      }

 
}

void dilatation4connex(GImage *Iin, GImage* &Iout, int taille) 
{
  int i,j,k,l;
  BOOL mark;



  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR: dilatation4connex: image d'entree nulle !\n");
      exit(1);
    }
 
  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR: dilatation4connex: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR: dilatation4connex: ");
      Iin->Error(1);
      exit(1);
    }

  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if(Iin->Buf[i][j] == 0)
	  {
	    mark=False;
	    for(k=-taille;k<=taille;k++)
	      {
		if((i+k <0) || (i+k >= Iin->Haut) || (mark==True)) continue;
		else
		  {
		    for(l=-taille;l<=taille;l++)
		      {
			if((j+l<0) || (j+l >= Iin->Larg) || (k*l !=0)|| (mark==True)) continue;
			else if(Iin->Buf[i+k][j+l]!=0)
			   mark=True;
		      }
		  }
	      }
	    if(mark==True)
	      Iout->Buf[i][j]=255;
	    else 
	      Iout->Buf[i][j]=0;
	    
	  }
	else
	  Iout->Buf[i][j]=255;
      }

 
}


void recons(GImage *Iin, GImage * Mask, GImage* &Iout)
{
  int i,j,k,l;
  BOOL mark;
  int Niter=0; 

   
  if((Iin==NULL) || (Mask==NULL))
    {
      fprintf(stderr,"ERROR:recons: image d'entree ou masque nulle !\n");
      exit(1);
    }

  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR:recons: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Mask->Bin==False)
     {
       fprintf(stderr,"ERROR:recons: Image masque non binaire !"); 
       exit(1);
     }
   
   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
   else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut) || (Iout->Larg != Mask->Larg) || (Iout->Haut != Mask->Haut))
     {
       fprintf(stderr,"ERROR:recons: ");
       Iin->Error(1);
       exit(1);
     }
	      
   /* pretraitement */

   for(i=0;i< Iin->Haut; i++)
     for(j=0;j< Iin->Larg;j++)
       {
	 if(Iin->Buf[i][j] != 0)
	   {
	     if(Mask->Buf[i][j] != 0)
	       Iout->Buf[i][j]=255;
	     else
	       Iout->Buf[i][j]=128;
	   }
	 else
	   Iout->Buf[i][j]=0;
       }
   /* end pretraitement */

  
   



    do
     {
       mark=False;
       Niter++;
      
       for(i=1;i< Iout->Haut-1; i++)
	 for(j=1;j< Iout->Larg-1;j++)
	   {
	     if(Iout->Buf[i][j]==255)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==128) && (k+l+k*l != 0))
			 {
			   Iout->Buf[i+k][j+l]=255;
			   mark=True;
			 }
		     }
	       }
	     else if(Iout->Buf[i][j]==128)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==255) && (k+l+k*l != 0))
			 {
			   Iout->Buf[i][j]=255;
			   mark=True;
			   break;
			 }
		     }
	       }
	     
	   }
	    

       if(mark==False)  break;

       Niter++;

        for(i=Iout->Haut-2;i>0; i--)
	 for(j=Iout->Larg-2;j>0;j--)
	   {
	     if(Iout->Buf[i][j]==255)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==128) && (k+l+k*l != 0))
			 {
			   Iout->Buf[i+k][j+l]=255;
			   mark=True;
			 }
		     }
	       }
	     else if(Iout->Buf[i][j]==128)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==255) && (k+l+k*l != 0))
			 {
			   Iout->Buf[i][j]=255;
			   mark=True;
			   break;
			 }
		     }
	       }
	     
	   }

     }while(mark==True);
	       




   for(i=0;i< Iout->Haut; i++)
     for(j=0;j< Iout->Larg;j++)
       {
	 if(Iout->Buf[i][j] == 128)
	   Iout->Buf[i][j]=0;
       }

   Iout->Bin = True;
   fprintf(stderr,"recons: %d iteration(s) \n",Niter);

}



void recons4connex(GImage *Iin, GImage * Mask, GImage* &Iout)
{
  int i,j,k,l;
  BOOL mark;
  int Niter=0; 

   
  if((Iin==NULL) || (Mask==NULL))
    {
      fprintf(stderr,"ERROR:recons4connex: image d'entree ou masque nulle !\n");
      exit(1);
    }

  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR:recons4connex: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Mask->Bin==False)
     {
       fprintf(stderr,"ERROR:recons4connex: Image masque non binaire !"); 
       exit(1);
     }
   
   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
   else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut) || (Iout->Larg != Mask->Larg) || (Iout->Haut != Mask->Haut))
     {
       fprintf(stderr,"ERROR:recons4connex: ");
       Iin->Error(1);
       exit(1);
     }
	      
   /* pretraitement */

   for(i=0;i< Iin->Haut; i++)
     for(j=0;j< Iin->Larg;j++)
       {
	 if(Iin->Buf[i][j] != 0)
	   {
	     if(Mask->Buf[i][j] != 0)
	       Iout->Buf[i][j]=255;
	     else
	       Iout->Buf[i][j]=128;
	   }
	 else
	   Iout->Buf[i][j]=0;
       }
   /* end pretraitement */

  
   



    do
     {
       mark=False;
       Niter++;
      
       for(i=1;i< Iout->Haut-1; i++)
	 for(j=1;j< Iout->Larg-1;j++)
	   {
	     if(Iout->Buf[i][j]==255)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==128) && (k+l+k*l != 0) && (k*l==0))
			 {
			   Iout->Buf[i+k][j+l]=255;
			   mark=True;
			 }
		     }
	       }
	     else if(Iout->Buf[i][j]==128)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==255) && (k+l+k*l != 0) && (k*l==0))
			 {
			   Iout->Buf[i][j]=255;
			   mark=True;
			   break;
			 }
		     }
	       }
	     
	   }
	    

       if(mark==False)  break;

       Niter++;

        for(i=Iout->Haut-2;i>0; i--)
	 for(j=Iout->Larg-2;j>0;j--)
	   {
	     if(Iout->Buf[i][j]==255)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==128) && (k+l+k*l != 0) && (k*l==0))
			 {
			   Iout->Buf[i+k][j+l]=255;
			   mark=True;
			 }
		     }
	       }
	     else if(Iout->Buf[i][j]==128)
	       {
		 for(k=-1;k<=1;k++)
		   for(l=-1;l<=1;l++)
		     {
		       
		       if((Iout->Buf[i+k][j+l]==255) && (k+l+k*l != 0) && (k*l==0))
			 {
			   Iout->Buf[i][j]=255;
			   mark=True;
			   break;
			 }
		     }
	       }
	     
	   }

     }while(mark==True);
	       




   for(i=0;i< Iout->Haut; i++)
     for(j=0;j< Iout->Larg;j++)
       {
	 if(Iout->Buf[i][j] == 128)
	   Iout->Buf[i][j]=0;
       }

   Iout->Bin = True;
   fprintf(stderr,"recons4connex: %d iteration(s) \n",Niter);

}




 

void CConexion(GImage *Iin, GImage* &Iout) /* L'image masque est noire avec le bord blanc (1 pixel epaisseur) n'intervient pas explicitement - implemantation plus rapide */
{
 
  int i,j;
  BOOL arret;
  int iter,Npoint;
  unsigned char  min;


  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:CConexion: image d'entree nulle !\n");
      exit(1);
    }
 
   if(Iout==NULL)
    Iout=new GImage(Iin->Larg, Iin->Haut);
   else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:CConexion: L'image d'entreee n'a pas les meme dimensions que celle de sortie !");
      exit(1);
    }
   
   /* initialisation image sortie */
   
   for(i=0;i< Iin->Haut; i++)
     {
       Iout->Buf[i][0]=Iin->Buf[i][0];
       Iout->Buf[i][Iin->Larg-1]=Iin->Buf[i][Iin->Larg-1];
     }
   for(j=0;j< Iin->Larg; j++)
     {
       Iout->Buf[0][j]=Iin->Buf[0][j];
       Iout->Buf[Iin->Haut -1][j]= Iin->Buf[Iin->Haut -1][j];
     }
  
   
   for(i=1; i< Iin->Haut-1; i++)
     for(j=1; j< Iin->Larg-1; j++)
       Iout->Buf[i][j] =255;
	

 /* end initialisation */

   iter=0;
   /* iteration avant-arriere */
   
   do
     {
       arret=True;
       Npoint=0;
       iter++;
      
       for(i=1; i< Iin->Haut-1; i++)
	 for(j=1; j< Iin->Larg-1; j++)
	   {
	     min=Iout->Buf[i-1][j-1];
	     if(Iout->Buf[i-1][j] < min)  min=Iout->Buf[i-1][j];
	     if(Iout->Buf[i-1][j+1] < min)  min=Iout->Buf[i-1][j+1];
	     if(Iout->Buf[i][j-1] < min)  min=Iout->Buf[i][j-1];
	     if(Iout->Buf[i][j] < min)  min=Iout->Buf[i][j];
	     
	     if(Iin->Buf[i][j] >= min)  
	       {
		 if(Iout->Buf[i][j] != Iin->Buf[i][j]) 
		   {
		     arret=False;
		     Npoint++;
		     Iout->Buf[i][j]=Iin->Buf[i][j];
		   }
	       }
	     else  
	       {
		 if(min != Iout->Buf[i][j])  
		   {
		     arret=False;
		     Npoint++;
		     Iout->Buf[i][j]= min;
		   }
	       }
	   }

       for(i=Iin->Haut-2; i>0; i--)
	 for(j=Iin->Larg-2; j>0; j--)
	   {
	     min=Iout->Buf[i+1][j+1];
	     if(Iout->Buf[i+1][j] < min)  min=Iout->Buf[i+1][j];
	     if(Iout->Buf[i+1][j-1] < min)  min=Iout->Buf[i+1][j-1];
	     if(Iout->Buf[i][j+1] < min)  min=Iout->Buf[i][j+1];
	     if(Iout->Buf[i][j] < min)  min=Iout->Buf[i][j];

	      if(Iin->Buf[i][j] >= min)  
	       {
		 if(Iout->Buf[i][j] != Iin->Buf[i][j]) 
		   {
		     arret=False;
		     Npoint++;
		     Iout->Buf[i][j]=Iin->Buf[i][j];
		   }
	       }
	     else  
	       {
		 if(min != Iout->Buf[i][j]) 
		   {
		     arret=False;
		     Npoint++;
		     Iout->Buf[i][j]= min;
		   }
	       }
	   }
       // fprintf(stderr,"CConexion: iteration %d Points modifie: %d\n",iter,Npoint);  
     }while(arret!=True);

   /* etape finale */

   for(i=0;i< Iin->Haut; i++)
     {
       Iout->Buf[i][0]=0;
       Iout->Buf[i][Iin->Larg-1]=0;
     }
   for(j=0;j< Iin->Larg; j++)
     {
       Iout->Buf[0][j]=0;
       Iout->Buf[Iin->Haut -1][j]= 0;
     }
   
   //fprintf(stderr,"CConexion: %d iterations allee-retour\n",iter);
}

void inversion(GImage *Iin, GImage* &Iout)
{
  int i,j;
  BOOL flag;
 
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:inversion: image d'entree nulle !\n");
      exit(1);
    }

  if(Iout==NULL)
    Iout = new GImage(Iin->Larg, Iin->Haut);
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR: inversion: Images d'entree et sortie n'ont pas les memes dimensions !\n");
      exit(1);
    }


  for(i=0;i< Iin->Haut; i++)
    for(j=0;j< Iin->Larg; j++)
      Iout->Buf[i][j] = 255 - Iin->Buf[i][j];

  flag = Iin->Bin;
  Iout->Bin = flag;

}
  
	
void Algebre(GImage *I1, GImage *I2, GImage* &Iout, char c)
{
  int i,j,temp;


   if((I1==NULL) || (I2==NULL)) 
     {
       fprintf(stderr,"ERROR: Algebre: Au moins une des images d'entree est nulle !\n");
     exit(1);
     }

    if((I2->Larg != I1->Larg) || (I2->Haut != I1->Haut))
      {
	fprintf(stderr,"ERROR: Algebre: Les images \"operandes\" n'ont pas les memes dimensions !\n");
	exit(1);
      }
   
    if(Iout==NULL)
      Iout = new GImage(I1->Larg, I1->Haut);
    else if((Iout->Larg != I1->Larg) || (Iout->Haut != I1->Haut))
      {
	fprintf(stderr,"ERROR: Algebre: Les images d'entree et sortie n'ont pas les memes dimensions !\n");
	exit(1);
      }
    
    for(i=0;i< I1->Haut; i++)
      for(j=0;j< I1->Larg; j++)
	{
	  switch(c)
	    {
	    case '&': /* and */
	      Iout->Buf[i][j] = (unsigned char)((int)I1->Buf[i][j] & (int)I2->Buf[i][j]);
	      break;
	      
	    case '|' : /* or */
	       Iout->Buf[i][j] = (unsigned char)((int)I1->Buf[i][j] | (int)I2->Buf[i][j]);
	       break;
	       
	    case  '^': /* xor */
	       Iout->Buf[i][j] = (unsigned char)((int)I1->Buf[i][j] ^ (int)I2->Buf[i][j]);
	    break;  
	    
	    case '-' :
	      if(I1->Buf[i][j] > I2->Buf[i][j])
		Iout->Buf[i][j] = (unsigned char)((int)I1->Buf[i][j] - (int)I2->Buf[i][j]);
	      else
		Iout->Buf[i][j]=0;

	    break;

	    case '+' :
	       if((temp=(int)I1->Buf[i][j] + (int)I2->Buf[i][j]) > 255)
		 Iout->Buf[i][j]= 255;
	       else
		 Iout->Buf[i][j]= temp;

	    break;    

	    
	    case 'M' :
	      if(I1->Buf[i][j] >= I2->Buf[i][j])
		Iout->Buf[i][j]=I1->Buf[i][j];
	      else
		Iout->Buf[i][j]=I2->Buf[i][j];
	      
	    break;

	     case 'm' :
	      if(I1->Buf[i][j] <= I2->Buf[i][j])
		Iout->Buf[i][j]=I1->Buf[i][j];
	      else
		Iout->Buf[i][j]=I2->Buf[i][j];
	      
	      break;



	    default:
	      fprintf(stderr,"ERROR: Algebre: \"%c\" - operation non existente !\n",c);
	      exit(1);
	      break;

	    }
	}

    if((I1->Bin==True) && (I2->Bin == True))  Iout->Bin = True;
   

}
    

void BoucheTrous(GImage *Iin, GImage* &Iout)
{
  GImage *Temp,*Mask,*Itemp;
  int i,j;

  fprintf(stderr,"BoucheTrous  en cours ...\n"); 
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:BoucheTrous: image d'entree nulle !\n");
      exit(1);
    }

  if((Iout!=NULL) && ((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut)))
       {
	 fprintf(stderr,"ERROR: BoucheTrous: Images d'entree et sortie n'ont pas les memes dimensions !\n");
	 exit(1);
       }
  if(Iin->Bin==False)
    {
       fprintf(stderr,"ERROR: BoucheTrous: Image d'entree non binaire !\n");
       exit(1);
    }

  Temp = NULL;
  Itemp=NULL;
  inversion(Iin,Temp);
  
  Mask=NULL;
  Mask= new GImage(Iin->Larg,Iin->Haut);
  
  for(i=0;i<Mask->Haut;i++)
    {
      Mask->Buf[i][0]=255;
      Mask->Buf[i][Mask->Larg-1]=255;
    }
    
    for(j=0;j<Mask->Larg; j++)
      {
	Mask->Buf[0][j]=255;
	Mask->Buf[Mask->Haut-1][j]=255;
      }

    Mask->Bin=True;
    Temp->Bin=True;
    recons(Temp,Mask,Itemp);
    inversion(Itemp,Mask);
    Algebre(Temp,Mask,Itemp,'&');
    Algebre(Itemp,Iin,Iout,'|');

    if(Mask != NULL) delete Mask;
    if(Temp != NULL)  delete Temp;
    if(Itemp != NULL)  delete Itemp;

    fprintf(stderr,"BoucheTrous  end.\n");

}
  
void BoucheTrous4C(GImage *Iin, GImage* &Iout)
{
  GImage *Temp,*Mask,*Itemp;
  int i,j;

  fprintf(stderr,"BoucheTrous4C  en cours ...\n"); 
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:BoucheTrous4C: image d'entree nulle !\n");
      exit(1);
    }

  if((Iout!=NULL) && ((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut)))
       {
	 fprintf(stderr,"ERROR: BoucheTrous4C: Images d'entree et sortie n'ont pas les memes dimensions !\n");
	 exit(1);
       }
  if(Iin->Bin==False)
    {
       fprintf(stderr,"ERROR: BoucheTrous4C: Image d'entree non binaire !\n");
       exit(1);
    }

  Temp = NULL;
  Itemp=NULL;
  inversion(Iin,Temp);
  
  Mask=NULL;
  Mask= new GImage(Iin->Larg,Iin->Haut);
  
  for(i=0;i<Mask->Haut;i++)
    {
      Mask->Buf[i][0]=255;
      Mask->Buf[i][Mask->Larg-1]=255;
    }
    
    for(j=0;j<Mask->Larg; j++)
      {
	Mask->Buf[0][j]=255;
	Mask->Buf[Mask->Haut-1][j]=255;
      }

    Mask->Bin=True;
    Temp->Bin=True;
    recons4connex(Temp,Mask,Itemp);
    inversion(Itemp,Mask);
    Algebre(Temp,Mask,Itemp,'&');
    Algebre(Itemp,Iin,Iout,'|');

    if(Mask != NULL) delete Mask;
    if(Temp != NULL)  delete Temp;
    if(Itemp != NULL)  delete Itemp;

    fprintf(stderr,"BoucheTrous4C  end.\n");

}
  
int old_etiquettage(GImage *Iin,int **buf,unsigned char val)
{
  
  int i,j,k,l, Nbconex=0;
  
  BOOL marketi,arret;
 
  int eti,Niter,Nmodif;
  int *liste;
 
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:old_etiquettage:image d'entree nulle !\n");
      exit(1);
    }

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR:old_etiquettage: buffer etiquettage nul !\n");
      exit(1);
    }

  /* etiquettage */

  /* buf=(int**)calloc(Iin->Haut,sizeof(int*));
  for(i=0;i<Iin->Haut;i++)
    buf[i]=(int*)calloc(Iin->Larg,sizeof(int));*/


  Niter=1;
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j]==val)
	  {
	    // mark=False;
	    marketi=False;
	    if(Nbconex==0)
	      {	     
		Nbconex++;
		buf[i][j]=Nbconex;
	      }
	    else
	      {
		eti=Nbconex;
		for(k = -1;k<=1;k++)
		  {
		    
		    if((i+k <0) || (i+k >=Iin->Haut)) continue;
		    else
		      {
			
			for(l=-1;l<=1;l++)
			  {
			    if((j+l<0) || (j+l >= Iin->Larg) || (2*k+l>=0)) continue;//voisinage causal
			    
			    else 
			      {
				
				//if(Iin->Buf[i+k][j+l]!=val) continue;
			
				if(buf[i+k][j+l] != 0)
				  {
				    marketi=True;
				    if(eti>buf[i+k][j+l]) eti=buf[i+k][j+l];
				  }
			      }
			  }
		      }
		  }

		
		    if(marketi==True)
		      buf[i][j]=eti;
		    else
		      {
			Nbconex++;
			buf[i][j]=Nbconex;
		      }
	
	      
	      }
	  }
	else buf[i][j]=0;
      }
  // fprintf(stderr,"Nb.particules: Nbconex apres 1-ere iter.=%d\n",Nbconex);  
 
  Nbconex=0;
  do
    {
      Niter++;
      Nmodif=0;
      arret=True;
       for(i=Iin->Haut-1;i>=0;i--)
	 for(j=Iin->Larg-1;j>=0;j--)
      
	   {
	     if(Iin->Buf[i][j]==val)
	       {
		
		 eti=buf[i][j];
		 for(k = -1;k<=1;k++)
		   {
		     
		     if((i+k <0) || (i+k >=Iin->Haut)) continue;
		     else
		       {
			 
			 for(l=-1;l<=1;l++)
			   {
			     if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)) continue;
			    
			     else 
			      {
				if((buf[i+k][j+l]< eti)&&(buf[i+k][j+l]!=0))
				  {
				    eti=buf[i+k][j+l];
				    arret=False;
				    Nmodif++;
				  }
			      }
			   }
		       }
		   }
	       
		 buf[i][j]=eti;
		 if(eti > Nbconex) Nbconex=eti;
	       }
	   }
      
       if(arret==True) break;

       arret=True;
       Nbconex=0;
       Niter++;
       Nmodif=0;
       for(i=0;i<Iin->Haut;i++)
	 for(j=0;j<Iin->Larg;j++)
      
	   {
	     if(Iin->Buf[i][j]==val)
	       {
		
		 eti=buf[i][j];
		 for(k = -1;k<=1;k++)
		   {
		     
		     if((i+k <0) || (i+k >=Iin->Haut)) continue;
		     else
		       {
			 
			 for(l=-1;l<=1;l++)
			   {
			     if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)) continue;
			    
			     else 
			      {
				if((buf[i+k][j+l]< eti)&&(buf[i+k][j+l]!=0))
				  {
				    eti=buf[i+k][j+l];
				    arret=False;
				    Nmodif++;
				  }
			      }
			   }
		       }
		   }
	       
		 buf[i][j]=eti;
		 if(eti > Nbconex) Nbconex=eti;
	       }
	   }

      
    }while(arret==False);
  
  liste=(int*)calloc(Nbconex+1,sizeof(int));
  Nbconex=0;
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if((liste[buf[i][j]]==0) && (buf[i][j]!=0))
	   {
	     Nbconex++;
	     liste[buf[i][j]]=Nbconex;
	   }
      }

   fprintf(stderr,"INFO: old_etiquettage: Nb.particules trouvees: %d\n",Nbconex);


   

   for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(buf[i][j]!=0)
	  buf[i][j]=liste[buf[i][j]];
      }

  free(liste);
  return(Nbconex);
}

 
int etiquettage(GImage *Iin,int **buf,unsigned char val)
{
  
  int i,j,k,l, Nbconex=0;
  
  BOOL marketi;
 
  int eti,Nmodif;
  int *liste;
 
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:etiquettage:image d'entree nulle !\n");
      exit(1);
    }

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR:etiquettage: buffer etiquettage nul !\n");
      exit(1);
    }

  /* etiquettage */

  /* buf=(int**)calloc(Iin->Haut,sizeof(int*));
  for(i=0;i<Iin->Haut;i++)
    buf[i]=(int*)calloc(Iin->Larg,sizeof(int));*/


 
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j]==val)
	  {
	    // mark=False;
	    marketi=False;
	    if(Nbconex==0)
	      {	     
		Nbconex++;
		buf[i][j]=Nbconex;
	      }
	    else
	      {
		eti=Nbconex;
		for(k = -1;k<=1;k++)
		  {
		    
		    if((i+k <0) || (i+k >=Iin->Haut)) continue;
		    else
		      {
			
			for(l=-1;l<=1;l++)
			  {
			    if((j+l<0) || (j+l >= Iin->Larg) || (2*k+l>=0)) continue; //voisinage causal
			    
			    else 
			      {
				
				//if(Iin->Buf[i+k][j+l]==val)
				//mark=True;
				if(buf[i+k][j+l] != 0)
				  {
				    marketi=True;
				    if(eti>buf[i+k][j+l]) eti=buf[i+k][j+l];
				  }
			      }
			  }
		      }
		  }

		
		    if(marketi==True)
		      buf[i][j]=eti;
		    else
		      {
			Nbconex++;
			buf[i][j]=Nbconex;
		      }
	
	      
	      }
	  }//if(Iin->Buf[i][j]==val)
	else buf[i][j]=0;
		      
      }
  // fprintf(stderr,"Nb.particules: Nbconex apres 1-ere iter.=%d\n",Nbconex);  
 
  liste=(int*)calloc(Nbconex+1,sizeof(int));
  for(i=0;i<=Nbconex;i++)
    liste[i]=i;
  
    
  for(i=Iin->Haut-1;i>=0;i--)
    for(j=Iin->Larg-1;j>=0;j--)
      
      {
	if(Iin->Buf[i][j]==val)
	  {
	    
	    eti=buf[i][j];
	    for(k = -1;k<=1;k++)
	      {
		
		if((i+k <0) || (i+k >=Iin->Haut)) continue;
		
		    
		for(l=-1;l<=1;l++) 
		  {
		    if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)||(buf[i+k][j+l]==0)) continue;
		    
		    
		    if(buf[i+k][j+l]< eti)
		      {
			if(liste[eti] >= liste[buf[i+k][j+l]])
			  liste[eti]=liste[buf[i+k][j+l]];
			else
			  liste[buf[i+k][j+l]]=liste[eti];
			
			eti=liste[buf[i+k][j+l]];
		      }
		    else 
		      {
			if(liste[eti] <= liste[buf[i+k][j+l]])
			  liste[buf[i+k][j+l]]=liste[eti];
			else liste[eti] = liste[buf[i+k][j+l]];
			buf[i+k][j+l]=liste[buf[i+k][j+l]];
		      }
		  }
	      }
	    
	    
	    buf[i][j]=eti;
	    
	  }
      }
  
  //do{
  //  arret=True;
    for(i=1;i<=Nbconex;i++)
      {
	if(liste[liste[i]] < liste[i])
	  {
	    //arret=False;
	    liste[i]=liste[liste[i]];
	  }
      }
    //}while(!arret);
 
  Nmodif=0;
  for(i=1;i<=Nbconex;i++)
    {
      if(liste[i]==i)
	{
	  Nmodif++;
	  liste[i]=Nmodif;
	}
      else liste[i]=liste[liste[i]];
    }

   for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	//if(buf[i][j]!=0)
	  buf[i][j]=liste[buf[i][j]];
      }

  free(liste);

  fprintf(stderr,"etiquettage: %d particules.\n",Nmodif);
  return(Nmodif);
}
 

int etiquettage_c(GImage *Iin,int** buf,unsigned char val)
{
  /* etiquettage de l'ensemble de valeurs differentes de val */
  int i,j,k,l, Nbconex=0;
  
  BOOL marketi;
 
  int eti,Nmodif;
  int *liste;
 
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:etiquettage:image d'entree nulle !\n");
      exit(1);
    }

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR:etiquettage: buffer etiquettage nul !\n");
      exit(1);
    }

  /* etiquettage */

  /* buf=(int**)calloc(Iin->Haut,sizeof(int*));
  for(i=0;i<Iin->Haut;i++)
    buf[i]=(int*)calloc(Iin->Larg,sizeof(int));*/


 
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j] != val)
	  {
	   
	    marketi=False;
	    if(Nbconex==0)
	      {	     
		Nbconex++;
		buf[i][j]=Nbconex;
	      }
	    else
	      {
		eti=Nbconex;
		for(k = -1;k<=1;k++)
		  {
		    
		    if((i+k <0) || (i+k >=Iin->Haut)) continue;
		    else
		      {
			
			for(l=-1;l<=1;l++)
			  {
			    if((j+l<0) || (j+l >= Iin->Larg) || (2*k+l>=0)) continue; //voisinage causal
			    
			    else 
			      {
				
				
				if(buf[i+k][j+l] != 0)
				  {
				    marketi=True;
				    if(eti>buf[i+k][j+l]) eti=buf[i+k][j+l];
				  }
			      }
			  }
		      }
		  }

		
		    if(marketi==True)
		      buf[i][j]=eti;
		    else
		      {
			Nbconex++;
			buf[i][j]=Nbconex;
		      }
	
	      
	      }
	  }//if(Iin->Buf[i][j]!=val)
	else buf[i][j]=0;
		      
      }
  // fprintf(stderr,"Nb.particules: Nbconex apres 1-ere iter.=%d\n",Nbconex);  
 
  liste=(int*)calloc(Nbconex+1,sizeof(int));
  for(i=0;i<=Nbconex;i++)
    liste[i]=i;
  
    
  for(i=Iin->Haut-1;i>=0;i--)
    for(j=Iin->Larg-1;j>=0;j--)
      
      {
	if(Iin->Buf[i][j] != val)
	  {
	    
	    eti=buf[i][j];
	    for(k = -1;k<=1;k++)
	      {
		
		if((i+k <0) || (i+k >=Iin->Haut)) continue;
		
		    
		for(l=-1;l<=1;l++) 
		  {
		    if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)||(buf[i+k][j+l]==0)) continue;
		    
		    
		    if(buf[i+k][j+l]< eti)
		      {
			if(liste[eti] >= liste[buf[i+k][j+l]])
			  liste[eti]=liste[buf[i+k][j+l]];
			else
			  liste[buf[i+k][j+l]]=liste[eti];
			
			eti=liste[buf[i+k][j+l]];
		      }
		    else 
		      {
			if(liste[eti] <= liste[buf[i+k][j+l]])
			  liste[buf[i+k][j+l]]=liste[eti];
			else liste[eti] = liste[buf[i+k][j+l]];
			buf[i+k][j+l]=liste[buf[i+k][j+l]];
		      }
		  }
	      }
	    
	    
	    buf[i][j]=eti;
	    
	  }
      }
  
  //do{
  //  arret=True;
    for(i=1;i<=Nbconex;i++)
      {
	if(liste[liste[i]] < liste[i])
	  {
	    //arret=False;
	    liste[i]=liste[liste[i]];
	  }
      }
    //}while(!arret);
 
  Nmodif=0;
  for(i=1;i<=Nbconex;i++)
    {
      if(liste[i]==i)
	{
	  Nmodif++;
	  liste[i]=Nmodif;
	}
      else liste[i]=liste[liste[i]];
    }

   for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	//if(buf[i][j]!=0)
	  buf[i][j]=liste[buf[i][j]];
      }

  free(liste);

  fprintf(stderr,"etiquettage_c: %d particules.\n",Nmodif);
  return(Nmodif);
}



int etiquettage_4connex(GImage *Iin,int **buf,unsigned char val)
{
  
  int i,j,k,l, Nbconex=0;
  
  BOOL marketi;
 
  int eti,Nmodif;
  int *liste;
 
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:etiquettage_4connex:image d'entree nulle !\n");
      exit(1);
    }

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR:etiquettage_4connex: buffer etiquettage nul !\n");
      exit(1);
    }

  /* etiquettage */

 
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j]==val)
	  {
	    // mark=False;
	    marketi=False;
	    if(Nbconex==0)
	      {	     
		Nbconex++;
		buf[i][j]=Nbconex;
	      }
	    else
	      {
		eti=Nbconex;
		for(k = -1;k<=1;k++)
		  {
		    
		    if((i+k <0) || (i+k >=Iin->Haut)) continue;
		    else
		      {
			
			for(l=-1;l<=1;l++)
			  {
			    if((j+l<0) || (j+l >= Iin->Larg) || (2*k+l>=0)|| (k*l != 0)) continue;//voisinage causal
			    
			    else 
			      {
				
				//if(Iin->Buf[i+k][j+l]==val)
				// mark=True;
				if(buf[i+k][j+l] != 0)
				  {
				    marketi=True;
				    if(eti>buf[i+k][j+l]) eti=buf[i+k][j+l];
				  }
			      }
			  }
		      }
		  }

		
		    if(marketi==True)
		      buf[i][j]=eti;
		    else
		      {
			Nbconex++;
			buf[i][j]=Nbconex;
		      }
	
	      
	      }
	  }
	else buf[i][j]=0;
		      
      }
  // fprintf(stderr,"Nb.particules: Nbconex apres 1-ere iter.=%d\n",Nbconex);  
 
  liste=(int*)calloc(Nbconex+1,sizeof(int));
  for(i=0;i<=Nbconex;i++)
    liste[i]=i;
  
    
  for(i=Iin->Haut-1;i>=0;i--)
    for(j=Iin->Larg-1;j>=0;j--)
      
      {
	if(Iin->Buf[i][j]==val)
	  {
	    
	    eti=buf[i][j];
	    for(k = -1;k<=1;k++)
	      {
		
		if((i+k <0) || (i+k >=Iin->Haut)) continue;
	
		
		for(l=-1;l<=1;l++)
		  {
		    if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)|| (k*l != 0)||(buf[i+k][j+l]==0)) continue;
		    
		    
		    if(buf[i+k][j+l]< eti)
		      {
			if(liste[eti] >= liste[buf[i+k][j+l]])
			  liste[eti]=liste[buf[i+k][j+l]];
			else
			  liste[buf[i+k][j+l]]=liste[eti];
			
			eti=liste[buf[i+k][j+l]];
		      }
		    else 
		      {
			if(liste[eti] <= liste[buf[i+k][j+l]])
			  liste[buf[i+k][j+l]]=liste[eti];
			else liste[eti] = liste[buf[i+k][j+l]];
			buf[i+k][j+l]=liste[buf[i+k][j+l]];
		      }
		  }
	      }
	    
	    buf[i][j]=eti;
	    
	  }
      }
  
  //do{
  //  arret=True;
    for(i=1;i<=Nbconex;i++)
      {
	if(liste[liste[i]] < liste[i])
	  {
	    //arret=False;
	    liste[i]=liste[liste[i]];
	  }
      }
    //}while(!arret);

  Nmodif=0;
  for(i=1;i<=Nbconex;i++)
    {
      if(liste[i]==i)
	{
	  Nmodif++;
	  liste[i]=Nmodif;
	}
      else liste[i]=liste[liste[i]];
    }

   for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	//if(buf[i][j]!=0)
	  buf[i][j]=liste[buf[i][j]];
      }

  free(liste);

  fprintf(stderr,"etiquettage_4connex: %d particules.\n",Nmodif);
  return(Nmodif);
}





int old_etiquettage_4connex(GImage *Iin,int **buf,unsigned char val)
{
  
  int i,j,k,l, Nbconex=0;
  
  BOOL marketi,arret;
 
  int eti,Niter,Nmodif;
  int *liste;
  
  
  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:old_etiquettage_4connex:image d'entree nulle !\n");
      exit(1);
    }

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR:old_etiquettage_4connex: buffer etiquettage nul !\n");
      exit(1);
    }

  /* etiquettage */

  /* buf=(int**)calloc(Iin->Haut,sizeof(int*));
  for(i=0;i<Iin->Haut;i++)
    buf[i]=(int*)calloc(Iin->Larg,sizeof(int));*/


  Niter=1;
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j]==val)
	  {
	    //mark=False;
	    marketi=False;
	    if(Nbconex==0)
	      {	     
		Nbconex++;
		buf[i][j]=Nbconex;
	      }
	    else
	      {
		eti=Nbconex;
		for(k = -1;k<=1;k++)
		  {
		    
		    if((i+k <0) || (i+k >=Iin->Haut)) continue;
		    else
		      {
			
			for(l=-1;l<=1;l++)
			  {
			    if((j+l<0) || (j+l >= Iin->Larg) || (2*k+l>=0)|| (k*l != 0)) continue;//voisinage causal
			    
			    else 
			      {
				
				//if(Iin->Buf[i+k][j+l]==val)
				// mark=True;
				if(buf[i+k][j+l] != 0)
				  {
				    marketi=True;
				    if(eti>buf[i+k][j+l]) eti=buf[i+k][j+l];
				  }
			      }
			  }
		      }
		  }

		
		    if(marketi==True)
		      buf[i][j]=eti;
		    else
		      {
			Nbconex++;
			buf[i][j]=Nbconex;
		      }
	
	      
	      }
	  }
	else buf[i][j]=0;
      
		      
      }
  // fprintf(stderr,"Nb.particules: Nbconex apres 1-ere iter.=%d\n",Nbconex);  
 
  Nbconex=0;
  do
    {
      Niter++;
      Nmodif=0;
      arret=True;
       for(i=Iin->Haut-1;i>=0;i--)
	 for(j=Iin->Larg-1;j>=0;j--)
      
	   {
	     if(Iin->Buf[i][j]==val)
	       {
		
		 eti=buf[i][j];
		 for(k = -1;k<=1;k++)
		   {
		     
		     if((i+k <0) || (i+k >=Iin->Haut)) continue;
		     else
		       {
			 
			 for(l=-1;l<=1;l++)
			   {
			     if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)|| (k*l != 0)) continue;
			    
			     else 
			      {
				if((buf[i+k][j+l]< eti)&&(buf[i+k][j+l]!=0))
				  {
				    eti=buf[i+k][j+l];
				    arret=False;
				    Nmodif++;
				  }
			      }
			   }
		       }
		   }
	       
		 buf[i][j]=eti;
		 if(eti > Nbconex) Nbconex=eti;
	       }
	   }
      
       if(arret==True) break;

       arret=True;
       Nbconex=0;
       Niter++;
       Nmodif=0;
       for(i=0;i<Iin->Haut;i++)
	 for(j=0;j<Iin->Larg;j++)
      
	   {
	     if(Iin->Buf[i][j]==val)
	       {
		
		 eti=buf[i][j];
		 for(k = -1;k<=1;k++)
		   {
		     
		     if((i+k <0) || (i+k >=Iin->Haut)) continue;
		     else
		       {
			 
			 for(l=-1;l<=1;l++)
			   {
			     if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)|| (k*l != 0)) continue;
			    
			     else 
			      {
				if((buf[i+k][j+l]< eti)&&(buf[i+k][j+l]!=0))
				  {
				    eti=buf[i+k][j+l];
				    arret=False;
				    Nmodif++;
				  }
			      }
			   }
		       }
		   }
	       
		 buf[i][j]=eti;
		 if(eti > Nbconex) Nbconex=eti;
	       }
	   }

      
    }while(arret==False);
  
  liste=(int*)calloc(Nbconex+1,sizeof(int));
  Nbconex=0;
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if((liste[buf[i][j]]==0) && (buf[i][j]!=0))
	   {
	     Nbconex++;
	     liste[buf[i][j]]=Nbconex;
	   }
      }

   fprintf(stderr,"INFO: old_etiquettage_4connex: Nb.particules trouvees: %d\n",Nbconex);


   

   for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(buf[i][j]!=0)
	  buf[i][j]=liste[buf[i][j]];
      }

  free(liste);
  return(Nbconex);
}


void minimum(GImage *Iin,GImage* &Iout)
{
  register int i,j,k,l;
  unsigned char temp;
  GImage *Temp=NULL;

  
   if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:min: image d'entree nulle !\n");
      exit(1);
    }

  if((Iout!=NULL) && ((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut)))
       {
	 fprintf(stderr,"ERROR: min: Images d'entree et sortie n'ont pas les memes dimensions !\n");
	 exit(1);
       }

  
  Temp = new GImage(Iin->Larg,Iin->Haut);
  
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	temp = Iin->Buf[i][j];


	for(k = -1;k<=1;k++)
	  {
	    
	    if((i+k <0) || (i+k >=Iin->Haut)) continue;
	    
	    for(l=-1;l<=1;l++)
	      {
		if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)) continue;
	       	if(temp > Iin->Buf[i+k][j+l])
		  temp = Iin->Buf[i+k][j+l];
	      }
	  }

	Temp->Buf[i][j]=temp;
      }
  
  Iout->ImageCopy(Temp);
  if(Temp != NULL) delete Temp;
}



void maximum(GImage *Iin,GImage* &Iout)
{
  register int i,j,k,l;
  unsigned char temp;
  GImage *Temp=NULL;

  
   if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:max: image d'entree nulle !\n");
      exit(1);
    }

  if((Iout!=NULL) && ((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut)))
       {
	 fprintf(stderr,"ERROR: max: Images d'entree et sortie n'ont pas les memes dimensions !\n");
	 exit(1);
       }

  
  Temp = new GImage(Iin->Larg,Iin->Haut);
  
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	temp = Iin->Buf[i][j];


	for(k = -1;k<=1;k++)
	  {
	    
	    if((i+k <0) || (i+k >=Iin->Haut)) continue;
	    
	    for(l=-1;l<=1;l++)
	      {
		if((j+l<0) || (j+l >= Iin->Larg) || (k+l+k*l==0)) continue;
	       	if(temp < Iin->Buf[i+k][j+l])
		  temp = Iin->Buf[i+k][j+l];
	      }
	  }

	Temp->Buf[i][j]=temp;
      }
  
  Iout->ImageCopy(Temp);
  if(Temp != NULL) delete Temp;
}



void particules(GImage *Iin,GImage* &Iout,unsigned char val,char *nb_keep)
{
  int **buf=NULL;
  int i,j,Nbmark,max,haut,larg,keep;
  int *liste,*index;
  BOOL arret;
  


   if(Iin==NULL)
    {
      fprintf(stderr,"ERROR: particules: image d'entree nulle !\n");
      exit(1);
    }

  

  if((buf=(int**)calloc(Iin->Haut,sizeof(int*)))==NULL)
    {
      fprintf(stderr,"ERROR: particules: allocation error !\n");
      exit(1);
    }

  for(i=0;i<Iin->Haut;i++)
    {
      if((buf[i]=(int*)calloc(Iin->Larg,sizeof(int)))==NULL)
	{
	  fprintf(stderr,"ERROR: particules: allocation error !\n");
	  exit(1);
	}
    }
  
 

  Nbmark=etiquettage(Iin,buf,val);

  

  if(Iout!=NULL)
    {
      haut=Iin->Haut;
      larg=Iin->Larg;
      delete Iout;
      Iout=NULL;
      Iout= new GImage(larg,haut);
    }
  else
    Iout= new GImage(Iin->Larg,Iin->Haut);

  if(Nbmark==0)
    {
      fprintf(stderr,"INFO: particules: 0 particules de valeur %d!\n",val);
      for(i=0;i<Iout->Haut;i++)
	free(buf[i]);
      free(buf);
      return;
    }

  if((liste=(int*)calloc(Nbmark+1,sizeof(int)))==NULL)
    {
      fprintf(stderr,"ERROR: particules: allocation error !\n");
      exit(1);
    }

   if((index=(int*)calloc(Nbmark+1,sizeof(int)))==NULL)
    {
      fprintf(stderr,"ERROR: particules: allocation error !\n");
      exit(1);
    }

  for(i=0;i<Iout->Haut;i++)
    for(j=0;j<Iout->Larg;j++)
      {
	liste[buf[i][j]]++;
      }

  /* max=0;
  for(i=1;i<=Nbmark;i++)
    if(liste[i]>max)  max=liste[i];*/

  for(i=0;i<=Nbmark;i++)
    {
      // liste[i] = (liste[i]*255)/max;
      index[i]=i;
    }
  liste[0]=0;

  /* bubble sort */

  do{
    arret=True;
    for(i=1;i<=Nbmark;i++)
      {
	if(liste[index[i]]>liste[index[i-1]])
	  {
	    arret=False;
	    max=index[i];
	    index[i]=index[i-1];
	    index[i-1]=max;
	  }
      }
  }while(!arret);
  
  /* for(i=0;i<Nbmark;i++)
    fprintf(stderr,"%d ",liste[index[i]]);*/

  if(strcmp(nb_keep,"a")==0)
    keep=Nbmark;
  else 
    {
      for(i=0;i<(int)strlen(nb_keep);i++)
	if(!isdigit(nb_keep[i]))
	  {
	    fprintf(stderr,"ERROR: particules: format errone pour le dernier champ !\n");
	    exit(1);
	  }
      keep=atoi(nb_keep);
    }

  if(keep >Nbmark) keep=Nbmark;

  if(keep <= 0)
    {
      fprintf(stderr,"ERROR: particules: format non-signifiant pour le dernier champ !\n");
      exit(1);
    }
	
  for(i=0;i<keep;i++)
    liste[index[i]] = 255*(keep-i)/keep;
  for(i=keep;i<Nbmark+1;i++)
    liste[index[i]] = 0;

  for(i=0;i<Iout->Haut;i++)
    for(j=0;j<Iout->Larg;j++)
      {
	Iout->Buf[i][j]=(unsigned char)liste[buf[i][j]];
      }
  if(keep==1)  Iout->Bin=True;

  for(i=0;i<Iout->Haut;i++)
    free(buf[i]);
  free(buf);
  free(index);
  free(liste);
  
}


void nderosioncarre(GImage *Iin, GImage* &Iout, int taille) /*renvoie True si l'image sortie est differente de zero*/
{
  int i,j,k,l,Neti;
  BOOL mark, *Valid;
  int **buf;



  if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:nderosioncarre: image d'entree nulle !\n");
      exit(1);
    }
  
  if(Iin->Bin==False)
    {
      fprintf(stderr,"ERROR:nderosioncarre: Image d'entree non binaire !"); 
      exit(1);
    }

   if(Iout==NULL)
     {
       Iout=new GImage(Iin->Larg, Iin->Haut);
       Iout->Bin=Iin->Bin;
     }
  else if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:nderosioncarre: ");
      Iin->Error(1);
      exit(1);
    }

  if((buf = (int**)calloc(Iin->Haut,sizeof(int*)))==NULL)
  {
    fprintf(stderr,"ERROR:nderosioncarre: alloc error\n");
    exit(1);
  }
  for(i=0;i<Iin->Haut;i++)
  {
    if((buf[i] = (int*)calloc(Iin->Larg,sizeof(int)))==NULL)
     {
      fprintf(stderr,"ERROR:nderosioncarre: alloc error\n");
      exit(1);
    }
  }

  Neti=etiquettage_c(Iin,buf,0);
  
  Valid = (BOOL*)calloc(Neti+1,sizeof(BOOL));
  
  for(i=0;i< Iin->Haut;i++)
    for(j=0;j<Iin->Larg; j++)
      {
	if(buf[i][j] != 0)  
	  {
	    mark=False;
	    for(k = -taille;k<=taille;k++)
	      {
	
		if((i+k <0) || (i+k >= Iin->Haut)  || (mark==True)) continue;
		else
		  {
		    
		    for(l=-taille;l<=taille;l++)
		      {
			if((j+l<0) || (j+l >= Iin->Larg) || (mark==True)) continue;
			 
			else if(Iin->Buf[i+k][j+l]==0)
			      mark=True;
			   
			  
		      }
		  }
	      }
	    if(mark==True)
	      {
		Iout->Buf[i][j]=0;
		
	      }
	    else 
	      {
		Iout->Buf[i][j]=Iin->Buf[i][j];
		
	      }
	  }
	else  Iout->Buf[i][j]=0;
      }

 free(Valid);
 for(i=0;i<Iin->Haut;i++)
   free(buf[i]);
 free(buf);
  
}

void SMDCC_Y(GImage *Iin, GImage* &Iout, int taille) /* L'image masque est donnée dans Iout; les bords de l'image ne seront pas ajoutés dans le masque*/
{
 
  int i,j,k;
  BOOL arret;
  int iter,Npoint;
  unsigned char  min,mx;
  GImage *Inc=NULL, *Ic=NULL;

  if(Iin==NULL || Iout == NULL)
    {
      fprintf(stderr,"ERROR:SMDCC_Y: image d'entree nulle !\n");
      exit(1);
    }
 
  if((Iout->Larg != Iin->Larg) || (Iout->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:SMDCC_Y: L'image d'entreee n'a pas les meme dimensions que celle de sortie !");
      exit(1);
    }
   
  if(taille < 1)
    {
      fprintf(stderr,"ERROR:SMDCC_Y: taille de l'element structurant invalide !");
      exit(1);
    }

  /* initialisation image sortie */
   
  Inc=new GImage(Iin->Larg, Iin->Haut);
  Ic=new GImage(Iin->Larg, Iin->Haut);

  for(i=0; i< Iin->Haut; i++)
    for(j=0; j< Iin->Larg; j++)
      {
	mx = 0;
	for(k=0;k<=taille;k++)
 	  {
            if((i+k >= 0)&&(i+k < Iin->Haut))
	      mx = MAX(mx,Iin->Buf[i+k][j]);
	    if((j+k >=0)&&(j+k < Iin->Larg))
	      mx = MAX(mx,Iin->Buf[i][j+k]);
       	    if((i+k >=0)&&(i+k < Iin->Haut)&&(j+k >=0)&&(j+k < Iin->Larg))
   	      mx = MAX(mx,Iin->Buf[i+k][j+k]);
	  }
	Inc->Buf[i][j] = mx;
      }

  for(i=Iin->Haut-1; i>=0 ; i--)
    for(j=Iin->Larg-1; j>=0 ; j--)
      {
	mx = 0;
	for(k=-taille;k<=0;k++)
 	  {
            if((i+k >= 0)&&(i+k < Iin->Haut))
	      mx = MAX(mx,Iin->Buf[i+k][j]);
	    if((j+k >=0)&&(j+k < Iin->Larg))
	      mx = MAX(mx,Iin->Buf[i][j+k]);
       	    if((i+k >=0)&&(i+k < Iin->Haut)&&(j+k >=0)&&(j+k < Iin->Larg))
   	      mx = MAX(mx,Iin->Buf[i+k][j+k]);
	  }
	Ic->Buf[i][j] = mx;
      }

  Algebre(Inc,Ic,Ic,'m');    //fonction contrainte

  delete Inc;
   
  for(i=0; i< Iin->Haut; i++)
    for(j=0; j< Iin->Larg; j++)
      {
	if(Iout->Buf[i][j] != 0)
	  Iout->Buf[i][j]=Iin->Buf[i][j]; //masque Y
	else
	  Iout->Buf[i][j] = Ic->Buf[i][j];
      }

  delete Ic;
  //inclusion des bords dans le masque
  /*for(i=0;i< Iin->Haut; i++)
    {
    Iout->Buf[i][0]=Iin->Buf[i][0];  
    Iout->Buf[i][Iin->Larg-1]=Iin->Buf[i][Iin->Larg-1];
    }
    for(j=0;j< Iin->Larg; j++)
    {
    Iout->Buf[0][j]=Iin->Buf[0][j];
    Iout->Buf[Iin->Haut -1][j]= Iin->Buf[Iin->Haut -1][j];
    }*/
   

  /* end initialisation */


  iter=0;
  /* iteration avant-arriere */
   
  do
    {
      arret=True;
      Npoint=0;
      iter++;
      //fprintf(stderr,"\r SMDCC_Y: iteration %d allee  ",iter);
      for(i=1; i< Iin->Haut-1; i++)
	for(j=1; j< Iin->Larg-1; j++)
	  {
	    min=Iout->Buf[i-1][j-1];
	    if(Iout->Buf[i-1][j] < min)  min=Iout->Buf[i-1][j];
	    if(Iout->Buf[i-1][j+1] < min)  min=Iout->Buf[i-1][j+1];
	    if(Iout->Buf[i][j-1] < min)  min=Iout->Buf[i][j-1];
	    if(Iout->Buf[i][j] < min)  min=Iout->Buf[i][j];
	     
	    if(Iin->Buf[i][j] >= min)  
	      {
		if(Iout->Buf[i][j] != Iin->Buf[i][j]) 
		  {
		    arret=False;
		    Npoint++;
		    Iout->Buf[i][j]=Iin->Buf[i][j];
		  }
	      }
	    else  
	      {
		if(min != Iout->Buf[i][j])  
		  {
		    arret=False;
		    Npoint++;
		    Iout->Buf[i][j]= min;
		  }
	      }
	  }
     // fprintf(stderr,"\r SMDCC_Y: iteration %d retour  ",iter);
      for(i=Iin->Haut-2; i>0; i--)
	for(j=Iin->Larg-2; j>0; j--)
	  {
	    min=Iout->Buf[i+1][j+1];
	    if(Iout->Buf[i+1][j] < min)  min=Iout->Buf[i+1][j];
	    if(Iout->Buf[i+1][j-1] < min)  min=Iout->Buf[i+1][j-1];
	    if(Iout->Buf[i][j+1] < min)  min=Iout->Buf[i][j+1];
	    if(Iout->Buf[i][j] < min)  min=Iout->Buf[i][j];

	    if(Iin->Buf[i][j] >= min)  
	      {
		if(Iout->Buf[i][j] != Iin->Buf[i][j]) 
		  {
		    arret=False;
		    Npoint++;
		    Iout->Buf[i][j]=Iin->Buf[i][j];
		  }
	      }
	    else  
	      {
		if(min != Iout->Buf[i][j]) 
		  {
		    arret=False;
		    Npoint++;
		    Iout->Buf[i][j]= min;
		  }
	      }
	  }
        
    }while(arret!=True);


  
  
 // fprintf(stderr,"\rSMDCC_Y: %d iterations allee-retour\n",iter);
}
void recons_gris(GImage *Iin, GImage * Mask, GImage* &Iout)
{
  int i,j,k,n,vi,vj;
  BOOL mark;
  int Niter=0; 
  COORD *vois=NULL;
  unsigned char mx;
   
  if((Iin==NULL) || (Mask==NULL))
    {
      fprintf(stderr,"ERROR:recons: image d'entree ou masque nulle !\n");
      exit(1);
    }

  if((Mask->Larg != Iin->Larg) || (Mask->Haut != Iin->Haut))
    {
      fprintf(stderr,"ERROR:recons_gris_dil: ");
      Iin->Error(1);
      exit(1);
    }
   
  if(Iout==NULL)
    {
      Iout=new GImage(Iin->Larg, Iin->Haut);
       
    }
  
	      
  /* pretraitement */
  if(Iout != Mask)
    Iout->ImageCopy(Mask);
   
  /* end pretraitement */

  
  vois=define_neigh();



  do
    {
      mark=False;
      Niter++;
      
      for(i=0;i< Iout->Haut; i++)
	for(j=0;j< Iout->Larg;j++)
	  {
	    mx = Iout->Buf[i][j];
	    for(n=-1;n<3;n++)
	      {
		k = (n + 8)%8;
		vi = i+vois[k].i;
		vj = j+vois[k].j;
		if((vi < 0) || (vi >= Iin->Haut) || (vj < 0) || (vj >= Iin->Larg))
		  continue;
		mx = MAX(mx,Iout->Buf[vi][vj]);
	      }
	    mx = MIN(mx,Iin->Buf[i][j]);
	    if(mx != Iout->Buf[i][j])
	      {
		Iout->Buf[i][j] = mx;
		mark = True;
	      }
	  }
	    
	  

      if(mark==False)  break;

      Niter++;

      for(i=Iout->Haut-1;i>=0; i--)
	for(j=Iout->Larg-1;j>=0;j--)
	  {
	     
	    mx = Iout->Buf[i][j];
	    for(k=3;k<=6;k++)
	      {
		 
		vi = i+vois[k].i;
		vj = j+vois[k].j;
		if((vi < 0) || (vi >= Iin->Haut) || (vj < 0) || (vj >= Iin->Larg))
		  continue;
		mx = MAX(mx,Iout->Buf[vi][vj]);
	      }
	    mx = MIN(mx,Iin->Buf[i][j]);
	    if(mx != Iout->Buf[i][j])
	      {
		Iout->Buf[i][j] = mx;
		mark = True;
	      }

	   	     
	  }
      

    }while(mark==True);
	       


  free_neigh(vois);

   
  //fprintf(stderr,"recons_gris_dil: %d demi-iteration(s) \n",Niter);

}

void open_gdisk(GImage* &Ima,int R)
{
  int i,j,Nd;
  PIXEL *p=NULL;
  PIXEL *fdisk=NULL,*ldisk=NULL;
  GImage *Tmp=NULL;
  
  unsigned char mini,maxi;



  if(Ima == NULL)
    {
      fprintf(stderr,"ERROR:open_disk:image d'entree nulle !\n");
      exit(1);
    }

  Tmp = new GImage(Ima->Larg,Ima->Haut);
  

  construct_disk(R,fdisk,ldisk,&Nd);
  if(fdisk == NULL)
    {
      fprintf(stderr,"ERROR:open_disk:erreur construction disque !\n");
      exit(1);
    }

  for(i=0;i<Ima->Haut;i++)
    for(j=0;j<Ima->Larg;j++)
      {
	mini = Ima->Buf[i][j];
	if(mini==0)
	  {
	    Tmp->Buf[i][j]= 0;
	    continue;
	  }

	p=fdisk;

	while(p != NULL)
	  {
	    if((p->i+i < 0)||(p->i+i>=Ima->Haut)||(p->j+j <0)||(p->j+j >=  Ima->Larg))
	      {
		
		p=p->suiv;
		continue;
	      }
	    mini = MIN(Ima->Buf[i+p->i][j+p->j],mini);
	      
	    p=p->suiv;
	  }
	
	Tmp->Buf[i][j]=mini;
      }

  for(i=0;i<Ima->Haut;i++)
    memset(Ima->Buf[i],0,Ima->Larg*sizeof(char));



  for(i=0;i<Ima->Haut;i++)
    for(j=0;j<Ima->Larg;j++)
      {
	maxi = Tmp->Buf[i][j];
	if(maxi==255)
	  {
	    Ima->Buf[i][j]= 255;
	    continue;
	  }

	p=fdisk;

	while(p != NULL)
	  {
	    if((p->i+i < 0)||(p->i+i>=Ima->Haut)||(p->j+j <0)||(p->j+j >=  Ima->Larg))
	      {
		
		p=p->suiv;
		continue;
	      }
	    maxi = MAX(Tmp->Buf[i+p->i][j+p->j],maxi);
	      
	    p=p->suiv;
	  }
	
	Ima->Buf[i][j]=maxi;
      }

   

  if(Tmp != NULL) delete Tmp;
  freeliste_pixel(fdisk,ldisk);
}

void close_gdisk(GImage* &Ima,int R)
{
  int i,j,Nd;
  PIXEL *p=NULL;
  PIXEL *fdisk=NULL,*ldisk=NULL;
  GImage *Tmp=NULL;
  unsigned char mini,maxi;



  if(Ima == NULL)
    {
      fprintf(stderr,"ERROR:close_disk:image d'entree nulle !\n");
      exit(1);
    }

  Tmp = new GImage(Ima->Larg,Ima->Haut);
  

  construct_disk(R,fdisk,ldisk,&Nd);
  if(fdisk == NULL)
    {
      fprintf(stderr,"ERROR:close_disk:erreur construction disque !\n");
      exit(1);
    }

  for(i=0;i<Ima->Haut;i++)
    for(j=0;j<Ima->Larg;j++)
      {
	maxi = Ima->Buf[i][j];
	if(maxi==255)
	  {
	    Tmp->Buf[i][j]= 255;
	    continue;
	  }

	p=fdisk;

	while(p != NULL)
	  {
	    if((p->i+i < 0)||(p->i+i>=Ima->Haut)||(p->j+j <0)||(p->j+j >=  Ima->Larg))
	      {
		
		p=p->suiv;
		continue;
	      }
	    maxi = MAX(Ima->Buf[i+p->i][j+p->j],maxi);
	      
	    p=p->suiv;
	  }
	
	Tmp->Buf[i][j]=maxi;
      }

  
  for(i=0;i<Ima->Haut;i++)
    memset(Ima->Buf[i],0,Ima->Larg*sizeof(char));
 
  for(i=0;i<Ima->Haut;i++)
    for(j=0;j<Ima->Larg;j++)
      {
	mini = Tmp->Buf[i][j];
	if(mini==0)
	  {
	    Ima->Buf[i][j]= 0;
	    continue;
	  }

	p=fdisk;

	while(p != NULL)
	  {
	    if((p->i+i < 0)||(p->i+i>=Ima->Haut)||(p->j+j <0)||(p->j+j >=  Ima->Larg))
	      {
		
		p=p->suiv;
		continue;
	      }
	    mini = MIN(Tmp->Buf[i+p->i][j+p->j],mini);
	      
	    p=p->suiv;
	  }
	
	Ima->Buf[i][j]=mini;
      }

   
  if(Tmp != NULL) delete Tmp;
  freeliste_pixel(fdisk,ldisk);

}

void erod_gdisk(GImage* &Ima,int R)
{
  int i,j,Nd;
  PIXEL *p=NULL;
  PIXEL *fdisk=NULL,*ldisk=NULL;
  GImage *Tmp=NULL;
  
  unsigned char mini,maxi;



  if(Ima == NULL)
    {
      fprintf(stderr,"ERROR:erod_disk:image d'entree nulle !\n");
      exit(1);
    }

  Tmp = new GImage(Ima->Larg,Ima->Haut);
  

  construct_disk(R,fdisk,ldisk,&Nd);
  if(fdisk == NULL)
    {
      fprintf(stderr,"ERROR:erod_disk:erreur construction disque !\n");
      exit(1);
    }

  for(i=0;i<Ima->Haut;i++)
    for(j=0;j<Ima->Larg;j++)
      {
	mini = Ima->Buf[i][j];
	if(mini==0)
	  {
	    Tmp->Buf[i][j]= 0;
	    continue;
	  }

	p=fdisk;

	while(p != NULL)
	  {
	    if((p->i+i < 0)||(p->i+i>=Ima->Haut)||(p->j+j <0)||(p->j+j >=  Ima->Larg))
	      {
		
		p=p->suiv;
		continue;
	      }
	    mini = MIN(Ima->Buf[i+p->i][j+p->j],mini);
	      
	    p=p->suiv;
	  }
	
	Tmp->Buf[i][j]=mini;
      }

  for(i=0;i<Ima->Haut;i++)
    memcpy(Ima->Buf[i],Tmp->Buf[i],Ima->Larg*sizeof(char));

  if(Tmp != NULL) delete Tmp;
  freeliste_pixel(fdisk,ldisk);

}


void dilat_gdisk(GImage* &Ima,int R)
{
  int i,j,Nd;
  PIXEL *p=NULL;
  PIXEL *fdisk=NULL,*ldisk=NULL;
  GImage *Tmp=NULL;
  unsigned char mini,maxi;



  if(Ima == NULL)
    {
      fprintf(stderr,"ERROR:dilat_disk:image d'entree nulle !\n");
      exit(1);
    }

  Tmp = new GImage(Ima->Larg,Ima->Haut);
  

  construct_disk(R,fdisk,ldisk,&Nd);
  if(fdisk == NULL)
    {
      fprintf(stderr,"ERROR:dilat_disk:erreur construction disque !\n");
      exit(1);
    }

  for(i=0;i<Ima->Haut;i++)
    for(j=0;j<Ima->Larg;j++)
      {
	maxi = Ima->Buf[i][j];
	if(maxi==255)
	  {
	    Tmp->Buf[i][j]= 255;
	    continue;
	  }

	p=fdisk;

	while(p != NULL)
	  {
	    if((p->i+i < 0)||(p->i+i>=Ima->Haut)||(p->j+j <0)||(p->j+j >=  Ima->Larg))
	      {
		
		p=p->suiv;
		continue;
	      }
	    maxi = MAX(Ima->Buf[i+p->i][j+p->j],maxi);
	      
	    p=p->suiv;
	  }
	
	Tmp->Buf[i][j]=maxi;
      }

  for(i=0;i<Ima->Haut;i++)
    memcpy(Ima->Buf[i],Tmp->Buf[i],Ima->Larg*sizeof(char));

  if(Tmp != NULL) delete Tmp;
  freeliste_pixel(fdisk,ldisk);

}
void construct_disk(double R,PIXEL* &f_cerc,PIXEL* &l_cerc,int *Npc)
{
  PIXEL *p=NULL,*q=NULL;
  int i,j,K;
 

  if(R < 0.0)
    {
      fprintf(stderr,"ERROR: construct_disk: rayon non-conforme r=%g !\n",R);
      exit(1);
    }

  K = (int)(R + 0.5) ;//+ 1;

  if(f_cerc != NULL)
    freeliste_pixel(f_cerc,l_cerc);
  f_cerc=NULL;l_cerc=NULL;

  

  for(i=-K;i<=K;i++)
    for(j=-K;j<=K;j++)
      {
	if((double)(i*i+j*j) <= R*R)
	  {
	    p=new PIXEL(i,j);
	    inpixel(p,f_cerc,l_cerc);
	    (*Npc)++;
	  }
      }
  
 
}

BOOL amincissement(GImage *Iin, GImage* &Iout, int taille)
// amincissement des structures \`a 255 en preservant la connexite
// les parties touchant les bords ne sont pas trait\'ees
{
  GImage *Itemp=NULL;
  int i,j,k, iter, nb4c, nb_intr,nb_intr2;
  COORD *vois;
  BOOL exist=False, black,black2;
  

  if(Iin == NULL)
    {
      fprintf(stderr,"ERROR:amincissement:image d'entree nulle !\n");
      exit(1);
    }
  if(Iin->Bin == False)
    {
      fprintf(stderr,"ERROR:amincissement:image d'entree non-binaire !\n");
      exit(1);
    }
  if(Iout == NULL)
    Iout = new GImage(Iin->Larg, Iin->Haut);
  if(Iin != Iout)
    Iout->ImageCopy(Iin);

  
  Itemp = new GImage(Iin->Larg, Iin->Haut);
  
  vois=define_neigh();

  for(iter=0;iter < taille; iter++)
    {
      
      Itemp->ImageCopy(Iout);
      
      for(i=1;i<Iin->Haut-1;i++)
	for(j=1;j<Iin->Larg-1;j++)
	  {
	    if(Itemp->Buf[i][j] != 255) continue;
	    
	    exist = True;

	    if(Itemp->Buf[i+vois[0].i][j+vois[0].j] != 255)
	      black = True;
	    else
	      black = False;

	    if(Itemp->Buf[i+vois[0].i][j+vois[0].j] < 128)
	      black2 = True;
	    else
	      black2 = False;

	    nb4c=0; nb_intr=0; nb_intr2=0;
	    for(k=1;k<9;k++)
	      {
		if((k<8)&&(k%2)&&(Itemp->Buf[i+vois[k%8].i][j+vois[k%8].j] != 0))
		  nb4c++;
		//test connexion de valeurs a 255
		if(Itemp->Buf[i+vois[k%8].i][j+vois[k%8].j] != 255)
		  {
		    if(!black) 
		      {
			nb_intr++;
			black = True;
		      }
		  }
		else if(black)
		  black=False;

		//test connexion de valeurs >= 128
		if(Itemp->Buf[i+vois[k%8].i][j+vois[k%8].j] < 128)
		  {
		    if(!black2) 
		      {
			nb_intr2++;
			black2 = True;
		      }
		  }
		else if(black2)
		  black2=False;
	      }

	    if((nb4c < 4)&&(nb_intr == 1)&&(nb_intr2 == 1))
	      {
		Itemp->Buf[i][j] = 128;
		Iout->Buf[i][j] = 0;
	      }
	  }
      if(!exist) break;
    }//for(iter ...

  free_neigh(vois);
  if(Itemp != NULL) delete Itemp;

  return(exist);

}

void granulometrie_disk(GImage *Iin, GImage* &Iout)
{
if(Iin == NULL)
    {
      fprintf(stderr,"ERROR:granulometrie_disk:image d'entree nulle !\n");
      exit(1);
    }
  if(Iin->Bin == False)
    {
      fprintf(stderr,"ERROR:granulometrie_disk:image d'entree non-binaire !\n");
      exit(1);
    }
  if(Iout != NULL)
  {
	delete Iout;
	Iout=NULL;
    Iout = new GImage(Iin->Larg, Iin->Haut);
	Iout->ImageCopy(Iin);
  }
  
 int **bdist=NULL;
 bdist = (int**)mat2Dalloc(sizeof(int),Iin->Haut,Iin->Larg);//for 2D distmap   
int i,j,n,rad;
 bool nonzero;
 GImage *Itmp=NULL;
 Itmp = new GImage(Iin->Larg, Iin->Haut);
 Itmp->ImageCopy(Iin);
 
 for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(Iout->Buf[i][j]>0)
				Iout->Buf[i][j]=1;
		}
 
 n=1;
 while(n>0)
 {
	//erosion taille n
	rad=5*n;
	distcart(Itmp,bdist,0);
	nonzero=false;
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(bdist[i][j]>rad)
			{
				Itmp->Buf[i][j]=255;
				nonzero=true;
			}
			else
				Itmp->Buf[i][j]=0;
		}
	if(!nonzero)
		break;
	//dilatation taille n
	distcart(Itmp,bdist,255);
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(bdist[i][j]<=rad)
				Itmp->Buf[i][j]=255;
			else
				Itmp->Buf[i][j]=0;
		}
		
	//mise a jour Iout
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(Itmp->Buf[i][j]>0)
				Iout->Buf[i][j]=(unsigned char)MIN(n+1,255);
		}
	n++;
 }
 
 mat2Dfree((void**&)bdist,Iin->Haut,Iin->Larg);
 delete Itmp;

}

void open_cd_disk(GImage *Iin, GImage* &Iout,int R)
{
bool nonzero;
if(Iin == NULL)
    {
      fprintf(stderr,"ERROR:open_cd_disk:image d'entree nulle !\n");
      exit(1);
    }
  if(Iin->Bin == False)
    {
      fprintf(stderr,"ERROR:open_cd_disk:image d'entree non-binaire !\n");
      exit(1);
    }
	if(Iout != Iin)
	{
	  if(Iout != NULL)
	  {
		delete Iout;
		Iout=NULL;
		Iout = new GImage(Iin->Larg, Iin->Haut);
		
	  }
	}	
  
 int **bdist=NULL;
 bdist = (int**)mat2Dalloc(sizeof(int),Iin->Haut,Iin->Larg);//for 2D distmap  
int i,j,n,rad;
 
 
	//erosion taille n
	rad=5*R;
	distcart(Iin,bdist,0);
	nonzero=false;
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(bdist[i][j]>rad)
			{
				Iout->Buf[i][j]=255;
				nonzero=true;
			}
			else
				Iout->Buf[i][j]=0;
		}
	if(nonzero)
	{	
	//dilatation taille n
	distcart(Iout,bdist,255);
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(bdist[i][j]<=rad)
				Iout->Buf[i][j]=255;
			else
				Iout->Buf[i][j]=0;
		}
		
	
	}
 
 mat2Dfree((void**&)bdist,Iin->Haut,Iin->Larg);
 

}

void close_cd_disk(GImage *Iin, GImage* &Iout,int R)
{
bool nonzero;
if(Iin == NULL)
    {
      fprintf(stderr,"ERROR:close_cd_disk:image d'entree nulle !\n");
      exit(1);
    }
  if(Iin->Bin == False)
    {
      fprintf(stderr,"ERROR:close_cd_disk:image d'entree non-binaire !\n");
      exit(1);
    }
	if(Iout != Iin)
	{
	  if(Iout != NULL)
	  {
		delete Iout;
		Iout=NULL;
		Iout = new GImage(Iin->Larg, Iin->Haut);
		
	  }
	}
   
 int **bdist=NULL;
 bdist = (int**)mat2Dalloc(sizeof(int),Iin->Haut,Iin->Larg);//for 2D distmap  
int i,j,n,rad;
 
 
	
	rad=5*R;
	
	//dilatation taille R
	nonzero=false;
	distcart(Iin,bdist,255);
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(bdist[i][j]<=rad)
			{
				Iout->Buf[i][j]=255;
				nonzero=true;
			}
			else
				Iout->Buf[i][j]=0;
		}
	if(nonzero)
	{	
	//erosion taille R
	distcart(Iout,bdist,0);
	
	for(i=0;i<Iin->Haut;i++)
		for(j=0;j<Iin->Larg;j++)
		{
			if(bdist[i][j]>rad)
			{
				Iout->Buf[i][j]=255;
				
			}
			else
				Iout->Buf[i][j]=0;
		}
	
	}
		
	
	
 
 mat2Dfree((void**&)bdist,Iin->Haut,Iin->Larg);
 

}