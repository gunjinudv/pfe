#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"inout.h"
#include"image.h"
#include "memalloc.h"

FILE* ouvert_fic(char *nom,char *code)

{
  FILE *ident; 


  if( ( ident = fopen(nom,code)) == NULL)
  {
	printf(" erreur ouverture fichier %s \n",nom);
        exit(1);
   }
   return(ident);
}



void lecture_ent_grey(FILE *ident,int *lar,int *hau,char** info)

{
  
  char *poubelle;
  int i,j,k;
  long pos;
  char ascii;
  BOOL flag=False;
  char* etiq[] = {
	"#Patient:",
	"#Slice_Thickness:",
	"#Slice_Location:",
	"#Pixel_Size:"};


  


  poubelle = new char [100];

  fscanf(ident,"%s",poubelle); /** lecture de P5 */

  if( ( *(poubelle) != 'P') || (*(poubelle+1) != '5')) 
  {
	printf(" format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(ident);
  i=0;
  while(1)
    {
      fscanf(ident,"%s",poubelle);
      if( *(poubelle) != '#')
	{
	  fseek(ident,pos,0);
	  break;
	}
      else 
	{
	  if(info != NULL)
	    {
	      for(j=0;j<4;j++)
		{
		  if(strcmp(poubelle,etiq[j])==0)
		    {
		      flag=True;
		      break;
		    }
		}
	    }
	   if(flag)
	    {	
	      strcpy(info[i],poubelle);
	      k=strlen(poubelle);
	    }
	   while(1)
	    {
	      fscanf(ident,"%c",&ascii);
	      if(flag)
		{
		  info[i][k]= ascii;
	          k++;
		}	
	      if(ascii=='\n')
		{
		  pos=ftell(ident);
		  if(flag) 
		    {
		      info[i][k]='\0';
		      i++;
		    }
		  flag=False; 
		  break;
		}
	    }
	}
    }

  free(poubelle);
  fscanf(ident,"%d %d",lar,hau);
  
  do{
    fscanf(ident,"%c",&ascii);
  }while(ascii!='\n');
  
  do{                               // "lecture" nombre niveau de gris
    fscanf(ident,"%c",&ascii);
  }while(ascii!='\n');
 
  //fscanf(ident,"%c%c%c",&poubelle_char,&poubelle_char,&poubelle_char);

 /* lecture du nombre de niveaux de gris*/
}  


void read_dimension(FILE *id, int *larg, int* haut)
{
  
  char *poubelle=NULL;
  
  long pos;
  char ascii;
 
  


  if((poubelle = new char [256])==NULL)
    {
      fprintf(stderr,"ERROR: read_dimension: Allocation error !\n");
      exit(1);
    }

  fscanf(id,"%s",poubelle); /** lecture de P5 */

  if( ( *(poubelle) != 'P') || (*(poubelle+1) != '5')) 
  {
	fprintf(stderr,"ERROR: read_dimension: format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(id);
  while(1)
    {
      fscanf(id,"%s",poubelle);
      if( *(poubelle) != '#')
	{
	  fseek(id,pos,0);
	  break;
	}
      else 
	{
	   
	   while(1)
	    {
	      fscanf(id,"%c",&ascii);
	      	
	      if(ascii=='\n')
		{
		  pos=ftell(id);
		   
		  break;
		}
	    }
	}
    }

  free(poubelle);
  fscanf(id,"%d %d",larg,haut);
  
  do{
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  if((*larg <= 0)||(*haut <= 0))
    {
      fprintf(stderr,"ERROR: read_dimension: dimension(s) non-conforme !\n");
      exit(1);
    }
}

BOOL read_coupe(FILE *id,int Larg,int Haut,unsigned char** &buf)
{
   char *poubelle=NULL;
  int i,larg,haut;
  long pos;
  char ascii;
 
  
  if(buf == NULL)
    {
      fprintf(stderr,"ERROR: read_coupe: Buffer coupe non-aloue !\n");
      exit(1);
    }

  if((poubelle = new char [256])==NULL)
    {
      fprintf(stderr,"ERROR: read_coupe: Allocation error !\n");
      exit(1);
    }

  fscanf(id,"%s",poubelle); /** lecture de P5 */

  if( ( *(poubelle) != 'P') || (*(poubelle+1) != '5')) 
  {
	fprintf(stderr,"ERROR: read_coupe: format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(id);
  i=0;
  while(1)
    {
      fscanf(id,"%s",poubelle);
      if( *(poubelle) != '#')
	{
	  fseek(id,pos,0);
	  break;
	}
      else 
	{
	   
	   while(1)
	    {
	      fscanf(id,"%c",&ascii);
	      	
	      if(ascii=='\n')
		{
		  pos=ftell(id);
		   
		  break;
		}
	    }
	}
    }

  free(poubelle);
  fscanf(id,"%d %d",&larg,&haut);
  
  do{
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  if((larg != Larg)||(haut != Haut))
    return(False);
  
  do{                               // "lecture" nombre niveau de gris
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  // lecture de l'image
  for(i=0;i<haut;i++)
    fread(buf[i],1,larg*sizeof(char),id);

  return(True);
  
}

void save_coupe(unsigned char **buf,int larg, int haut, char *fich)
{
  int i;
  FILE *id;

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR: save_coupe: buffer image null !\n");
      exit(1);
    }

 id = ouvert_fic(fich,"wb");
 fprintf(id,"%s\n","P5");
 
 fprintf(id,"%d %d\n",larg,haut);
 fprintf(id,"%d\n",255);
 for(i=0;i<haut;i++)
   fwrite(buf[i],1,(larg)*sizeof(char),id); 

 fclose(id);
 
}



void save_coupe(unsigned short **buf,int larg, int haut, char *fich)
{
  int i,j;
  FILE *id;

  if(buf == NULL)
    {
      fprintf(stderr,"ERROR: save_coupe: buffer image null !\n");
      exit(1);
    }
unsigned char val;
 id = ouvert_fic(fich,"wb");
 fprintf(id,"%s\n","P5");
 
 fprintf(id,"%d %d\n",larg,haut);
 fprintf(id,"%d\n",255);
 for(i=0;i<haut;i++)
	 for(j=0;j<larg;j++)
	 {
	if(buf[i][j]<256)
		val = (unsigned char)buf[i][j];
	else
	{
		val = (unsigned char)(1+buf[i][j]%255);
	}
   fwrite(&val,1,sizeof(char),id); 
 }

 fclose(id);
 
}




BOOL read_box_coupe(FILE *id,int Larg,int Haut,unsigned char **buf,BOX bp)
{
  char *poubelle=NULL;
  int i,larg,haut;
  long pos;
  char ascii;
 
  
  if(buf == NULL)
    {
      fprintf(stderr,"ERROR: read_box_coupe: Buffer coupe non-aloue !\n");
      exit(1);
    }

  if((poubelle = (char*)calloc(256,sizeof(char)))==NULL)
    {
      fprintf(stderr,"ERROR: read_box_coupe: Allocation error !\n");
      exit(1);
    }

  fscanf(id,"%s",poubelle); /** lecture de P5 */

  if( ( *(poubelle) != 'P') || (*(poubelle+1) != '5')) 
  {
	fprintf(stderr,"ERROR: read_box_coupe: format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(id);
  i=0;
  while(1)
    {
      fscanf(id,"%s",poubelle);
      if( *(poubelle) != '#')
	{
	  fseek(id,pos,0);
	  break;
	}
      else 
	{	   
	   while(1)
	    {
	      fscanf(id,"%c",&ascii);
	      	
	      if(ascii=='\n')
		{
		  pos=ftell(id);
		   
		  break;
		}
	    }
	}
    }

  free(poubelle);
  fscanf(id,"%d %d",&larg,&haut);
  
  do{
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  if((larg != Larg)||(haut != Haut))
    return(False);
  
  do{                               // "lecture" nombre niveau de gris
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  // lecture de l'image

  if((poubelle=(char*)calloc(larg+1,sizeof(char)))==NULL)
    {
      fprintf(stderr,"read_box_coupe : Allocation error !\n");
      exit(1);
    }
  for(i=0;i<bp.imin;i++)
    fread(poubelle,1,(larg)*sizeof(char),id);
  for(i=bp.imin;i<=bp.imax;i++)
    {
      if(bp.jmin > 0)
	fread(poubelle,1,(bp.jmin)*sizeof(char),id);
      fread(buf[i-bp.imin],1,(bp.jmax-bp.jmin+1)*sizeof(char),id);
      
      fread(poubelle,1,(larg-bp.jmax-1)*sizeof(char),id);
    }

  free(poubelle);

  return(True);
  
}


void InitPGM(GImage* &Ima,FILE *id,BOX bp)
{
  int i;
  char *poub;
  int larg,haut;
  long pos;
  char ascii;
  

  if(Ima != NULL)
   {
     delete Ima;
     Ima = NULL;
   }
  
  if((poub = (char*)calloc(256,sizeof(char)))==NULL)
    {
      fprintf(stderr,"ERROR: InitPGM: Allocation error !\n");
      exit(1);
    }

  fscanf(id,"%s",poub); /** lecture de P5 */

  if( ( *(poub) != 'P') || (*(poub+1) != '5')) 
  {
	fprintf(stderr,"ERROR: InitPGM: format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(id);
  i=0;
  while(1)
    {
      fscanf(id,"%s",poub);
      if( *(poub) != '#')
	{
	  fseek(id,pos,0);
	  break;
	}
      else 
	{	   
	   while(1)
	    {
	      fscanf(id,"%c",&ascii);
	      	
	      if(ascii=='\n')
		{
		  pos=ftell(id);
		   
		  break;
		}
	    }
	}
    }

  free(poub);
  fscanf(id,"%d %d",&larg,&haut);
  
  do{
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  
  
  do{                               // "lecture" nombre niveau de gris
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');

  if((bp.imin < 0)||(bp.jmin < 0)||(bp.imax >= haut)||(bp.jmax >= larg))
   {
     fprintf(stderr,"ERROR: bounding box overflow");
     exit(1);
   }
  
  Ima = new GImage(larg,haut);


  // lecture de l'image

  if((poub=(char*)calloc(larg+1,sizeof(char)))==NULL)
    {
      fprintf(stderr,"InitPGM : Allocation error !\n");
      exit(1);
    }
  for(i=0;i<bp.imin;i++)
    fread(poub,1,(larg)*sizeof(char),id);
  for(i=bp.imin;i<=bp.imax;i++)
    {
      if(bp.jmin > 0)
	fread(poub,1,(bp.jmin)*sizeof(char),id);
      fread(Ima->Buf[i-bp.imin],1,(bp.jmax-bp.jmin+1)*sizeof(char),id);
      
      fread(poub,1,(larg-bp.jmax-1)*sizeof(char),id);
    }

  free(poub);
}

void InitPGM(GImage* &Ima,FILE *id)
{
  int i;
  char *poub;
  int larg,haut; 
  long pos;
  char ascii;

  if(Ima != NULL)
   {
     delete Ima;
     Ima = NULL;
   }
  
  if((poub = (char*)calloc(256,sizeof(char)))==NULL)
    {
      fprintf(stderr,"ERROR: InitPGM: Allocation error !\n");
      exit(1);
    }

  fscanf(id,"%s",poub); /** lecture de P5 */

  if( ( *(poub) != 'P') || (*(poub+1) != '5')) 
  {
	fprintf(stderr,"ERROR: InitPGM: format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(id);
  i=0;
  while(1)
    {
      fscanf(id,"%s",poub);
      if( *(poub) != '#')
	{
	  fseek(id,pos,0);
	  break;
	}
      else 
	{	   
	   while(1)
	    {
	      fscanf(id,"%c",&ascii);
	      	
	      if(ascii=='\n')
		{
		  pos=ftell(id);
		   
		  break;
		}
	    }
	}
    }

  free(poub);
  fscanf(id,"%d %d",&larg,&haut);
  
  do{
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  
  
  do{                               // "lecture" nombre niveau de gris
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');

  
  
  Ima = new GImage(larg,haut);


  // lecture de l'image

  if((poub=(char*)calloc(larg+1,sizeof(char)))==NULL)
    {
      fprintf(stderr,"InitPGM : Allocation error !\n");
      exit(1);
    }
 
  for(i=0;i<haut;i++)
    {
      
      fread(Ima->Buf[i],1,(larg)*sizeof(char),id);
      
      
    }

  free(poub);
}

BOOL read_ROIcoupe(FILE *id,int Larg,int Haut,unsigned char** &buf,BOX bp)
{
  char *poubelle=NULL;
  int i,larg,haut;
  long pos;
  char ascii;
 
  
  if(buf == NULL)
    {
      fprintf(stderr,"ERROR: read_box_coupe: Buffer coupe non-aloue !\n");
      exit(1);
    }

  if((poubelle = (char*)calloc(256,sizeof(char)))==NULL)
    {
      fprintf(stderr,"ERROR: read_box_coupe: Allocation error !\n");
      exit(1);
    }

  fscanf(id,"%s",poubelle); /** lecture de P5 */

  if( ( *(poubelle) != 'P') || (*(poubelle+1) != '5')) 
  {
	fprintf(stderr,"ERROR: read_box_coupe: format non reconnu ( non PGM ) \n");
 	exit(1);
   }
  pos=ftell(id);
  i=0;
  while(1)
    {
      fscanf(id,"%s",poubelle);
      if( *(poubelle) != '#')
	{
	  fseek(id,pos,0);
	  break;
	}
      else 
	{	   
	   while(1)
	    {
	      fscanf(id,"%c",&ascii);
	      	
	      if(ascii=='\n')
		{
		  pos=ftell(id);
		   
		  break;
		}
	    }
	}
    }

  free(poubelle);
  fscanf(id,"%d %d",&larg,&haut);
  
  do{
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  if((larg != bp.jmax-bp.jmin+1)||(haut != bp.imax-bp.imin+1))
    return(False);
  if(bp.jmax>=Larg || bp.jmin<0 || bp.imax >=Haut || bp.imin<0)
    {
      fprintf(stderr,"ERROR: read_ROIcoupe: ROI defined outside image \n");
      exit(1);
    }
  
  do{                               // "lecture" nombre niveau de gris
    fscanf(id,"%c",&ascii);
  }while(ascii!='\n');
  
  // lecture de l'image

 //  if((poubelle=(char*)calloc(larg+1,sizeof(char)))==NULL)
//     {
//       fprintf(stderr,"read_box_coupe : Allocation error !\n");
//       exit(1);
//     }
  for(i=0;i<bp.imin;i++)
    memset(buf[i],0,(Larg)*sizeof(char));
  for(i=bp.imin;i<=bp.imax;i++)
    {
      memset(buf[i],0,(bp.jmin)*sizeof(char));
      fread((buf[i]+bp.jmin),1,(bp.jmax-bp.jmin+1)*sizeof(char),id);
      memset((buf[i]+bp.jmax),0,(Larg-bp.jmax-1)*sizeof(char));
      
    }
  for(i=bp.imax+1;i<Haut;i++)
    memset(buf[i],0,(Larg)*sizeof(char));
  //free(poubelle);

  return(True);
  
}

void save_RLE(char *nom, unsigned short int **Buf, int Larg, int Haut)
{
    int i,j,k,l;
    bool is0;
	bool changeState;
	int tempi,tempj;
	unsigned long int len;
    unsigned short int c;
	short int beg;
	FILE *ident=NULL;
	
	ident = ouvert_fic(nom,"wb");
    fprintf(ident,"%s\n","PRLE");
    fprintf(ident,"%d %d\n",Larg,Haut);
	fprintf(ident,"%d %d\n",sizeof(unsigned short int),sizeof(unsigned long int));
    //fprintf(stderr,"\nSave RLE begin... \n");

	if(Buf[0][0]==0)
    {
		beg=-1;
        fwrite(&beg,sizeof(short int),1,ident);
        is0=true;
    }
    else
    {
        beg=-2;
        fwrite(&beg,sizeof(short int),1,ident);
        is0=false;
    }

	i=0;
	j=0;
    k=0;
	l=0;
	changeState=false;

    for(i=0;i<Haut;i++)
    {
        for(j=0;j<Larg;j++)
        {
            if(is0)
            {
                if(Buf[i][j]!=0)
                {
                    len=(i-l)*Larg+j-k;
					//fprintf(stderr,"SaveRLE val=0 (%d,%d)->(%d,%d) : length= %d \n",l,k,i,j,len);
                    fwrite(&len,sizeof(unsigned long int),1,ident);
                    k=j;
					l=i;
                    changeState=true;
                }
            }
            else
            {
                if(Buf[i][j]==0)
                {
                    //fprintf(stderr," Save RLE 1...i= %d j= %d ",i,j);
                    len=(i-l)*Larg+j-k;
					//fprintf(stderr,"SaveRLE val!=0 (%d,%d)->(%d,%d) : length= %d \n",l,k,i,j,len);
                    fwrite(&len,sizeof(unsigned long int),1,ident);
					tempi=l;
					tempj=k;
                    for(unsigned int z=0;z<len;z++)
                    {
						c=Buf[tempi][tempj];
						//fprintf(stderr,"SaveRLE (%d,%d) = %d \n",i,z,c);
                        fwrite(&c,sizeof(unsigned short int),1,ident);
						tempj++;
						if(tempj==Larg)
						{
							tempj=0;
							tempi++;
						}
                    }
                    k=j;
					l=i;
                    changeState=true;
                }
            }
			if(changeState)
			{
				changeState=false;
				if(is0)
					is0=false;
				else
					is0=true;
			}
        }
    }
    if(is0)
    {
        len=(i-l-1)*Larg+j-k;
		//fprintf(stderr,"SaveRLE val=0 (%d,%d)->(%d,%d) : length= %d \n",l,k,i,j,len);
        fwrite(&len,sizeof(unsigned long int),1,ident);
    }
    else
    {
        len=(i-l-1)*Larg+j-k;
		//fprintf(stderr,"SaveRLE val!=0 (%d,%d)->(%d,%d) : length= %d \n",l,k,i,j,len);
        fwrite(&len,sizeof(unsigned long int),1,ident);
		tempi=l;
		tempj=k;
        for(unsigned int z=0;z<len;z++)
        {
			c=Buf[tempi][tempj];
			//fprintf(stderr,"SaveRLE (%d,%d) = %d \n",i,z,c);
            fwrite(&c,sizeof(unsigned short int),1,ident);
			tempj++;
			if(tempj==Larg)
			{
				tempj=0;
				tempi++;
			}
        }
    }
    //fprintf(stderr," Save RLE end... \n");
    fclose(ident);
}

void lecture_RLE(char *path, unsigned short int** &Buff,int Larg, int Haut)
{
    FILE *id = fopen(path,"rb");
	if(id==NULL)
	{
		fprintf(stderr,"RLE: ERROR unable to open file\n");
		exit(1);
	}
    int i,j;
    short int beg;
	unsigned long int len;
    bool is0=false;
    char line[500];
	double sizeShort;
	double sizeLong;
    fgets(line,500,id);
    if(strcmp(line,"PRLE\n"))
    {
        fprintf(stderr,"RLE: L'image n'est pas au format RLE\n");
    }
    else
    {
		///****** largeur hauteur ******
        line[0]='\0';
        fgets(line,500,id);
        char *buffer = strdup (line);
        char *tok1 = strtok( buffer, " " );
        int Larg=atoi(tok1);
        char *tok2 = strtok( NULL, " " );
        int Haut=atoi(tok2);

		//******* size of shorts size of longs ******
		fgets(line,500,id);
        char *buffer2 = strdup (line);
        char *tok3 = strtok( buffer2, " " );
        sizeShort=atoi(tok3);
        char *tok4 = strtok( NULL, " " );
        sizeLong=atoi(tok4);

        if(Buff==NULL)
        {
            Buff = (unsigned short int**)mat2Dalloc(sizeof(unsigned short int),Haut,Larg);
        }

		if(sizeShort!=sizeof(unsigned short int) || sizeLong!=sizeof(unsigned long int))
		{
			fprintf(stderr,"RLE: ERROR -- image created by a diffrent bits system... RLE\n");
			return;
		}

		//fprintf(stderr,"\nRead RLE begin... \n");
        unsigned short int tmp;
        i=0;
        j=0;
        line[0]='\0';
		fread(&beg,sizeof(short int),1,id);
        if(beg==-1)
        {
            is0=true;
        }
        else if(beg==-2)
        {
            is0=false;
        }
        while(!feof(id))
        {
			if(i==Haut)
			{
				break;
			}
			fread(&len,sizeof(unsigned long int),1,id);
			if(is0)
			{
				//fprintf(stderr,"ReadRLE val=0 (%d,%d) length= %d \n",i,j,len);
				for(int l=0;l<len;l++)
				{
					if(i==Haut)
					{
						//fprintf(stderr,"ReadRLE reaching limit\n");
						break;
					}
					Buff[i][j]=0;
					j++;
					if(j==Larg)
					{
						i++;
						j=0;
					}
				}
			}
			else
			{
				//fprintf(stderr,"ReadRLE val!=0 (%d,%d) length= %d \t|",i,j,len);
				for(int l=0;l<len;l++)
				{
					if(i==Haut)
					{
						//fprintf(stderr,"ReadRLE reaching limit\n");
						break;
					}
					fread(&tmp,sizeof(unsigned short int),1,id);
					//fprintf(stderr,"%d|",tmp);
					Buff[i][j]=tmp;
					j++;
					if(j==Larg)
					{
						i++;
						j=0;
					}
				}
				//fprintf(stderr,"\n");
			}
			is0=!is0;
		}
    }
    fclose(id);
	//fprintf(stderr,"Read RLE end... \n");
}
