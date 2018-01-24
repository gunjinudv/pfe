#include <stdlib.h>
//#include <values.h>
#include <limits.h>
#include <math.h>
#include "image.h"
#include "distcart.h"
//#include "comput.h"


CHAMFER::CHAMFER(int type)
{

  switch(type){
  case 5711: 

    nbvois = 9;
    if((posi=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    if((posj=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    if((val=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    
    
    posi[8]=0; posj[8]=0; val[8]=0;
    posi[0]=0; posj[0]=-1; val[0]=5;
    posi[4]=-1; posj[4]=2; val[4]=11;
    posi[3]=-1; posj[3]=1; val[3]=7;
    posi[2]=-1; posj[2]=0; val[2]=5;
    posi[1]=-1; posj[1]=-1; val[1]=7;
    posi[7]=-1; posj[7]=-2; val[7]=11;
    posi[5]=-2; posj[5]=1; val[5]=11;
    posi[6]=-2; posj[6]=-1; val[6]=11;

    break;
  case 34:

    nbvois = 5;
    if((posi=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    if((posj=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    if((val=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    
    posi[0]=0; posj[0]=0; val[0]=0;
    posi[1]=0; posj[1]=-1; val[1]=3;
    posi[2]=-1; posj[2]=1; val[2]=4;
    posi[3]=-1; posj[3]=0; val[3]=3;
    posi[4]=-1; posj[4]=-1; val[4]=4;

    break;

    case 11:

    nbvois = 5;
    if((posi=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    if((posj=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    if((val=(int*)calloc(nbvois,sizeof(int)))==NULL)
      {
	fprintf(stderr,"class CHAMFER: allocation error !");
	exit(1);
      }
    
    posi[0]=0; posj[0]=0; val[0]=0;
    posi[1]=0; posj[1]=-1; val[1]=1;
    posi[2]=-1; posj[2]=1; val[2]=1;
    posi[3]=-1; posj[3]=0; val[3]=1;
    posi[4]=-1; posj[4]=-1; val[4]=1;

    break;

  default:
    break;
  }
}



CHAMFER::~CHAMFER()
{
  
  free(posi);
  free(posj);
  free(val);
}


void  distcart(GImage *Iin, int** &buf,unsigned char val_obj)
{

  int i,j,k,sum,temp;
  
  CHAMFER *mask=NULL;
 

  if(Iin == NULL)
    {
      fprintf(stderr,"ERROR: distcart: Image d'entree nulle !\n");
      exit(1);
    }

  if(buf==NULL)
    {
      if((buf=(int**)calloc(Iin->Haut,sizeof(int*)))==NULL)
	{
	  fprintf(stderr,"ERROR: distcart: allocation error !\n");
	  exit(1);
	}
      for(i=0;i<Iin->Haut;i++)
	{
	  if((buf[i]=(int*)calloc(Iin->Larg,sizeof(int)))==NULL)
	    {
	      fprintf(stderr,"ERROR: distcart: allocation error !\n");
	      exit(1);
	    }
	}
    }
  
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j] != val_obj)
	  buf[i][j]= INT_MAX-20;
	else
	  buf[i][j]=0;
      }

  mask= new CHAMFER(5711);

  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(buf[i][j] == 0)  continue;
	
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< mask->nbvois-1;k++)
	  {
	    if((i+mask->posi[k] < 0) || (i+mask->posi[k] >= Iin->Haut)||(j+mask->posj[k] <0) || (j+mask->posj[k] >= Iin->Larg))  continue;
	    temp=mask->val[k]+buf[i+mask->posi[k]][j+mask->posj[k]];
	    if(temp < sum)
	      sum=temp;
	  }
	buf[i][j]=sum;
      }
  
  for(i=Iin->Haut-1;i>=0;i--)
    for(j=Iin->Larg-1;j>=0;j--)
      {
	if(buf[i][j] == 0)  continue;
	
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< mask->nbvois-1;k++)
	  {
	    if((i-mask->posi[k] < 0) || (i-mask->posi[k] >= Iin->Haut)||(j-mask->posj[k] <0) || (j-mask->posj[k] >= Iin->Larg))  continue;
	    temp=mask->val[k]+buf[i-mask->posi[k]][j-mask->posj[k]];
	    if(temp < sum)
	      sum=temp;
	  }
	buf[i][j]=sum;
      }
	       
  delete mask;
  

  
}


int**  geodistcart(GImage *Iin, int **buf_in,unsigned char val_obj)
  /* buf_in est le buffer d'etiquettage de Iin - dans une application separee l'etiquettage doit se faire dans cette procedure */
  //val_obj est la valeur de gris des points de reference pour le calcul de la distance geodesique. L'objet dans Iin est � 255 (ou valeur <> 0 et <> val_obj) sur fond noir (0); val_obj > 0 !
{

  int i,j,k,sum,temp,eti,Niter,index;
  int **buf=NULL;
  CHAMFER *mask=NULL;
  BOOL arret;
  int config[4];

  if(Iin == NULL)
    {
      fprintf(stderr,"ERROR: geodistcart: Image d'entree nulle !\n");
      exit(1);
    }
  if(buf_in == NULL)
    {
      fprintf(stderr,"ERROR: geodistcart: Buffer buf_in nul !\n");
      exit(1);
    }

  if((buf=(int**)calloc(Iin->Haut,sizeof(int*)))==NULL)
    {
      fprintf(stderr,"ERROR: geodistcart: allocation error !\n");
      exit(1);
    }
  for(i=0;i<Iin->Haut;i++)
    {
      if((buf[i]=(int*)calloc(Iin->Larg,sizeof(int)))==NULL)
	{
	  fprintf(stderr,"ERROR: geodistcart: allocation error !\n");
	  exit(1);
	}
    }
  
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j] != val_obj)
	  buf[i][j]=INT_MAX-20;
      }

  mask= new CHAMFER(5711);
  config[0]=24; config[1]=12; config[2]=6; config[3]=2;
  Niter=0;

  do{  
    arret=True;
    Niter++;
    //forward
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if((buf[i][j] == 0)||(Iin->Buf[i][j]==0))  continue;
	
	eti=buf_in[i][j];
	index=0;
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< 4;k++)
	  {
	    if((i+mask->posi[k] < 0) || (i+mask->posi[k] >= Iin->Haut)||(j+mask->posj[k] <0) || (j+mask->posj[k] >= Iin->Larg))  continue;

	    if(buf_in[i+mask->posi[k]][j+mask->posj[k]] != eti) 
	      {
		index += 1<<k;
		continue;
	      }

	    temp=mask->val[k]+buf[i+mask->posi[k]][j+mask->posj[k]];
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }
	if((j<Iin->Larg-1)&&(buf_in[i][j+1] != eti))
	  index += 16;
	// test si on prend en compte les elements "11" du mask

	for(k=4;k<8;k++)
	  {
	    if((i+mask->posi[k] < 0) || (i+mask->posi[k] >= Iin->Haut)||(j+mask->posj[k] <0) || (j+mask->posj[k] >= Iin->Larg)||(buf_in[i+mask->posi[k]][j+mask->posj[k]] != eti))  continue;

	    if((config[k-4] & index) != config[k-4])
	      {
		temp=mask->val[k]+buf[i+mask->posi[k]][j+mask->posj[k]];
		if(temp < sum)
		  {
		    sum=temp;
		    arret=False;
		  }
	      }
	  }


	buf[i][j]=sum;
      }
 
  //backward
  for(i=Iin->Haut-1;i>=0;i--)
    for(j=Iin->Larg-1;j>=0;j--)
      {
	if((buf[i][j] == 0)||(Iin->Buf[i][j]==0))  continue;
	
	eti=buf_in[i][j];
	index=0;
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< 4;k++)
	  {
	    if((i-mask->posi[k] < 0) || (i-mask->posi[k] >= Iin->Haut)||(j-mask->posj[k] <0) || (j-mask->posj[k] >= Iin->Larg))  continue;
	    if(buf_in[i-mask->posi[k]][j-mask->posj[k]] != eti)
	      {
		index += 1<<k;
		continue;
	      }

	    temp=mask->val[k]+buf[i-mask->posi[k]][j-mask->posj[k]];
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }

	if((j>0)&&(buf_in[i][j-1] != eti))
	  index += 16;
	// test si on prend en compte les elements "11" du mask

	for(k=4;k<8;k++)
	  {
	    if((i-mask->posi[k] < 0) || (i-mask->posi[k] >= Iin->Haut)||(j-mask->posj[k] <0) || (j-mask->posj[k] >= Iin->Larg)||(buf_in[i-mask->posi[k]][j-mask->posj[k]] != eti))  continue;

	    if((config[k-4] & index) != config[k-4])
	      {
		 temp=mask->val[k]+buf[i-mask->posi[k]][j-mask->posj[k]];
		 if(temp < sum)
		   {
		     sum=temp;
		     arret=False;
		   }
	      }
	  }

	buf[i][j]=sum;
      }

  }while(arret==False);     
  delete mask;
  fprintf(stderr,"INFO: geodistcart: %d iterations allee-retour \n",Niter); 

  return(buf);
}


int**  topodistcart(GImage *Iin, GImage *Imsk,unsigned char val_obj)
{

  int i,j,k,sum,temp,val;
  int **buf=NULL;
  CHAMFER *mask=NULL;
  GImage *Itop = NULL;
  int Niter;
  BOOL arret=True;

  if((Imsk == NULL) || (Iin == NULL))
    {
      fprintf(stderr,"ERROR: topodistcart: Image(s) d'entree nulle(s) !\n");
      exit(1);
    }
  if(Iin->Larg != Imsk->Larg || Iin->Haut != Imsk->Haut)
    {
      fprintf(stderr,"ERROR: topodistcart: Les image(s) d'entree n'ont pas les memes dimensions !\n");
      exit(1);
    }

  if((buf=(int**)calloc(Imsk->Haut,sizeof(int*)))==NULL)
    {
      fprintf(stderr,"ERROR: topodistcart: allocation error !\n");
      exit(1);
    }
  for(i=0;i<Imsk->Haut;i++)
    {
      if((buf[i]=(int*)calloc(Imsk->Larg,sizeof(int)))==NULL)
	{
	  fprintf(stderr,"ERROR: distcart: allocation error !\n");
	  exit(1);
	}
    }
  
  Itop = new GImage(Iin->Larg,Iin->Haut);
  
  
  for(i=0;i<Imsk->Haut;i++)
    for(j=0;j<Imsk->Larg;j++)
      {
	if(Imsk->Buf[i][j] != val_obj)
	  {
	    buf[i][j]= INT_MAX-275;
	    Itop->Buf[i][j] = Iin->Buf[i][j];
	  }
	else
	  {
	    Itop->Buf[i][j]=0;
	    buf[i][j]= 0;
	  }
      }

  mask= new CHAMFER(11);

  Niter=0;
  int ni,nj;
  val = 0;
  do{  
    arret=True;
    Niter++;
    //forward

  for(i=0;i<Imsk->Haut;i++)
    for(j=0;j<Imsk->Larg;j++)
      {
	if(buf[i][j] == 0)  continue;
	val = Itop->Buf[i][j];
	sum = buf[i][j] + mask->val[0];
	for(k=1; k< mask->nbvois;k++)
	  {
	    ni = i+mask->posi[k];
	    nj = j+mask->posj[k];
	    if((ni < 0) || (ni >= Imsk->Haut)||(nj <0) || (nj >= Imsk->Larg))  continue;
	    temp=mask->val[k]+buf[ni][nj]+ abs((int)Itop->Buf[ni][nj] - val);
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }
	buf[i][j]=sum;
      }
  //backward
  for(i=Imsk->Haut-1;i>=0;i--)
    for(j=Imsk->Larg-1;j>=0;j--)
      {
	if(buf[i][j] == 0)  continue;
	val = Itop->Buf[i][j];
	sum = buf[i][j] + mask->val[0];
	for(k=1; k< mask->nbvois;k++)
	  {
	    ni = i-mask->posi[k];
	    nj = j-mask->posj[k];
	    if((ni < 0) || (ni >= Imsk->Haut)||(nj <0) || (nj >= Imsk->Larg))  continue;
	    temp=mask->val[k]+buf[ni][nj] + abs((int)Itop->Buf[ni][nj] - val);
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }
	buf[i][j]=sum;
      }
  }while(!arret);
  
  fprintf(stderr,"INFO: topodistcart : %d iterations allee-retour.\n",Niter);

  delete mask;
  
  delete Itop;
  return(buf);
}


int**  compodistcart(GImage *Iin, int **buf_in,int **b_dist,unsigned char val_obj)
  //meme idee que geodistcart, sauf qu'il y a une composition avec les valeurs inversees de la carte de distance euclid par rapport aux bords
  // buf_in est le buffer d'etiquettage de Iin - dans une application separee l'etiquettage doit se faire dans cette procedure 
  //b_dist est la carte de dist par rapport aux bords
  //val_obj est la valeur de gris des points de reference pour le calcul de la distance geodesique. L'objet dans Iin est � 255 (ou valeur <> 0 et <> val_obj) sur fond noir (0); val_obj > 0 !
{

  int i,j,k,sum,temp,eti,Niter,index;
  int **buf=NULL;
  CHAMFER *mask=NULL;
  BOOL arret;
  int config[4];

  int maxdval;

  if(Iin == NULL)
    {
      fprintf(stderr,"ERROR: compodistcart: Image d'entree nulle !\n");
      exit(1);
    }
  if((buf_in == NULL)|| (b_dist==NULL))
    {
      fprintf(stderr,"ERROR: compodistcart: Buffer(s) input nul !\n");
      exit(1);
    }

  if((buf=(int**)calloc(Iin->Haut,sizeof(int*)))==NULL)
    {
      fprintf(stderr,"ERROR: compodistcart: allocation error !\n");
      exit(1);
    }
  for(i=0;i<Iin->Haut;i++)
    {
      if((buf[i]=(int*)calloc(Iin->Larg,sizeof(int)))==NULL)
	{
	  fprintf(stderr,"ERROR: compodistcart: allocation error !\n");
	  exit(1);
	}
    }

  //initialisation buffer sortie
  maxdval=0;
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j] != 0)
	  maxdval = max(maxdval,b_dist[i][j]);
      }
  
	  
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j] == val_obj)
	  continue;
	else if(Iin->Buf[i][j] != 0)
	  buf[i][j]= maxdval - b_dist[i][j];
	else
	  buf[i][j]=INT_MAX-20;
      }

  mask= new CHAMFER(5711);
  config[0]=24; config[1]=12; config[2]=6; config[3]=2;
  Niter=0;

  do{  
    arret=True;
    Niter++;
    //forward
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if((buf[i][j] == 0)||(Iin->Buf[i][j]==0))  continue;
	
	eti=buf_in[i][j];
	index=0;
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< 4;k++)
	  {
	    if((i+mask->posi[k] < 0) || (i+mask->posi[k] >= Iin->Haut)||(j+mask->posj[k] <0) || (j+mask->posj[k] >= Iin->Larg))  continue;

	    if(buf_in[i+mask->posi[k]][j+mask->posj[k]] != eti) 
	      {
		index += 1<<k;
		continue;
	      }

	    temp=mask->val[k]+buf[i+mask->posi[k]][j+mask->posj[k]];
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }
	if((j<Iin->Larg-1)&&(buf_in[i][j+1] != eti))
	  index += 16;
	// test si on prend en compte les elements "11" du mask

	for(k=4;k<8;k++)
	  {
	    if((i+mask->posi[k] < 0) || (i+mask->posi[k] >= Iin->Haut)||(j+mask->posj[k] <0) || (j+mask->posj[k] >= Iin->Larg)||(buf_in[i+mask->posi[k]][j+mask->posj[k]] != eti))  continue;

	    if((config[k-4] & index) != config[k-4])
	      {
		temp=mask->val[k]+buf[i+mask->posi[k]][j+mask->posj[k]];
		if(temp < sum)
		  {
		    sum=temp;
		    arret=False;
		  }
	      }
	  }


	buf[i][j]=sum;
      }
 
  //backward
  for(i=Iin->Haut-1;i>=0;i--)
    for(j=Iin->Larg-1;j>=0;j--)
      {
	if((buf[i][j] == 0)||(Iin->Buf[i][j]==0))  continue;
	
	eti=buf_in[i][j];
	index=0;
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< 4;k++)
	  {
	    if((i-mask->posi[k] < 0) || (i-mask->posi[k] >= Iin->Haut)||(j-mask->posj[k] <0) || (j-mask->posj[k] >= Iin->Larg))  continue;
	    if(buf_in[i-mask->posi[k]][j-mask->posj[k]] != eti)
	      {
		index += 1<<k;
		continue;
	      }

	    temp=mask->val[k]+buf[i-mask->posi[k]][j-mask->posj[k]];
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }

	if((j>0)&&(buf_in[i][j-1] != eti))
	  index += 16;
	// test si on prend en compte les elements "11" du mask

	for(k=4;k<8;k++)
	  {
	    if((i-mask->posi[k] < 0) || (i-mask->posi[k] >= Iin->Haut)||(j-mask->posj[k] <0) || (j-mask->posj[k] >= Iin->Larg)||(buf_in[i-mask->posi[k]][j-mask->posj[k]] != eti))  continue;

	    if((config[k-4] & index) != config[k-4])
	      {
		 temp=mask->val[k]+buf[i-mask->posi[k]][j-mask->posj[k]];
		 if(temp < sum)
		   {
		     sum=temp;
		     arret=False;
		   }
	      }
	  }

	buf[i][j]=sum;
      }

  }while(arret==False);     
  delete mask;
  fprintf(stderr,"INFO: compodistcart: %d iterations allee-retour \n",Niter); 

  return(buf);
}


