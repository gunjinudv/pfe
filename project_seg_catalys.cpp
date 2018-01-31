#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "image.h"
#include "inout.h"
#include "voxel.h"

#include "lissage.h"
#include "coordinates.h"
#include "memalloc.h"

#include "distcart.h"
#include "morpho.h"
#include "3dmorpho.h"


double PSZ;
double ZSZ;
unsigned int THD;
char PM;

int Nsv; //slice nb for debug/display


double r_cyl=34.0, l_cyl=33.0;
double r_gt=8;//rayon pixels gros trou
double r_ext=30;

void printcmd()
{

    fprintf(stderr,"  project_seg_catalys sequence####.pgm start=nr_start end=nr_end step=step_value  [-isotropic] [-resol:psize,zsize] [-save_valid_points]  [-smooth3D:radius,sigma] [-display_temp:image_number] [-save_gray] [[-save_color] [-overlay]] [-file_position:fichier.txt]\n\n");
    fprintf(stderr," Outputs a color series with cylinder axis superimposed on original images\n");
    fprintf(stderr,"  -display_temp: requires the image number (original format) for which intermediary results will be displayed\n");
    fprintf(stderr,"  -save_color: saves the color-coded result as axial images; if the option -overlay is on, the result is superimposed on the original gray values of the images\n\n");
}

void parcours_objet(VOXEL* voxarg, int connex, unsigned char*** &buf, int greyin, int greyout, int Larg, int Haut, int Nbcoupe, COORDINATES* &coordinates) {

    VOXEL *fin=NULL, *lin=NULL, *fout=NULL, *lout=NULL, *ftrou=NULL, *ltrou=NULL;
    int i, j, k, n;
    int N=0;
    VOXEL *vox=NULL, *vox2=NULL, *vox3=NULL;
    COORDINATES *coordinates1 = NULL;

    vox = new VOXEL(voxarg->i,voxarg->j, voxarg->k, voxarg->eti);
    assert(vox);
    invoxel(vox,fin,lin);
    double maxdir[3];

    VOIS *ng=NULL;
    ng = new VOIS(connex);

    while(fin!=NULL) {
        vox = fin;

        while (vox!=NULL) {
            for(n=0; n<ng->Nbvois;n++) {
                i = vox->i+ng->crd[n].i;
                j = vox->j+ng->crd[n].j;
                k = vox->k+ng->crd[n].k;
                if (i>=0 && i<Haut && j>=0 && j<Larg && k>=0 && k<Nbcoupe && buf[k][i][j]==greyin) {
                    buf[k][i][j] = greyout;
                    vox2 = new VOXEL(i,j,k,0);
                    assert(vox2);
                    vox3 = new VOXEL(i,j,k,0);
                    assert(vox3);
                    invoxel(vox2,fout,lout);
                    invoxel(vox3,ftrou,ltrou);
                    N++;
                    vox2 = NULL; vox3 = NULL;
                }
            }
            vox=vox->suiv;
        } //while vox!=NULL
        freelistevoxel(fin,lin);

        fin = fout; fout = NULL;
        lin = lout; lout = NULL;
    } //while fin!=NULL

    //calcul des composantes principales
    double** mat_vp=NULL;
    double* val_pr=NULL;
    double moyx=0, moyy=0, moyz=0;
    prin_comp_analisys(ftrou,mat_vp,val_pr,moyx,moyy,moyz);
    i=getMaxPos(val_pr,3);
    maxdir[0]=mat_vp[0][i];
    maxdir[1]=mat_vp[1][i];
    maxdir[2]=mat_vp[2][i];
    coordinates = new COORDINATES(moyx,moyy,moyz,val_pr[i],maxdir,N);
    //fin calcul composantes

    freelistevoxel(ftrou,ltrou);
    ftrou = NULL;
    ltrou = NULL;

}

