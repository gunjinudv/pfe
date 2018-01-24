#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "image.h" 


GImage::GImage(int larg, int haut)
{
int i,j;

Larg=larg;
Haut=haut;
Bin=False;
Associe=NULL;




 if((Buf= (unsigned char**)calloc(Haut,sizeof(unsigned char*))) == NULL)
   {
     fprintf(stderr,"ERROR:GImage:constructeur - alocation memoire !\n");
     exit(1);
   }
 for(j=0;j<Haut;j++)
   {
      if((Buf[j]= (unsigned char*)calloc(Larg,sizeof(unsigned char)))==NULL)
	 {
	   fprintf(stderr,"ERROR:GImage:constructeur - alocation memoire !\n");
	   exit(1);
	 }
   }

}

GImage::~GImage()
{
 int i;

 for(i=0;i<Haut;i++)
   free(Buf[i]);
 free(Buf);
}


void GImage::Error(int i)
{

switch(i)
  {
  case 1:
    printf("CopyError: Les images n'ont pas les memes dimensions");
    break;
  case 2:
    fprintf(stderr,"CopyError: Image source nulle !");
    break;  
  default:
    return;

}
}


void GImage::ImageCopy(GImage *Ima)
{
  int i,j;

   if(Ima==NULL)
    {
      Error(2);
      exit(1);
    }
  
  if((Larg != Ima->Larg) || (Haut != Ima->Haut))
    {
      Error(1);
      exit(1);
    }
  else
    {
     for(i=0;i<Haut;i++)
       memcpy(Buf[i],Ima->Buf[i], Larg*sizeof(unsigned char));
     Bin=Ima->Bin;
    }
}

void GImage::Init(unsigned char **buf)
{
  int i;
  
   if(buf==NULL)
    {
      Error(3);
      exit(1);
    }

   for(i=0;i<Haut;i++)
       memcpy(Buf[i],buf[i], Larg*sizeof(unsigned char));
}

void GImage::Copyto(unsigned char** &buf)
{
  int i;
  
   if(buf==NULL)
    {
      if((buf=(unsigned char**)malloc(Haut*sizeof(unsigned char*)))==NULL)
	{
	  fprintf(stderr,"GImage::Copyto: buffer destination null. Alloc error\n");
	  exit(1);
	}
      for(i=0;i<Haut;i++)
   	{
	  if((buf[i]=(unsigned char*)malloc(Larg*sizeof(unsigned char)))==NULL)
	    {
	  	fprintf(stderr,"GImage::Copyto: buffer destination null. Alloc error\n");
	  	exit(1);
	    }
	}
    }

   for(i=0;i<Haut;i++)
       memcpy(buf[i],Buf[i], Larg*sizeof(unsigned char));
}

void GImage::lecture_image_grey(FILE *ident)
{
  int i;


  for(i=0;i<this->Haut;i++)
    fread(this->Buf[i],1,(this->Larg)*sizeof(char),ident);
}


void GImage::lecture_image_grey(FILE *ident,BOX bp)
{
  int i,j;
  char *poubelle=NULL;
  
  if((poubelle=(char*)calloc(Larg+1,sizeof(char)))==NULL)
    {
      fprintf(stderr,"lecture_image_grey(FILE,BOX) : Allocation error !\n");
      exit(1);
    }

  if(bp.imin < 0)
    bp.imin = 0;
  if(bp.jmin < 0)
    bp.jmin = 0;
  if(bp.imax > Haut-1)
    bp.imax = Haut-1;
  if(bp.jmax > Larg-1)
    bp.jmax = Larg-1;

  for(i=0;i<bp.imin;i++)
    fread(poubelle,1,(Larg)*sizeof(char),ident);
  for(i=bp.imin;i<=bp.imax;i++)
    {
      if(bp.jmin > 0)
	fread(poubelle,1,(bp.jmin)*sizeof(char),ident);
      fread(Buf[i-bp.imin],1,(bp.jmax-bp.jmin+1)*sizeof(char),ident);
      
      fread(poubelle,1,(Larg-bp.jmax-1)*sizeof(char),ident);
    }

  free(poubelle);
  Haut = bp.imax-bp.imin+1;
  Larg = bp.jmax-bp.jmin+1;

 
}