int**  sumdistcart(GImage *Iin1,GImage *Iin2, unsigned char val_ref1,unsigned char val_ref2)
  //calcule la carte de distance par rapport � l'ensemble de Iin1 de valeur val_ref1 puis l'additionne � la carte de dist calcul�e par rapport � l'ensemble de Iin2 de valeur val_ref2
{

  int i,j,k,sum,temp,Niter;
  int **buf=NULL,**buf2=NULL;
  CHAMFER *mask=NULL;
  BOOL arret;

  if(Iin1 == NULL || Iin2 == NULL)
    {
      fprintf(stderr,"ERROR: sumdistcart: Image(s) d'entree nulles !\n");
      exit(1);
    }


  distcart(Iin1,buf,val_ref1);
  distcart(Iin2,buf2,val_ref2);
  
   for(i=0;i<Iin2->Haut;i++)
    for(j=0;j<Iin2->Larg;j++)
      {
	
	  buf[i][j]= min(INT_MAX-20,buf[i][j]+buf2[i][j]);
      }
   for(i=0;i<Iin2->Haut;i++)
     free(buf2[i]);
   free(buf2);

   return(buf);

  for(i=0;i<Iin2->Haut;i++)
    for(j=0;j<Iin2->Larg;j++)
      {
	if(Iin2->Buf[i][j] != val_ref2)
	  buf[i][j]= INT_MAX-20;
      }

  mask= new CHAMFER(5711);
  Niter=0;
   do{  
    arret=True;
    Niter++;

  for(i=0;i<Iin2->Haut;i++)
    for(j=0;j<Iin2->Larg;j++)
      {
	if(buf[i][j] == 0)  continue;
	
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< mask->nbvois-1;k++)
	  {
	    if((i+mask->posi[k] < 0) || (i+mask->posi[k] >= Iin2->Haut)||(j+mask->posj[k] <0) || (j+mask->posj[k] >= Iin2->Larg))  continue;
	    temp=mask->val[k]+buf[i+mask->posi[k]][j+mask->posj[k]];
	    if(temp < sum)
	      {
		sum=temp;
		arret=False;
	      }
	  }
	
	buf[i][j]=sum;
	    
	  
      }
  
  for(i=Iin2->Haut-1;i>=0;i--)
    for(j=Iin2->Larg-1;j>=0;j--)
      {
	if(buf[i][j] == 0)  continue;
	
	sum = buf[i][j] + mask->val[8];
	for(k=0; k< mask->nbvois-1;k++)
	  {
	    if((i-mask->posi[k] < 0) || (i-mask->posi[k] >= Iin2->Haut)||(j-mask->posj[k] <0) || (j-mask->posj[k] >= Iin2->Larg))  continue;
	    temp=mask->val[k]+buf[i-mask->posi[k]][j-mask->posj[k]];
	    if(temp < sum)
	      {
		 arret=False;
		 sum=temp;
	      }
	  }
	
	buf[i][j]=sum;
	   
	 
	
      }
   }while(arret==False);
	       
  delete mask;
  fprintf(stderr,"INFO: sumdistcart: %d iterations allee-retour \n",Niter); 


  return(buf);
}