int  main(int argc,char *argv[])
{


    VOXEL *vox=NULL,*fseed=NULL,*lseed=NULL;
    int eti;
    char  *endptr;
    char **info=NULL,**endpt=NULL;
    char pub[500], fawaxis[512],boxaxis[256];
    FILE *id;
    int i,j,k;
    int repr;
    int X,Y,npm,taille;
    int seuil;
    //int sw;
    int Larg,Haut,ILarg,IHaut,Nbcoupe,start,end,step,Nsize;
    char *format=NULL, *nom=NULL;
    char *base=NULL, *ext=NULL, *path=NULL;
    char *formatcal=NULL;
    char *basecal=NULL, *extcal=NULL;
    int reprcal=0;
    unsigned char ***buf0=NULL, ***buf1=NULL;
    //DIR *dirp;
    //struct dirent *direntp;
    BOOL flag_exist=False, lowpass=False;
    VOXEL *seed=NULL;
    GImage *Iref=NULL,*Ima=NULL,*Imsk=NULL,*Inb=NULL;
    BOX bp1,bpcal,btrach;
    BOX3D b3x,baw;
    double *Histo;
    double rad;
    VOIS *nhd=NULL;
    VOXEL **fvs=NULL, **lvs=NULL;
    GImage *Iin=NULL, *Iout=NULL;
    double psize=1.0, zsize=1.0;
    //BOOL isclosing = False, isfdir=False, isdetectpoum=False, forcetrachea = False;
    bool issave=false, remtopbot=false, elimcnxwall=false,isawaxis=false,isboxaxis=false,iscolorcalib=false,isawcal=false,isoverlay=false;
    bool clean_valid=false;
    char chval[500];
    char filepos[256];
    unsigned char LTHD=100; //valeur hautes densites parenchyme pulmonaire
    bool keepcnxtrah=false;
    //test arguments ligne de commande. Vous pouvez ajouter d'autres options du type -save_axial_temp
    char seqcal[256];
    Data vol;
    double sig2D=0.1, sig3D=0.1;
    int rad2D=1,rad3D=1;
    bool  smooth3D=false;
    int imanb=-1;
    int  WTmax=100;
    bool save_color=false;
    bool isotropic=false;
    bool isresol=false;
    char psval[200],zsval[200];
    bool save_valid=false;
    bool isdtmp=false;

    if(argc < 5)
    {

        fprintf(stderr," Erreur argument ! Usage : \n");
        printcmd();
        exit(1);

    }

    //BOOL isboxseuil=False;
    bool ispostrah=false;
    if(argc > 5)
    {
        for(i=5;i<argc;i++)
        {
            if(!strcmp(argv[i],"-save_gray"))
                issave = True;
            else if(!strcmp(argv[i],"-save_color"))
                save_color=true;
            else if(!strcmp(argv[i],"-overlay"))
                isoverlay=true;
            else if(!strcmp(argv[i],"-isotropic"))
                isotropic=true;
            else if(!strcmp(argv[i],"-save_valid_points"))
                save_valid=true;

            else if(!strncmp(argv[i],"-resol:",7))
            {
                isresol = true;
                psval[0]='\0';
                zsval[0]='\0';
                //strcpy(psval,argv[i]);


                endptr = strchr((argv[i]+7),',');
                if(endptr == NULL)
                {
                    fprintf(stderr,"-resol: error specifying parameters pixel_size, z_size: %d fields read\nargv[i] = %s\npsval=%s,zsval=%s.",i,argv[i],psval,zsval);

                    exit(1);
                }
                strncpy(psval,(argv[i]+7),endptr-argv[i]-7);
                psval[endptr-argv[i]-7]='\0';
                strcpy(zsval,endptr+1);
                fprintf(stderr,"psval=%s,zsval=%s\n",psval,zsval);

                psize = strtod(psval,endpt);
                zsize = strtod(zsval,endpt);

            }

            else if(!strncmp(argv[i],"-display_temp:",14))
            {
                isdtmp=true;
                imanb = atoi(argv[i]+14);
                fprintf(stderr,"Reference image for display %d\n",imanb);
            }

            else if(!strncmp(argv[i],"-smooth3D:",10))
            {
                if(sscanf(argv[i],"-smooth3D:%d,%s",&rad3D,pub)!=2)
                {
                    fprintf(stderr,"-smooth3D: error specifying parameters radius, sigma\n");
                    fprintf(stderr,"\nUsage: -smooth3D:radius(int),sigma(double)\n");
                    exit(1);
                }
                sig3D = strtod(pub,endpt);
                smooth3D=true;
            }

            else
            {
                fprintf(stderr,"Option %s inconnue \n!",argv[i]);
                printcmd();


                exit(1);
            }
        }
    }

/*  if(!strncmp(argv[5],"-file_position:",15))
	    {
	      
	      
	      strcpy(filepos,argv[5]+15);
	    }
	  else 
		{
			fprintf(stderr,"Erreur syntaxe argument \"-file_position:\" -> %s \n!",argv[5]);
	      printcmd();
	      
	
	      exit(1);
	    }
		*/
    //verification de l'existence des fichiers

    if((format=(char*)calloc(256,sizeof(char)))==NULL)
    {
        fprintf(stderr,"ERROR: main: Allocation error\n");
        exit(1);
    }

    if((base=(char*)calloc(256,sizeof(char)))==NULL)
    {
        fprintf(stderr,"ERROR: main: Allocation error\n");
        exit(1);
    }

    if((ext=(char*)calloc(256,sizeof(char)))==NULL)
    {
        fprintf(stderr,"ERROR: main: Allocation error\n");
        exit(1);
    }


    //detection parametres serie images

    endptr = strchr(argv[1],'#');
    if(endptr == NULL)
    {
        fprintf(stderr,"Nom de sequence errone ! Usage :\n");
        printcmd();

        exit(1);
    }
    strncpy(base,argv[1],endptr-argv[1]);
    base[endptr-argv[1]]='\0';
    repr=0;
    while(*(endptr+repr)=='#')
    {
        repr++;
    }

    sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%c",'\0');

    strcpy(ext,(endptr+repr));

    if(strncmp(argv[2],"start=",6))
    {
        fprintf(stderr,"Deuxieme argument errone ! Usage :\n");
        printcmd();

        exit(1);
    }
    else
    {
        start = atoi(argv[2]+6);
    }

    if(strncmp(argv[3],"end=",4))
    {
        fprintf(stderr,"Troisieme argument errone ! Usage :\n");
        printcmd();

        exit(1);
    }
    else
    {
        end = atoi(argv[3]+4);
    }

    if(strncmp(argv[4],"step=",5))
    {
        fprintf(stderr,"Quatrieme argument errone ! Usage :\n");
        printcmd();

        exit(1);
    }
    else
    {
        step = atoi(argv[4]+5);
    }


    Nbcoupe = (end - start)/step +1;//nombre d'images dans la sequence



    if((nom=(char*)calloc(512,sizeof(char)))==NULL)
    {
        fprintf(stderr,"ERROR: main: Allocation error )\n");
        exit(1);
    }
    char *nbase=NULL;
    /*if((nbase=(char*)calloc(256,sizeof(char)))==NULL)
      {
        fprintf(stderr,"ERROR: main: Allocation error\n");
        exit(1);
      }*/

    endptr = strrchr(base,'/');
    if(endptr != NULL)
    {
        if((path=(char*)calloc(256,sizeof(char)))==NULL)
        {
            fprintf(stderr,"ERROR: main: Allocation error )\n");
            exit(1);
        }
        strncpy(path,base,endptr-base);
        path[endptr-base]='\0';
        strcpy(base,(endptr+1));
    }


    // free(nbase);

    time_t maintenant;
    time(&maintenant);
    pub[0]='\0';
    sprintf(pub,"report_file_seg_cyl_%s.txt%c",base,'\0');
    id = ouvert_fic(pub,"w");
    for(i=0;i<argc;i++)
        fprintf(id,"%s ",argv[i]);
    fprintf(id,"\nstart:\n");
    fprintf(id,"%s\n",ctime(&maintenant));
    fclose(id);



    //lecture info taille pixel dans le header image

    if(path == NULL)
        sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%c",'\0');
    else
        sprintf(format,"%s/%s%d%s%c",path,"%s%0",repr,"d%s%c",'\0');

    sprintf(nom,format,base,start,ext,'\0');

    info = (char**)calloc(4,sizeof(char*));
    for(i=0;i<4;i++)
        info[i] = (char*)calloc(500,sizeof(char));

    for(i=0;i<4;i++)
        info[i][0]='\0';


    id = ouvert_fic(nom,"rb");
    lecture_ent_grey(id,&ILarg,&IHaut,info);


    fclose(id);
    //pixel-size and voxel size

    if(!isresol)
    {

        if(info != NULL && info[3][0] != '\0')
        {

            if(sscanf(info[3],"#Pixel_Size:%s",pub)!= 1)
            {
                fprintf(stderr,"Error detecting pixel size from original pgm images ! Exit\n");
                exit(1);
                //psize = zsize;
            }
            else
            {
                fprintf(stderr,"%s %s\n",info[3],pub);
                psize = strtod(pub,endpt);
            }
            for(i=0;i<4;i++)
                free(info[i]);
            free(info);
            info = NULL;
        }
        else
        {
            fprintf(stderr,"Error detecting pixel size from original pgm images ! Exit\n");
            exit(1);
            // psize = zsize;
        }

        if(!isotropic)
        {
            zsize = (double)step;
            for(i=0;i<repr-3;i++)
                zsize /= 10.0;

        }
        else
            zsize =psize;


    }//if(!isresol)
    else
    {
        if(psval==zsval)
            isotropic=true;
    }



    ZSZ = zsize;//variable externe a passer dans les autres procedures

    PSZ = psize;//variable externe a passer dans les autres procedures

    fprintf(stderr,"PSZ=%g ZSZ=%g\n",PSZ,ZSZ);

    vol.res_x=psize;
    vol.res_y=psize;
    vol.res_z=zsize;

    //possibilite de definition d'une ROI et de charger que l'interieur
    bp1.imin=0;
    bp1.imax=IHaut-1;
    bp1.jmin = 0;
    bp1.jmax=ILarg-1;




    //fprintf(stderr,"imin1=%d imax1=%d jmin1=%d jmax1=%d\n",bp1.imin, bp1.imax, bp1.jmin,bp1.jmax);

    Larg=bp1.jmax-bp1.jmin+1;
    Haut=bp1.imax-bp1.imin+1;


    fprintf(stderr,"Dimension volume: Larg=%d Haut=%d Nbcps=%d\n",Larg,Haut,Nbcoupe);

    //ecriture du fichier "box.dat"
    id = ouvert_fic("box_seg.dat","w");
    fprintf(id,"%s %s\n","Sequence:",base);
    fprintf(id,"imin=%d\n",bp1.imin);
    fprintf(id,"imax=%d\n",bp1.imax);
    fprintf(id,"jmin=%d\n",bp1.jmin);
    fprintf(id,"jmax=%d\n",bp1.jmax);
    fprintf(id,"start=%d\n",start);
    fprintf(id,"end=%d\n",end);
    fprintf(id,"step=%d\n",step);
    fprintf(id,"pixel_size(mm)=%g\n",psize);
    fprintf(id,"z_size(mm)=%g\n",zsize);

    fclose(id);



    fprintf(stderr,"Volume allocation needs %.2f kbytes of memory. \n",2.0*(double)(Larg*Haut*(Nbcoupe+2))/1024.0);

    int Nbcoupe2 = Nbcoupe+2;

    if(isdtmp)
    {
        Nsv=imanb+1;
    }
    else
        Nsv = Nbcoupe2/2;

    vol.hauteur = Haut;//hauteur de ton image
    vol.largeur = Larg;//larg image
    vol.nbcoupes = Nbcoupe2;

    //allocation memoire buffer donnees originales et resultat
    //ajout de 2 images supplementaires, noires, en haut et en bas du volume
    buf0 = (unsigned char***)mat3Dalloc(sizeof(unsigned char),Nbcoupe2,Haut,Larg);

    //-----------------------------------//
    buf1 = (unsigned char***)mat3Dalloc(sizeof(unsigned char),Nbcoupe2,Haut,Larg);


    unsigned char ***buf2=NULL;
    buf2 = (unsigned char***)mat3Dalloc(sizeof(unsigned char),Nbcoupe2,Haut,Larg);

    unsigned char ***buf3=NULL;
    buf3 = (unsigned char***)mat3Dalloc(sizeof(unsigned char),Nbcoupe2,Haut,Larg);


    //lecture volume original dans buf1
    fprintf(stderr,"\n");
    for(k=0;k<Nbcoupe;k++)
    {


        fprintf(stderr,"\r Read coupe: %d (real: %d)",k,start + step*k);

        nom[0]='\0';
        sprintf(nom,format,base,start+step*k,ext,'\0');
        id = ouvert_fic(nom,"rb");

        if(!read_coupe(id,ILarg,IHaut,buf1[k+1]))
        {
            fprintf(stderr,"FATAL ERROR: L'image %s n'a pas les bonnes dimensions :%dx%d !\n",nom,Larg,Haut);
            fclose(id);
            exit(1);
        }
        else
            fclose(id);
    }


    fprintf(stderr,"\nBegin processing\n");
    bool validate;


    if(smooth3D)
    {
        fprintf(stderr,"smooth3D, rad=%d,sigma=%g...\n",rad3D,sig3D);
        smooth_data(buf1,vol,rad3D,rad3D,rad3D,sig3D);
        fprintf(stderr,"end\n");
        save_coupe(buf1[Nsv],Larg,Haut,"test_smooth.pgm");
    }

    save_coupe(buf1[Nsv],Larg,Haut,"test_orig_k.pgm");

    //exemple binarisation
    for(k=0;k<Nbcoupe2;k++)
        for(i=0;i<Haut;i++)
            for(j=0;j<Larg;j++)
            {
                if(buf1[k][i][j]>200)
                    buf0[k][i][j]=255;
                else
                    buf0[k][i][j]=0;
            }
    save_coupe(buf0[Nsv],Larg,Haut,"test_bin_k.pgm");

    /*for(i=0;i<Haut;i++)
        for(j=0;j<Larg;j++)
        {

            if(buf0[Nsv][i][j]>0 && buf1[Nsv][i][j]>254)
                buf0[Nsv][i][j]=100;

        }*/

    //2D pellet detection

    GImage *Ima1 = NULL;

    //detection en k
    Ima1 = new GImage(Haut,Larg);
    Iout = new GImage(Haut,Larg);
    for(k=0;k<Nbcoupe2;k++)
    {
        Ima1->Init(buf0[k]);
        Ima1->Bin=True;

        BoucheTrous4C(Ima1, Iout);
        Algebre(Iout,Ima1,Iout,'-');
        Ima1->ImageCopy(Iout);
        //open_gdisk(Iout,6);
        //recons_gris(Ima1, Iout, Iout);
        Iout->Copyto(buf2[k]);


    }
    delete Ima1; Ima1=NULL;
    delete Iout; Iout=NULL;

    save_coupe(buf2[Nsv],Larg,Haut,"test_traitementk_k.pgm");

    //detection en i
    Ima1 = new GImage(Nbcoupe2,Larg);
    Iout = new GImage(Nbcoupe2, Larg);
    for(i=0;i<Haut;i++) {

        for (j = 0; j < Larg; j++) {
            for (k = 0; k < Nbcoupe2; k++)
                Ima1->Buf[j][k] = buf0[k][i][j];
            }
        Ima1->Bin=True;
        if(i==Haut/2)
            save_coupe(Ima1->Buf,Nbcoupe2,Larg,"test_bin_i.pgm");

        BoucheTrous4C(Ima1, Iout);
        Algebre(Iout,Ima1,Iout,'-');
        Ima1->ImageCopy(Iout);
        //open_gdisk(Iout,6);
        //recons_gris(Ima1, Iout, Iout);

        if(i==Haut/2)
            save_coupe(Iout->Buf,Nbcoupe2,Larg,"test_traitementi_i.pgm");

        for (j = 0; j < Larg; j++)
            for (k = 0; k < Nbcoupe2; k++) {
                buf2[k][i][j] = max(Iout->Buf[j][k], buf2[k][i][j]);
            }
    }
    delete Ima1; Ima1=NULL;
    delete Iout; Iout=NULL;

    save_coupe(buf2[Nsv],Larg,Haut,"test_traitement2_k.pgm");

    //detection j
    Ima1 = new GImage(Haut,Nbcoupe2);
    Iout = new GImage(Haut,Nbcoupe2);
    for(j=0;j<Larg;j++) {

        for (k = 0; k < Nbcoupe2; k++) {
            for (i = 0; i < Haut; i++)
                Ima1->Buf[k][i] = buf0[k][i][j];
            }

        Ima1->Bin=True;
        if(j==Larg/2)
            save_coupe(Ima1->Buf,Haut,Nbcoupe2,"test_bin_j.pgm");

        BoucheTrous4C(Ima1, Iout);
        Algebre(Iout,Ima1,Iout,'-');
        Ima1->ImageCopy(Iout);
        //open_gdisk(Iout,6);
        //recons_gris(Ima1, Iout, Iout);

        if(j==Larg/2)
            save_coupe(Iout->Buf,Haut,Nbcoupe2,"test_traitementj_j.pgm");



        for (k = 0; k < Nbcoupe2; k++)
            for (i = 0; i < Haut; i++) {
                buf2[k][i][j] = max(Iout->Buf[k][i], buf2[k][i][j]);
            }
    }
    delete Ima1;
    delete Iout;

    Ima1 = NULL;
    Iout = NULL;

    save_coupe(buf2[Nsv],Larg,Haut,"test_traitement3_k.pgm");

    open_cd_sphere(buf2, buf3, 6.1, Haut, Larg, Nbcoupe2);

    for(k=0; k<Nbcoupe2; k++)
        for(i=0; i<Haut; i++)
            for(j=0; j<Larg; j++) {
                if (buf3[k][i][j] > 0) {
                    buf0[k][i][j] = 128;
                }

            }
    save_coupe(buf0[Nsv],Larg,Haut,"test_ouverture3D_k_61.pgm");

    //


    //LEGENDE NIVEAUX DE GRIS

    //trou détecté = 128
    //trou étiqueté = 64
    //premier voxel de chaque trou = 32
    //milieu des trous = 16


    //parcours des trous pour les étiqueter

    int Ntrou = 0 ;

    VOXEL *premiertrou = NULL;
    VOXEL *derniertrou = NULL;
    VOXEL *voxtrou = NULL, *vox1=NULL;
    COORDINATES *fcoordinates = NULL, *lcoordinates = NULL;
    COORDINATES *coordinates = NULL;
    int ic=0, jc=0, kc=0;

    for(k=0; k<Nbcoupe2; k++)
        for(i=0; i<Haut; i++)
            for(j=0; j<Larg; j++) {
                if (buf0[k][i][j] == 128) {

                    voxtrou = new VOXEL(i,j,k,Ntrou);
                    assert(voxtrou);
                    Ntrou++;
                    invoxel(voxtrou, premiertrou, derniertrou);

                    vox1 = new VOXEL(i,j,k,Ntrou);
                    assert(vox1);
                    parcours_objet(vox1, 26, buf0, 128, 64, Larg, Haut, Nbcoupe2, coordinates);
                    incoordinates(coordinates,fcoordinates,lcoordinates);
                    kc = int (-coordinates->z + 0.5);
                    ic = int (coordinates->x + 0.5);
                    jc = int (coordinates->y + 0.5);
                    buf0[kc][ic][jc] = 16;
                    delete vox1; vox1=NULL;
                    coordinates = NULL;
                    voxtrou = NULL;

                    //fprintf(stderr,"found: i=%d,j=%d,k=%d\n",i,j,k);

                    //buf0[k][i][j] = 32; //colorier premier voxel


                }
            }

    //sauvegarde

    //if(issave)
    //{
    for(k=0;k<Nbcoupe;k++)
    {

        nom[0]='\0';
        sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%c",'\0');
        sprintf(nom,format,base,start + step*k,"_obj.pgm",'\0');
        fprintf(stderr,"\rSave coupe: %d (real: %s)  ",k,nom);
        save_coupe(buf0[k+1],Larg,Haut,nom);
    }
    //}

    COORDINATES *param=NULL, *f_parok=NULL, *l_parok=NULL,*f_parwr=NULL, *l_parwr=NULL;

    COORDINATES *parameters=NULL;
//f_parameter, *l_parameter sont mis à jour lors de la detection d'objets;

// write in file the center coordinates and direction of the objects
    pub[0]='\0';
    sprintf(pub,"Objects_volume%d.txt%c",1,'\0');
    id = ouvert_fic(pub,"w");

    fprintf(id,"\n Center coordinates pixels: x\ty\tz\t Orientation (3 coordinates): x\ty\tz\t Volume \n");

    parameters = fcoordinates;
    i=0;
    while(parameters != NULL)
    {
        i++;
        //fprintf(id," %g; %g; %g; \t %g; %g; %g; ",parameters->x,parameters->y,parameters->z,parameters->max_dir[0],parameters->max_dir[1],parameters->max_dir[2]);
        fprintf(id,"\t\t %d \n",parameters->vol);
        parameters=parameters->suiv;
    }
    fprintf(id,"Total number of objects: %d",i);
    fclose(id);

    parameters = fcoordinates;
    fprintf(stderr,"Toto\n");
    i=0;
    while(parameters != NULL)
    {
        i++;
        draw_cylindre(buf0,parameters,6.1,20,Haut,Larg,Nbcoupe2);
        fprintf(stderr,"point %d     \r",i);
        parameters=parameters->suiv;
    }

    //calcul gradients à partir des images originales
    for(k=0;k<Nbcoupe2;k++)
        for(i=0;i<Haut;i++)
            for(j=0;j<Larg;j++)
            {
                if(buf1[k][i][j]>200)
                    buf2[k][i][j]=255;
                else
                    buf2[k][i][j]=0;
            }
    for(k=1; k<Nbcoupe2-1; k++)
        for(i=1; i<Haut-1; i++)
            for(j=1; j<Larg-1; j++) {
                int temp = (buf2[k+1][i][j] - buf2[k-1][i][j])/2 + (buf2[k][i+1][j] - buf2[k][i-1][j])/2 + (buf2[k][i][j+1] - buf2[k][i][j-1])/2;
                if (temp > 255) {
                    buf3[k][i][j] = 255;
                }
                else {
                    buf3[k][i][j] = temp;
                }
            }

    parameters = fcoordinates;
    while(parameters != NULL)
    {
        draw_cylindre(buf3,parameters,6.1,19,Haut,Larg,Nbcoupe2);
        parameters=parameters->suiv;
    }



    //read text file
    /*char chx[50],chy[50],chz[50],chdx[50],chdy[50],chdz[50];
    double px,py,pz,pdx,pdy,pdz;
      double maxdir[3];

    char linescan[1000];
    id = ouvert_fic(filepos,"r");
    while(!feof(id))
    {
        linescan[0]='\0';
        if(fgets(linescan,995,id)==NULL)
            break;


        chx[0]='\0';
        chy[0]='\0';
        chz[0]='\0';
        chdx[0]='\0';
        chdy[0]='\0';
        chdz[0]='\0';
        //fprintf(stderr,"Parsing line %s\n",linescan);
        endptr = strrchr(linescan,';');
        //champ "eti"
        if(endptr == NULL)
          {
            fprintf(stderr,"Format error when reading %s file :%s\n",filepos,linescan);
                exit(2);
          }
        //strncpy(path,base,endptr-base);
        linescan[endptr-linescan]='\0';
        eti = atoi(endptr+1);
        //strcpy(base,(endptr+1));
        //champ chdz
        endptr = strrchr(linescan,';');
        if(endptr == NULL)
          {
            fprintf(stderr,"Format error when reading %s file :%s\n",filepos,linescan);
                exit(2);
          }
        strcpy(chdz,(endptr+1));
        linescan[endptr-linescan]='\0';

        //champ chdy
        endptr = strrchr(linescan,';');
        if(endptr == NULL)
          {
            fprintf(stderr,"Format error when reading %s file :%s\n",filepos,linescan);
                exit(2);
          }
        strcpy(chdy,(endptr+1));
        linescan[endptr-linescan]='\0';

        //champ chdx
        endptr = strrchr(linescan,';');
        if(endptr == NULL)
          {
            fprintf(stderr,"Format error when reading %s file :%s\n",filepos,linescan);
                exit(2);
          }
        strcpy(chdx,(endptr+1));
        linescan[endptr-linescan]='\0';

        //champ chz
        endptr = strrchr(linescan,';');
        if(endptr == NULL)
          {
            fprintf(stderr,"Format error when reading %s file :%s\n",filepos,linescan);
                exit(2);
          }
        strcpy(chz,(endptr+1));
        linescan[endptr-linescan]='\0';

        //champ chy
        endptr = strrchr(linescan,';');
        if(endptr == NULL)
          {
            fprintf(stderr,"Format error when reading %s file :%s\n",filepos,linescan);
                exit(2);
          }
        strcpy(chy,(endptr+1));
        linescan[endptr-linescan]='\0';

        //chx
        strcpy(chx,linescan);
        // fprintf(stderr,"Read:  %s; %s; %s; \t %s; %s; %s; \t\t %d\n",chx,chy,chz,chdx,chdy,chdz,eti);

       px = strtod(chx,endpt);
       py = strtod(chy,endpt);
       pz = strtod(chz,endpt);
       pdx = strtod(chdx,endpt);
       pdy = strtod(chdy,endpt);
       pdz = strtod(chdz,endpt);
       fprintf(stderr,"Object position:  %g; %g; %g; \t %g; %g; %g; \t\t %d\n",px,py,pz,pdx,pdy,pdz,eti);
       i = (int)floor(px);
       j = (int)floor(py);
       k = -(int)floor(pz);
       validate=true;
       param=NULL;
       if(save_valid)
       {
          validate = check_matching2buf(buf1,i,j,k,pdx,pdy,-pdz,(int)floor(l_cyl/2.0),r_gt+0.5,Haut,Larg,Nbcoupe+2,128);
          maxdir[0]=pdx;
          maxdir[1]=pdy;
          maxdir[2]=pdz;
          param = new COORDINATES(px,py,pz,l_cyl/2.0,maxdir,eti);
          if(validate)
              incoordinates(param,f_parok,l_parok);//liste points valides
          else
              incoordinates(param,f_parwr,l_parwr);//liste points rejetes
       }
       else
       {
          maxdir[0]=pdx;
          maxdir[1]=pdy;
          maxdir[2]=pdz;
          param = new COORDINATES(px,py,pz,l_cyl/2.0,maxdir,eti);
          incoordinates(param,f_parok,l_parok);//liste points valides

       }

       write_axis2buf(buf0,i,j,k,pdx,pdy,-pdz,(int)floor(l_cyl/2.0),r_gt,Haut,Larg,Nbcoupe+2,validate);
       write_axis2buf(buf0,i,j,k,pdx,pdy,-pdz,(int)floor(l_cyl/2.0),r_ext,Haut,Larg,Nbcoupe+2,validate);

    }

    fclose(id);

    if(save_valid)
    {
        endptr = strrchr(filepos,'/');
        if(endptr != NULL)
          strcpy(pub,endptr+1);
        else
        {
          endptr = strrchr(filepos,'\\');
          if(endptr != NULL)
              strcpy(pub,endptr+1);
          else
              strcpy(pub,filepos);
        }

        endptr = strrchr(pub,'.');
        if(endptr != NULL)
          pub[endptr-pub]='\0';//nom fichier position objets sans extension
        if(f_parok != NULL)
        {
          nom[0]='\0';
          sprintf(nom,"%s_valid_pix.txt%c",pub,'\0');
          id = ouvert_fic(nom,"w");
          param = f_parok;
          while(param != NULL)
          {
              fprintf(id," %g; %g; %g; \t %g; %g; %g; ",param->x,param->y,param->z,param->max_dir[0],param->max_dir[1],param->max_dir[2]);
              fprintf(id,"\t\t %d \n",param->vol);
              param=param->suiv;
          }
          fclose(id);

          nom[0]='\0';
          sprintf(nom,"%s_valid_mm.txt%c",pub,'\0');
          id = ouvert_fic(nom,"w");
          param = f_parok;
          while(param != NULL)
          {
              fprintf(id," %g; %g; %g; \t %g; %g; %g; ",param->x*PSZ,param->y*PSZ,param->z*ZSZ,param->max_dir[0],param->max_dir[1],param->max_dir[2]);
              fprintf(id,"\t\t %d \n",param->vol);
              param=param->suiv;
          }
          fclose(id);

        }

        if(f_parwr != NULL)
        {
          nom[0]='\0';
          sprintf(nom,"%s_reject_pix.txt%c",pub,'\0');
          id = ouvert_fic(nom,"w");
          param = f_parwr;
          while(param != NULL)
          {
              fprintf(id," %g; %g; %g; \t %g; %g; %g; ",param->x,param->y,param->z,param->max_dir[0],param->max_dir[1],param->max_dir[2]);
              fprintf(id,"\t\t %d \n",param->vol);
              param=param->suiv;
          }
          fclose(id);
        }

    }
  */

//sauvegarder les axes
    KImage *KIma=NULL;
    char **info_null=NULL;

    strcpy(pub,ext);
    endptr = strrchr(pub,'.');
    if(endptr != NULL)
        pub[endptr-pub]='\0';


    /*if(save_color)
    {

        KIma = new KImage(Larg,Haut);
        for(k=0;k<Nbcoupe;k++)
        {
            for(i=0;i<Haut;i++)
                for(j=0;j<Larg;j++)
                {
                    if(buf0[k+1][i][j]==0 || buf0[k+1][i][j]==255)
                    {
                        KIma->Buf[i][j].r = KIma->Buf[i][j].g = KIma->Buf[i][j].b = buf1[k+1][i][j];
                    }
                    else if(buf0[k+1][i][j]==128)
                    {//objet détecté
                        KIma->Buf[i][j].b = 128;
                        KIma->Buf[i][j].r = 128;
                        KIma->Buf[i][j].g = 128;
                    }
                    else if(buf0[k+1][i][j]==64)
                    {//objet étiqueté
                        KIma->Buf[i][j].g = 255;
                        KIma->Buf[i][j].r = KIma->Buf[i][j].b = 0;
                    }
                    else  if(buf0[k+1][i][j]==32)
                    {//premier voxel des trous
                        KIma->Buf[i][j].r = 255;
                        KIma->Buf[i][j].g = KIma->Buf[i][j].b = 0;
                    }
                    else  if(buf0[k+1][i][j]==16)
                    {//centre des trous
                        KIma->Buf[i][j].b = 255;
                        KIma->Buf[i][j].g = KIma->Buf[i][j].r = 0;
                    }
                    else  if(buf0[k+1][i][j]==100)
                    {//
                        KIma->Buf[i][j].r = 255;
                        KIma->Buf[i][j].g = KIma->Buf[i][j].b = 0;
                    }
                    else  if(buf0[k+1][i][j]==110)
                    {//extérieur
                        KIma->Buf[i][j].b = 255;
                        KIma->Buf[i][j].g = KIma->Buf[i][j].r = 0;
                    }
                }
            nom[0]='\0';
            if(pub[0]!='\0')
            {
                sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%s%c",'\0');
                sprintf(nom,format,base,start + step*k,pub,"_coloraxis.ppm",'\0');
            }
            else
            {
                sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%c",'\0');
                sprintf(nom,format,base,start + step*k,"_coloraxis.ppm",'\0');
            }
            fprintf(stderr,"\rSave coupe: %d (real: %s)  ",k,nom);
            id = ouvert_fic(nom,"wb");
            KIma->save_image_color(id,info_null);
            fclose(id);
        }

        delete KIma;
    }*/

    if(save_color) //buf3 gradients uniquement
    {

        KIma = new KImage(Larg,Haut);
        for(k=0;k<Nbcoupe;k++)
        {
            for(i=0;i<Haut;i++)
                for(j=0;j<Larg;j++)
                {
                    if(buf3[k+1][i][j]==0 || buf3[k+1][i][j]==255)
                    {
                        KIma->Buf[i][j].r = KIma->Buf[i][j].g = KIma->Buf[i][j].b = buf3[k+1][i][j];
                    }
                    else  if(buf3[k+1][i][j]==100)
                    {//
                        KIma->Buf[i][j].r = 255;
                    }
                    else  if(buf3[k+1][i][j]==110)
                    {//extérieur
                        KIma->Buf[i][j].b = 255;
                    }
                }
            nom[0]='\0';
            if(pub[0]!='\0')
            {
                sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%s%c",'\0');
                sprintf(nom,format,base,start + step*k,pub,"_grad.ppm",'\0');
            }
            else
            {
                sprintf(format,"%s%d%s%c","%s%0",repr,"d%s%c",'\0');
                sprintf(nom,format,base,start + step*k,"_grad.ppm",'\0');
            }
            fprintf(stderr,"\rSave coupe: %d (real: %s)  ",k,nom);
            id = ouvert_fic(nom,"wb");
            KIma->save_image_color(id,info_null);
            fclose(id);
        }

        delete KIma;
    }



//	freelistcoordinates(f_parok,l_parok);
//	freelistcoordinates(f_parwr,l_parwr);

    //elib mem
    fprintf(stderr,"Memory free ...");
    mat3Dfree((void***&)buf0,Nbcoupe2,Haut,Larg);
    mat3Dfree((void***&)buf1,Nbcoupe2,Haut,Larg);
    mat3Dfree((void***&)buf2,Nbcoupe2,Haut,Larg);




    pub[0]='\0';
    sprintf(pub,"report_file_seg_cyl_%s.txt%c",base,'\0');
    id = ouvert_fic(pub,"a");
    fprintf(id,"\nend:\n");
    time(&maintenant);
    fprintf(id,"%s\n",ctime(&maintenant));
    fclose(id);


    free(nom);
    free(format);
    free(base);
    free(ext);
    fprintf(stderr,"end\n");




    return(0);



}
  