void GImage::save_image_grey(FILE *ident,char** info)
{
 int i;

 fprintf(ident,"%s\n","P5");
 if(info != NULL)
   {
     for(i=0;i<4;i++)
       {
	 if(info[i][0]!='\0') fprintf(ident,"%s",info[i]);
       }
   }
 fprintf(ident,"%d %d\n",this->Larg,this->Haut);
 fprintf(ident,"%d\n",255);
 for(i=0;i<this->Haut;i++)
   fwrite(this->Buf[i],1,(this->Larg)*sizeof(char),ident); 
 
}


KImage::KImage(int larg, int haut)
{
int i,j;

Larg=larg;
Haut=haut;
Bin=False;
Associe=NULL;


 Buf= (color**)calloc(Haut,sizeof(color*));
 for(j=0;j<Haut;j++)
      Buf[j]= (color*)calloc(Larg,sizeof(color));




}

KImage::~KImage()
{
 int i;

 for(i=0;i<Haut;i++)
   free(Buf[i]);
 free(Buf);
}

void KImage::Error(int i)
{

switch(i)
  {
  case 1:
    fprintf(stderr,"CopyError: Les images n'ont pas les memes dimensions");
    break;
  case 2:
    fprintf(stderr,"CopyError: Image source nulle !");
    break;
  default:
    return;
  }
}

void KImage::ImageCopy(KImage *Ima)
{
  int i,j;

  if(Ima==NULL)
    {
      Error(2);
      exit(1);
    }
  
  if((Larg != Ima->Larg) || (Haut != Ima->Haut))
    {
      Error(1);
      exit(1);
    }
  else
    {
     for(i=0;i<Haut;i++)
       memcpy(Buf[i],Ima->Buf[i], Larg*sizeof(color));
     // for(j=0;j<Larg;j++)
     // Buf[i][j]=Ima->Buf[i][j];
    }
}

void KImage::ImageGCopy(GImage *Ima)
{
  int i,j;

   if(Ima==NULL)
    {
      Error(2);
      exit(1);
    }
  
  if((Larg != Ima->Larg) || (Haut != Ima->Haut))
    {
      Error(1);
      return;
    }
  else
    {
     for(i=0;i<Haut;i++)
	 for(j=0;j<Larg;j++)
	   {
	     Buf[i][j].r=Ima->Buf[i][j];
	     Buf[i][j].g=Ima->Buf[i][j];
	     Buf[i][j].b=Ima->Buf[i][j];
	   }

    }
}
    
void KImage::save_image_color(FILE *ident,char** info)
{
 int i;

 fprintf(ident,"%s\n","P6");
 if(info != NULL)
   {
     for(i=0;i<4;i++)
       {
	 if(info[i][0]!='\0') fprintf(ident,"%s",info[i]);
       }
   }
 fprintf(ident,"%d %d\n",this->Larg,this->Haut);
 fprintf(ident,"%d\n",255);
 for(i=0;i<this->Haut;i++)
   fwrite(this->Buf[i],1,(this->Larg)*sizeof(color),ident); 
}

void KImage::lecture_image_color(FILE *ident)
{
  int i;


  for(i=0;i<this->Haut;i++)
    fread(this->Buf[i],1,(this->Larg)*sizeof(color),ident);
}

void CopyGImage(GImage* &Iout, GImage *Iin)
{
  int i,j;
  int larg, haut;

   if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:CopyGImage: image source nulle !\n");
      exit(1);
    }

  if(Iout==NULL)  
    {
      larg=Iin->Larg;
      haut=Iin->Haut;
     
      Iout=new GImage(larg,haut);
    }
  else
    {
      if((Iin->Larg != Iout->Larg) || (Iin->Haut != Iout->Haut))
	{
	  fprintf(stderr,"ERROR:CopyImage: ");
	  Iin->Error(1);
	  exit(1);
	}
    }
  
  for(i=0;i<Iin->Haut;i++)
    memcpy(Iout->Buf[i],Iin->Buf[i], Iin->Larg*sizeof(unsigned char));
  Iout->Bin=Iin->Bin;
  

}

void CopyKImage(KImage* &Iout, KImage *Iin)
{
  int i,j;

   if(Iin==NULL)
    {
      fprintf(stderr,"ERROR:CopyKImage: image source nulle !\n");
      exit(1);
    }

 if(Iout==NULL)  
    {
      Iout=new KImage(Iin->Larg,Iin->Haut);
    }
  else
    {
       if((Iin->Larg != Iout->Larg) || (Iin->Haut != Iout->Haut))
	{
	  fprintf(stderr,"ERROR:CopyKImage: ");
	  Iin->Error(1);
	  exit(1);
	}
    }
      
  
    
  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
	 Iout->Buf[i][j]=Iin->Buf[i][j];
    
}

BOOL imageoverflow(int i,int j,int haut,int larg)
{
  BOOL ret=False;

  if( i<0 || i>=haut || j<0 || j>=larg)
    ret=True;

  return(ret);
}

BOOL imageoverflow(int i,int j,GImage *Ima)
{
  BOOL ret=False;
  
  if(Ima == NULL)
    {
      fprintf(stderr,"ERR: imageoverflow: image d'entree nulle\n");
      exit(1);
    }
  
  if( i<0 || i>=Ima->Haut || j<0 || j>=Ima->Larg)
    ret=True;

  return(ret);
}

BOOL imagediffer(GImage *Ima,GImage *Iin)
{
  BOOL ret=False;
  int i,j;
  
  if(Ima == NULL || Iin == NULL)
    {
      fprintf(stderr,"ERR: imagediffer: image(s) d'entree nulle(s)\n");
      exit(1);
    }
  if((Iin->Larg != Ima->Larg) || (Iin->Haut != Ima->Haut))
    {
      fprintf(stderr,"ERROR: imagediffer: ");
      Iin->Error(1);
      exit(1);
    }

  for(i=0;i<Iin->Haut;i++)
    for(j=0;j<Iin->Larg;j++)
      {
	if(Iin->Buf[i][j] != Ima->Buf[i][j])
	  {
	    ret = True;
	    return(ret);
	  }
      }
  
  return(ret);
}

XImage::XImage(int larg, int haut)
{
int j;

Larg=larg;
Haut=haut;





 if((Buf= (unsigned short**)calloc(Haut,sizeof(unsigned short*))) == NULL)
   {
     fprintf(stderr,"ERROR:GImage:constructeur - alocation memoire !\n");
     exit(1);
   }
 for(j=0;j<Haut;j++)
   {
      if((Buf[j]= (unsigned short*)calloc(Larg,sizeof(unsigned short)))==NULL)
	 {
	   fprintf(stderr,"ERROR:GImage:constructeur - alocation memoire !\n");
	   exit(1);
	 }
   }

}

XImage::~XImage()
{
 int i;

 for(i=0;i<Haut;i++)
   free(Buf[i]);
 free(Buf);
}

void InitCoronalMsk(unsigned char*** buf,GImage* &Iin,int i,int haut,int larg,int Ncp,GImage *Msk)
{


	if(Iin==NULL || Msk==NULL || buf ==NULL)
	{
	fprintf(stderr,"Error:InitCoronalMsk - input image(s) null(s)\n");
		exit(1);
	}

	if(Iin->Haut != Ncp || Iin->Larg != larg)
	{
		fprintf(stderr,"Error:InitCoronalMsk - dimension of input image do not correspond to a coronal view\n");
		exit(1);
	}
	if(Msk->Haut != haut || Msk->Larg != larg)
	{
		fprintf(stderr,"Error:InitCoronalMsk - dimension of mask image do not correspond to an axial view\n");
		exit(1);
	}
	if(i<0 || i>= haut)
	{
		fprintf(stderr,"Error:InitCoronalMsk - required section  %d outside image dimension\n",i);
		exit(1);
	}
    int k,j;

	for(k=0;k<Ncp;k++)
		for(j=0;j<larg;j++)
		{
			if(Msk->Buf[i][j] > 0)
				Iin->Buf[k][j] = buf[k][i][j];
			else
				Iin->Buf[k][j] = 0;
		}
		
}

void InitCoronal(unsigned char*** buf,GImage* &Iin,int i,int haut,int larg,int Ncp)
{


	if(Iin==NULL || buf ==NULL)
	{
	fprintf(stderr,"Error:InitCoronal - input image(s) null(s)\n");
		exit(1);
	}

	if(Iin->Haut != Ncp || Iin->Larg != larg)
	{
		fprintf(stderr,"Error:InitCoronal - dimension of input image do not correspond to a coronal view\n");
		exit(1);
	}
	if(i<0 || i>= haut)
	{
		fprintf(stderr,"Error:InitCoronal - required section  %d outside image dimension\n",i);
		exit(1);
	}
    int k,j;

	for(k=0;k<Ncp;k++)
		for(j=0;j<larg;j++)
		{
			
			Iin->Buf[k][j] = buf[k][i][j];
			
		}
		
}

void InitSagittalMsk(unsigned char*** buf,GImage* &Iin,int j,int haut,int larg,int Ncp,GImage *Msk)
{


	if(Iin==NULL || Msk==NULL || buf ==NULL)
	{
	fprintf(stderr,"Error:InitSagittalMsk - input image(s) null(s)\n");
		exit(1);
	}

	if(Iin->Haut != Ncp || Iin->Larg != haut)
	{
		fprintf(stderr,"Error:InitSagittalMsk - dimension of input image do not correspond to a sagittal view\n");
		exit(1);
	}
	if(Msk->Haut != haut || Msk->Larg != larg)
	{
		fprintf(stderr,"Error:InitSagittalMsk - dimension of mask image do not correspond to an axial view\n");
		exit(1);
	}
	if(j<0 || j>= larg)
	{
		fprintf(stderr,"Error:InitSagittalMsk - required section  %d outside image dimension\n",j);
		exit(1);
	}
    int k,i;

	for(k=0;k<Ncp;k++)
		for(i=0;i<haut;i++)
		{
			if(Msk->Buf[i][j] > 0)
				Iin->Buf[k][i] = buf[k][i][j];
			else
				Iin->Buf[k][i] = 0;
		}
		
}

void InitSagittal(unsigned char*** buf,GImage* &Iin,int j,int haut,int larg,int Ncp)
{


	if(Iin==NULL  || buf ==NULL)
	{
	fprintf(stderr,"Error:InitSagittalMsk - input image(s) null(s)\n");
		exit(1);
	}

	if(Iin->Haut != Ncp || Iin->Larg != haut)
	{
		fprintf(stderr,"Error:InitSagittalMsk - dimension of input image do not correspond to a coronal view\n");
		exit(1);
	}
	
	if(j<0 || j>= larg)
	{
		fprintf(stderr,"Error:InitSagittalMsk - required section  %d outside image dimension\n",j);
		exit(1);
	}
    int k,i;

	for(k=0;k<Ncp;k++)
		for(i=0;i<haut;i++)
		{
			
				Iin->Buf[k][i] = buf[k][i][j];
			
		}
		
}

void CopyCoronal(GImage* Iin,unsigned char*** &buf,int i,int haut,int larg,int Ncp)
{


	if(Iin==NULL || buf ==NULL)
	{
	fprintf(stderr,"Error:CopyCoronal - input image(s) null(s)\n");
		exit(1);
	}

	if(Iin->Haut != Ncp || Iin->Larg != larg)
	{
		fprintf(stderr,"Error:CopyCoronal - dimension of input image do not correspond to a coronal view\n");
		exit(1);
	}
	if(i<0 || i>= haut)
	{
		fprintf(stderr,"Error:CopyCoronal - required section  %d outside image dimension\n",i);
		exit(1);
	}
    int k,j;

	for(k=0;k<Ncp;k++)
		for(j=0;j<larg;j++)
		{
			
			buf[k][i][j] = Iin->Buf[k][j];
			
		}
		
}

void CopySagittal(GImage* Iin,unsigned char*** &buf,int j,int haut,int larg,int Ncp)
{


	if(Iin==NULL  || buf ==NULL)
	{
	fprintf(stderr,"Error:CopySagittal - input image(s) null(s)\n");
		exit(1);
	}

	if(Iin->Haut != Ncp || Iin->Larg != haut)
	{
		fprintf(stderr,"Error:CopySagittal - dimension of input image do not correspond to a sagittal view\n");
		exit(1);
	}
	
	if(j<0 || j>= larg)
	{
		fprintf(stderr,"Error:CopySagittal - required section  %d outside image dimension\n",j);
		exit(1);
	}
    int k,i;

	for(k=0;k<Ncp;k++)
		for(i=0;i<haut;i++)
		{
			
				buf[k][i][j] = Iin->Buf[k][i];
			
		}
		
}