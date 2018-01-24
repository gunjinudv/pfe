#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include <unistd.h>
//#include <dirent.h>
#include <float.h>
//#include <values.h>
#include <limits.h>
#include <math.h>
//#include "defs.h"
#include "image.h"
#include "inout.h"
#include "distmap.h"
#include "procedures.h"

extern double PSZ;
extern double ZSZ;

//#define min(a,b) (a <= b ? a : b)


//***************************************
//mask class 
//***************************************





AMask::AMask(int mtype)
{
	int n;
	support = True;
	switch(mtype)
	{
		case 123:
			//mask size 3*3*3 1-2-3
			NE=13;
			dbase=1;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=0;


				mask[0].value=mask[2].value=mask[6].value=mask[8].value=1;//vertex
				mask[1].value=mask[3].value=mask[5].value=mask[7].value=2;//edge
				mask[4].value=3;//face
				mask[9].value=mask[11].value=2;//edge
				mask[10].value=mask[12].value=3;//face

				break;}
		default:
			fprintf(stderr,"unsupported type!\n");
			support = False;
			mask = NULL;
			break;
	}
}

AMask::~AMask()
{
	if(mask)
		free(mask);
}
//---------------------



BMask::BMask(int mtype)
{
	double mnsize = min(PSZ,ZSZ);
	double ps = PSZ/mnsize;
	double zs = ZSZ/mnsize;
	int n;
	support = True;
	switch(mtype)
	{
		case 1:
			//mask size 3*3*3
			NE=14;
			dbase=30;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

// 	mask[13].value=0;
// 	mask[0].value=mask[2].value=mask[6].value=mask[8].value=5;
// 	mask[1].value=mask[3].value=mask[5].value=mask[7].value=4;
// 	mask[4].value=3;
// 	mask[9].value=mask[11].value=4;
// 	mask[10].value=mask[12].value=3;

				break;}

		case 123:
			//mask size 3*3*3 1-2-3
			NE=14;
			dbase=10;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

// 	mask[13].value=0;
// 	mask[0].value=mask[2].value=mask[6].value=mask[8].value=3;
// 	mask[1].value=mask[3].value=mask[5].value=mask[7].value=2;
// 	mask[4].value=1;
// 	mask[9].value=mask[11].value=2;
// 	mask[10].value=mask[12].value=1;

				break;}

		case 2:
			//mask size 5*5*5
			NE= 50;
			dbase=50;


			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

				mask[13].value=0;
				mask[0].value=mask[2].value=mask[6].value=mask[8].value=8;
				mask[1].value=mask[3].value=mask[5].value=mask[7].value=7;
				mask[4].value=5;
				mask[9].value=mask[11].value=7;
				mask[10].value=mask[12].value=5;

				//extend mask with size 3*3*3 to 5*5*5
				for( n=14;n<=29;n++)
					mask[n].k=-2;
				for ( n=30;n<=45;n++)
					mask[n].k=-1;
				for( n=46;n<=49;n++)
					mask[n].k=0;

				mask[14].i=mask[15].i=-2;
				mask[16].i=mask[17].i=mask[18].i=mask[19].i=mask[20].i=-1;
				mask[21].i=mask[22].i=0;
				mask[23].i=mask[24].i=mask[25].i=mask[26].i=mask[27].i=1;
				mask[28].i=mask[29].i=2;
				mask[30].i=mask[31].i=mask[32].i=mask[33].i=mask[34].i=-2;
				mask[35].i=mask[36].i=-1;
				mask[37].i=mask[38].i=0;
				mask[39].i=mask[40].i=1;
				mask[41].i=mask[42].i=mask[43].i=mask[44].i=mask[45].i=2;
				mask[46].i=mask[47].i=-2;
				mask[48].i=mask[49].i=-1;

				mask[16].j=mask[23].j=mask[30].j=mask[35].j=mask[37].j=mask[39].j=mask[41].j=mask[48].j=-2;
				mask[14].j=mask[17].j=mask[21].j=mask[24].j=mask[28].j=mask[31].j=mask[42].j=mask[46].j=-1;
				mask[18].j=mask[25].j=mask[32].j=mask[43].j=0;
				mask[15].j=mask[19].j=mask[22].j=mask[26].j=mask[29].j=mask[33].j=mask[44].j=mask[47].j=1;
				mask[20].j=mask[27].j=mask[34].j=mask[36].j=mask[38].j=mask[40].j=mask[45].j=mask[49].j=2;

// 	mask[14].value=mask[15].value=mask[16].value=mask[20].value=15;
// 	mask[23].value=mask[27].value=mask[28].value=mask[29].value=15;
// 	mask[17].value=mask[19].value=mask[24].value=mask[26].value=12;
// 	mask[18].value=mask[21].value=mask[22].value=mask[25].value=11;
// 	mask[30].value=mask[34].value=mask[41].value=mask[45].value=15;
// 	mask[31].value=mask[33].value=mask[35].value=mask[36].value=12;
// 	mask[39].value=mask[40].value=mask[42].value=mask[44].value=12;
// 	mask[32].value=mask[37].value=mask[38].value=mask[43].value=11;
// 	mask[46].value=mask[47].value=mask[48].value=mask[49].value=11;
				break;}

		case 3:
			//mask size 5*5*5, but only include pixel which distance is less than 5^0.5
			NE=26;
			dbase=50;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

// 	mask[13].value=0;
// 	mask[0].value=mask[2].value=mask[6].value=mask[8].value=8;
// 	mask[1].value=mask[3].value=mask[5].value=mask[7].value=7;
// 	mask[4].value=5;
// 	mask[9].value=mask[11].value=7;
// 	mask[10].value=mask[12].value=5;

				//extend mask
// 	for( n=14;n<26;n++)
// 	  mask[n].value=11;

				for( n=14;n<18;n++)
					mask[n].k=-2;
				for( n=18;n<22;n++)
					mask[n].k=-1;
				for( n=22;n<26;n++)
					mask[n].k=0;

				mask[18].i=mask[22].i=mask[23].i=-2;
				mask[14].i=mask[24].i=mask[25].i=-1;
				mask[15].i=mask[16].i=mask[19].i=mask[20].i=0;
				mask[17].i=1;
				mask[21].i=2;

				mask[19].j=mask[24].j=-2;
				mask[15].j=mask[22].j=-1;
				mask[14].j=mask[17].j=mask[18].j=mask[21].j=0;
				mask[16].j=mask[23].j=1;
				mask[20].j=mask[25].j=2;




				break;}


		default:
			printf("unsupported type!\n");
			support = False;
			mask = NULL;
			break;
	}

	//correction en pixel/z-size
	double val,x,y,z;
	for( n=0;n<NE;n++)
	{
// 	val = mask[n].value;
// 	if(mask[n].i != 0 || mask[n].j != 0)
// 	  val = val*ps;
// 	if(mask[n].k != 0)
// 	  val = val*zs;
		x = mask[n].i*ps;
		y = mask[n].j*ps;
		z = mask[n].k*zs;
		val = (double)dbase*sqrt(x*x+y*y+z*z);

		mask[n].value = (int)floor(val);
	}
	if(mtype==3)
	{
		fprintf(stderr,"Mask type 3:\na=%d,b=%d,c=%d,d=%d,e=%d,f=%d,g=%d,h=%d\n",mask[10].value,mask[4].value,mask[11].value,mask[5].value,mask[8].value,mask[22].value,mask[20].value,mask[17].value);
	}
}

BMask::~BMask()
{
	if(mask)
		free(mask);
}

//-------------




CMask::CMask(int mtype)
{
	double mnsize = min(PSZ,ZSZ);
	double ps = PSZ/mnsize;
	double zs = ZSZ/mnsize;
	int n;
	support = True;
	switch(mtype)
	{
		case 1:
			//mask size 3*3*3
			NE=14;
			dbase=3;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

				mask[13].value=0;
				mask[0].value=mask[2].value=mask[6].value=mask[8].value=5;
				mask[1].value=mask[3].value=mask[5].value=mask[7].value=4;
				mask[4].value=3;
				mask[9].value=mask[11].value=4;
				mask[10].value=mask[12].value=3;

				break;}

		case 123:
			//mask size 3*3*3 1-2-3
			NE=14;
			dbase=1;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

				mask[13].value=0;
				mask[0].value=mask[2].value=mask[6].value=mask[8].value=3;
				mask[1].value=mask[3].value=mask[5].value=mask[7].value=2;
				mask[4].value=1;
				mask[9].value=mask[11].value=2;
				mask[10].value=mask[12].value=1;

				break;}

		case 2:
			//mask size 5*5*5
			NE= 50;
			dbase=5;


			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)//line 48
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

				mask[13].value=0;
				mask[0].value=mask[2].value=mask[6].value=mask[8].value=8;
				mask[1].value=mask[3].value=mask[5].value=mask[7].value=7;
				mask[4].value=5;
				mask[9].value=mask[11].value=7;
				mask[10].value=mask[12].value=5;

				//extend mask with size 3*3*3 to 5*5*5
				for( n=14;n<=29;n++)
					mask[n].k=-2;
				for ( n=30;n<=45;n++)
					mask[n].k=-1;
				for( n=46;n<=49;n++)
					mask[n].k=0;

				mask[14].i=mask[15].i=-2;
				mask[16].i=mask[17].i=mask[18].i=mask[19].i=mask[20].i=-1;
				mask[21].i=mask[22].i=0;
				mask[23].i=mask[24].i=mask[25].i=mask[26].i=mask[27].i=1;
				mask[28].i=mask[29].i=2;
				mask[30].i=mask[31].i=mask[32].i=mask[33].i=mask[34].i=-2;
				mask[35].i=mask[36].i=-1;
				mask[37].i=mask[38].i=0;
				mask[39].i=mask[40].i=1;
				mask[41].i=mask[42].i=mask[43].i=mask[44].i=mask[45].i=2;
				mask[46].i=mask[47].i=-2;
				mask[48].i=mask[49].i=-1;

				mask[16].j=mask[23].j=mask[30].j=mask[35].j=mask[37].j=mask[39].j=mask[41].j=mask[48].j=-2;
				mask[14].j=mask[17].j=mask[21].j=mask[24].j=mask[28].j=mask[31].j=mask[42].j=mask[46].j=-1;
				mask[18].j=mask[25].j=mask[32].j=mask[43].j=0;
				mask[15].j=mask[19].j=mask[22].j=mask[26].j=mask[29].j=mask[33].j=mask[44].j=mask[47].j=1;
				mask[20].j=mask[27].j=mask[34].j=mask[36].j=mask[38].j=mask[40].j=mask[45].j=mask[49].j=2;

				mask[14].value=mask[15].value=mask[16].value=mask[20].value=15;
				mask[23].value=mask[27].value=mask[28].value=mask[29].value=15;
				mask[17].value=mask[19].value=mask[24].value=mask[26].value=12;
				mask[18].value=mask[21].value=mask[22].value=mask[25].value=11;
				mask[30].value=mask[34].value=mask[41].value=mask[45].value=15;
				mask[31].value=mask[33].value=mask[35].value=mask[36].value=12;
				mask[39].value=mask[40].value=mask[42].value=mask[44].value=12;
				mask[32].value=mask[37].value=mask[38].value=mask[43].value=11;
				mask[46].value=mask[47].value=mask[48].value=mask[49].value=11;
				break;}

		case 3:
			//mask size 5*5*5, but only include pixel which distance is less than 5^0.5
			NE=26;
			dbase=5;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

				mask[13].value=0;
				mask[0].value=mask[2].value=mask[6].value=mask[8].value=8;
				mask[1].value=mask[3].value=mask[5].value=mask[7].value=7;
				mask[4].value=5;
				mask[9].value=mask[11].value=7;
				mask[10].value=mask[12].value=5;

				//extend mask
				for( n=14;n<26;n++)
					mask[n].value=11;

				for( n=14;n<18;n++)
					mask[n].k=-2;
				for( n=18;n<22;n++)
					mask[n].k=-1;
				for( n=22;n<26;n++)
					mask[n].k=0;

				mask[18].i=mask[22].i=mask[23].i=-2;
				mask[14].i=mask[24].i=mask[25].i=-1;
				mask[15].i=mask[16].i=mask[19].i=mask[20].i=0;
				mask[17].i=1;
				mask[21].i=2;

				mask[19].j=mask[24].j=-2;
				mask[15].j=mask[22].j=-1;
				mask[14].j=mask[17].j=mask[18].j=mask[21].j=0;
				mask[16].j=mask[23].j=1;
				mask[20].j=mask[25].j=2;




				break;}

		case 4:
			//mask size 5*5*5, but only include pixel which distance is less than 5^0.5; same as case 3 but with dbase x10; same as case 3 in BMask
			NE=26;
			dbase=50;

			if((mask=(melement *)calloc(NE,sizeof(melement)))==NULL)
			{
				fprintf(stderr,"ERROR: main: Allocation error\n");
				support=False;
				break;}
			else{
				mask[0].i=mask[1].i=mask[2].i=mask[9].i=mask[10].i=mask[11].i=-1;
				mask[3].i=mask[4].i=mask[5].i=mask[12].i=mask[13].i=0;
				mask[6].i=mask[7].i=mask[8].i=1;

				mask[0].j=mask[3].j=mask[6].j=mask[9].j=mask[12].j=-1;
				mask[1].j=mask[4].j=mask[7].j=mask[10].j=mask[13].j=0;
				mask[2].j=mask[5].j=mask[8].j=mask[11].j=1;

				mask[0].k=mask[1].k=mask[2].k=mask[3].k=mask[4].k=mask[5].k=mask[6].k=mask[7].k=mask[8].k=-1;
				mask[9].k=mask[10].k=mask[11].k=mask[12].k=mask[13].k=0;

// 	mask[13].value=0;
// 	mask[0].value=mask[2].value=mask[6].value=mask[8].value=8;
// 	mask[1].value=mask[3].value=mask[5].value=mask[7].value=7;
// 	mask[4].value=5;
// 	mask[9].value=mask[11].value=7;
// 	mask[10].value=mask[12].value=5;

				//extend mask
// 	for( n=14;n<26;n++)
// 	  mask[n].value=11;

				for( n=14;n<18;n++)
					mask[n].k=-2;
				for( n=18;n<22;n++)
					mask[n].k=-1;
				for( n=22;n<26;n++)
					mask[n].k=0;

				mask[18].i=mask[22].i=mask[23].i=-2;
				mask[14].i=mask[24].i=mask[25].i=-1;
				mask[15].i=mask[16].i=mask[19].i=mask[20].i=0;
				mask[17].i=1;
				mask[21].i=2;

				mask[19].j=mask[24].j=-2;
				mask[15].j=mask[22].j=-1;
				mask[14].j=mask[17].j=mask[18].j=mask[21].j=0;
				mask[16].j=mask[23].j=1;
				mask[20].j=mask[25].j=2;




				break;}


		default:
			printf("unsupported type!\n");
			support = False;
			mask = NULL;
			break;
	}

	//correction en pixel/z-size
	double val,x,y,z;
	for( n=0;n<NE;n++)
	{
// 	val = mask[n].value;
// 	if(mask[n].i != 0 || mask[n].j != 0)
// 	  val = val*ps;
// 	if(mask[n].k != 0)
// 	  val = val*zs;
		x = mask[n].i*ps;
		y = mask[n].j*ps;
		z = mask[n].k*zs;
		val = (double)dbase*sqrt(x*x+y*y+z*z);

		mask[n].value = (int)floor(val);
	}
	if(mtype==4)
	{
		fprintf(stderr,"Mask type 4:\na=%d,b=%d,c=%d,d=%d,e=%d,f=%d,g=%d,h=%d\n",mask[10].value,mask[4].value,mask[11].value,mask[5].value,mask[8].value,mask[22].value,mask[20].value,mask[17].value);
	}
}

CMask::~CMask()
{
	if(mask)
		free(mask);
}
//end of definition





//if error return value=1, else return value=0


int distance_map(unsigned char ***buf0,unsigned int*** &buf1,int height,int width,int length, int mtype,bool non_zero_val)
{
	CMask *mymask=NULL;


	if((buf0 == NULL)||(buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);

	if(mymask == NULL)
		return 1;

	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned int sum=MAXINT;
	bool change=False;

//initialize buf1
	if(non_zero_val)//carte dist par rap aux composantes non-nulles
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]!=0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=MAXINT;
				}
	}
	else//carte dist par rap aux composantes de val zero (complementaire)
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]==0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=MAXINT;
				}

	}


//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXINT;
				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{
						sum=min(sum,(unsigned int)mymask->mask[m].value+buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				//{
				//change=True;
				buf1[z][x][y]=sum;
				//}
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXINT;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{
						sum=min(sum,(unsigned int)mymask->mask[m].value + buf1[tz][tx][ty]);
					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				//{
				//change=True;
				buf1[z][x][y]=sum;
				//}

			}






	delete mymask;

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}

int distance_map_short(unsigned short ***buf0,unsigned short*** &buf1,int height,int width,int length, int mtype,bool non_zero_val)
{
	CMask *mymask=NULL;


	if((buf0 == NULL)||(buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);

	if(mymask == NULL)
		return 1;

	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned short sum=MAXSHRT;
	bool change=False;

//initialize buf1
	if(non_zero_val)//carte dist par rap aux composantes non-nulles
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]!=0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=MAXSHRT;
				}
	}
	else//carte dist par rap aux composantes de val zero (complementaire)
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]==0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=MAXSHRT;
				}

	}


//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXSHRT;
				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{
						sum=min(sum,(unsigned short)mymask->mask[m].value+buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				//{
				//change=True;
				buf1[z][x][y]=sum;
				//  }
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXSHRT;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{
						sum=min(sum,(unsigned short)mymask->mask[m].value + buf1[tz][tx][ty]);
					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				// {
				//change=True;
				buf1[z][x][y]=sum;
				// }

			}






	delete mymask;

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}



int distance_map_short(unsigned char ***buf0,unsigned short*** &buf1,int height,int width,int length, int mtype,bool non_zero_val)
{
	CMask *mymask=NULL;


	if((buf0 == NULL)||(buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);

	if(mymask == NULL)
		return 1;

	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned short sum=MAXSHRT;
	bool change=False;

//initialize buf1
	if(non_zero_val)//carte dist par rap aux composantes non-nulles
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]!=0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=MAXSHRT;
				}
	}
	else//carte dist par rap aux composantes de val zero (complementaire)
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]==0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=MAXSHRT;
				}

	}


//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXSHRT;
				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{
						sum=min(sum,(unsigned short)mymask->mask[m].value+buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				//{
				//change=True;
				buf1[z][x][y]=sum;
				//  }
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXSHRT;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{
						sum=min(sum,(unsigned short)mymask->mask[m].value + buf1[tz][tx][ty]);
					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				// {
				//change=True;
				buf1[z][x][y]=sum;
				// }

			}






	delete mymask;

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}


int distance_map_short(unsigned short*** &buf1,int height,int width,int length, int mtype)
{//buf1 already initialized

	CMask *mymask=NULL;


	if((buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);

	if(mymask == NULL)
		return 1;

	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned short sum=MAXSHRT;
	bool change=False;


//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXSHRT;
				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{
						sum=min(sum,(unsigned short)mymask->mask[m].value+buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				//{
				//change=True;
				buf1[z][x][y]=sum;
				//  }
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = MAXSHRT;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{
						sum=min(sum,(unsigned short)mymask->mask[m].value + buf1[tz][tx][ty]);
					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < buf1[z][x][y])
				// {
				//change=True;
				buf1[z][x][y]=sum;
				// }

			}






	delete mymask;

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}



int approx_distance_map(unsigned char ***buf0,unsigned char*** &buf1,int height,int width,int length, int mtype,bool non_zero_val)
{//carte de dist dans un buffer uchar - valeurs entieres tronquees a 255 donc valeurs reelles tronquees a 255/3 (mtype=1) ou a 255/5=51 (mtype=2,3)

	CMask *mymask=NULL;


	if((buf0 == NULL)||(buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);
	if(mymask == NULL)
	{

		return 1;
	}
	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	int sum=255;
	bool change=False;

//initialize buf1
	if(non_zero_val)//carte dist par rap aux composantes non-nulles
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]!=0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=255;
				}
	}
	else//carte dist par rap aux composantes de val zero (complementaire)
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf0[z][x][y]==0)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=255;
				}

	}


//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = 255;

				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{

						sum=min(sum,mymask->mask[m].value+(int)buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < (int)buf1[z][x][y])
				//{
				//change=True;

				buf1[z][x][y]=(unsigned char)(sum);
				// }
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = 255;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{

						sum=min(sum,mymask->mask[m].value+(int)buf1[tz][tx][ty]);
					}
				}
				//if (sum < (int)buf1[z][x][y]*mymask->dbase)
				//le point(0,0,0) est inclus dans le masque
				//if (sum < (int)buf1[z][x][y])
				//{
				//change=True;

				buf1[z][x][y]=(unsigned char)(sum);
				// }

			}






	delete mymask;


	return 0;
}


int approx_distance_cal(unsigned char ***buf0,unsigned char*** &buf1,int height,int width,int length, int mtype,VOXEL *fref,VOXEL *lref)
{//carte de dist dans un buffer uchar - valeurs entieres tronquees a 255 donc valeurs reelles tronquees a 255/3 (mtype=1) ou a 255/5=51 (mtype=2,3)
	//reference set in fref-lref; computation limited inside non-zero components

	CMask *mymask=NULL;
	VOXEL *vox=NULL;

	if((buf0 == NULL)||(buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);
	if(mymask == NULL)
	{

		return 1;
	}
	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	int sum=255;
	bool change=False;

//initialize buf1
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			memset(buf1[z][x],255,width*sizeof(char));

	vox=fref;
	while(vox != NULL)
	{
		buf1[vox->k][vox->i][vox->j]=0;
		vox = vox->suiv;
	}



//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = 255;

				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{

						sum=min(sum,mymask->mask[m].value+(int)buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < (int)buf1[z][x][y])
				//{
				//change=True;

				buf1[z][x][y]=(unsigned char)(sum);
				// }
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = 255;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{

						sum=min(sum,mymask->mask[m].value+(int)buf1[tz][tx][ty]);
					}
				}
				//if (sum < (int)buf1[z][x][y]*mymask->dbase)
				//le point(0,0,0) est inclus dans le masque
				//if (sum < (int)buf1[z][x][y])
				//{
				//change=True;

				buf1[z][x][y]=(unsigned char)(sum);
				// }

			}


	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf0[z][x][y]==0)
					buf1[z][x][y]=0;
			}



	delete mymask;


	return 0;
}


int approx_distance_map(unsigned char*** &buf1,int height,int width,int length, int mtype,unsigned char valref, bool same_val)
{//carte de dist dans un buffer uchar - valeurs entieres tronquees a 255 donc valeurs reelles tronquees a 255/3 (mtype=1) ou a 255/5=51 (mtype=2,3)

	CMask *mymask=NULL;


	if(buf1 == NULL)
	{
		fprintf(stderr,"\nERREUR: approx_distance_map: buffer non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);
	if(mymask == NULL)
	{

		return 1;
	}
	fprintf(stderr,"Operating distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	int sum=255;
	bool change=False;

//initialize buf1
	if(same_val)//carte dist par rap aux composantes de valeur valref
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf1[z][x][y]== valref)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=255;
				}
	}
	else//carte dist par rap aux composantes complementaires
	{
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf1[z][x][y] != valref)
						buf1[z][x][y]=0;
					else
						buf1[z][x][y]=255;
				}

	}


//distance transform

	fprintf(stderr,"\rIteration %d forward...          ",1);

//foward scan
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = 255;

				for(m=0;m<mymask->NE;m++)//line 143
				{
					tx=mymask->mask[m].i+x;
					ty=mymask->mask[m].j+y;
					tz=mymask->mask[m].k+z;
					if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
					{

						sum=min(sum,mymask->mask[m].value+(int)buf1[tz][tx][ty]);

					}
				}
				//le point(0,0,0) est inclus dans le masque
				//if (sum < (int)buf1[z][x][y])
				//{
				//change=True;

				buf1[z][x][y]=(unsigned char)(sum);
				// }
			}


	//backward scan
	fprintf(stderr,"\rIteration %d backward...          ",1);
	for(z=length-1;z>=0;z--)
		for(x=height-1;x>=0;x--)
			for(y=width-1;y>=0;y--)
			{
				if(buf1[z][x][y]==0)
					continue;
				sum = 255;
				for(m=0;m<mymask->NE;m++)
				{
					tx=x-mymask->mask[m].i;
					ty=y-mymask->mask[m].j;
					tz=z-mymask->mask[m].k;
					if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
					{

						sum=min(sum,mymask->mask[m].value+(int)buf1[tz][tx][ty]);
					}
				}
				//if (sum < (int)buf1[z][x][y]*mymask->dbase)
				//le point(0,0,0) est inclus dans le masque
				//if (sum < (int)buf1[z][x][y])
				//{
				//change=True;

				buf1[z][x][y]=(unsigned char)(sum);
				// }

			}






	delete mymask;


	return 0;
}





void limit_dilatation_cdist(unsigned char*** b_in,unsigned char*** &b_out,int Haut,int Larg,int Ncps,double radius)
{

	//dilatation de rayon limite a 255/5 = 51
	int i,j,k;
	double rad;



	if((b_in == NULL)||(b_out == NULL))
	{
		fprintf(stderr,"\nERREUR: dilation_cdist: buffer(s) non-alloue(s) !\n");
		exit(1);
	}



	int masktype = 3; //the type of mask is 3
	int base=5;



	if(radius > 255.0/(double)base)
	{
		rad = 255.0/(double)base;
		fprintf(stderr,"SE size too big ! Limited to %g\n",rad);

	}
	else
		rad = radius;


	// DISTANCE MAP COMPUTATION WRT COMPOSANTES NON-ZERO
	int result;

	if((result=approx_distance_map(b_in,b_out,Haut,Larg,Ncps,masktype,true))==1)
	{
		fprintf(stderr,"Fail to do distance transform! Will exit program!");
		exit(1);
	}



	for(k=0;k<Ncps;k++)
		for(i=0;i<Haut;i++)
			for(j=0;j<Larg;j++)
			{
				if((double)b_out[k][i][j]/(double)base <= rad)
					b_out[k][i][j] = 255;
				else
					b_out[k][i][j] = 0;

			}


}


void limit_erosion_cdist(unsigned char*** b_in,unsigned char*** &b_out,int Haut,int Larg,int Ncps,double radius)
{

	//erosion de rayon limite a 255/5 = 51
	int i,j,k;
	double rad;


	if((b_in == NULL)||(b_out == NULL))
	{
		fprintf(stderr,"\nERREUR: dilation_cdist: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	int masktype = 3; //the size of mask is 3
	int base=5;

	if(radius > 255.0/(double)base)
	{
		rad = 255.0/(double)base;
		fprintf(stderr,"SE size too big ! Limited to %g\n",rad);

	}
	else
		rad = radius;





	// DISTANCE MAP COMPUTATION WRT COMPOSANTES ZERO
	int result;

	if((result=approx_distance_map(b_in,b_out,Haut,Larg,Ncps,masktype,false))==1)
	{
		fprintf(stderr,"Fail to do distance transform! Will exit program!");
		exit(1);
	}



	for(k=0;k<Ncps;k++)
		for(i=0;i<Haut;i++)
			for(j=0;j<Larg;j++)
			{
				if((double)b_out[k][i][j]/(double)base >= rad)
					b_out[k][i][j] = 255;
				else
					b_out[k][i][j] = 0;

			}



}


//if error return value=1, else return value=0


int topologic_distance_map(unsigned char ***buf0,unsigned short*** &buf1,int height,int width,int length, int mtype)
//carte de distance calculee sur des hypersurfaces binaire en 3D, considerant le bord de la surface l'ensemble de points ayant moins de 8 voisins
{
	CMask *mymask=NULL;
	VOIS *ng=NULL;


	if((buf0 == NULL)||(buf1 == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}

	mymask=new CMask(mtype);
	ng = new VOIS(26);

	if(mymask == NULL || ng == NULL)
		return 1;

	fprintf(stderr,"Operating topologic distance map ...\n");
	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m,nv,i,j,k;
	int tx,ty,tz;
	unsigned short sum=MAXSHRT;
	bool change=False;

	//initialize buf1

	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if(buf0[z][x][y]!=0)
				{
					//initialisation avec le nb de voisins non-nuls
					nv=1;
					for(m=0;m<ng->Nbvois;m++)
					{
						i = ng->crd[m].i;
						j = ng->crd[m].j;
						k = ng->crd[m].k;
						if((z+k < 0) || (z+k >= length) || (x+i<0) || (x+i >= height) || (j+y<0) || (j+y>= width))
							continue;
						if(buf0[z+k][x+i][y+j]>0)
							nv++;
					}
					if(nv < 9)
						buf1[z][x][y]=nv;
					else
						buf1[z][x][y]=MAXSHRT;
				}
				else
					buf1[z][x][y]=0;
			}



	change = True;
	nv =0;
	//distance transform
	while(change)
	{
		change=False;
		nv++;
		fprintf(stderr,"\rIteration %d forward...          ",nv);

		//foward scan
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if(buf1[z][x][y]==0)
						continue;
					sum = MAXSHRT;
					for(m=0;m<mymask->NE;m++)//line 143
					{
						tx=mymask->mask[m].i+x;
						ty=mymask->mask[m].j+y;
						tz=mymask->mask[m].k+z;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							if(buf0[tz][tx][ty]>0)
								sum=min(sum,(unsigned short int)mymask->mask[m].value+buf1[tz][tx][ty]);

						}
					}
					if (sum < buf1[z][x][y])
					{
						change=True;
						buf1[z][x][y]=sum;
					}
				}


		//backward scan
		fprintf(stderr,"\rIteration %d backward...          ",nv);
		for(z=length-1;z>=0;z--)
			for(x=height-1;x>=0;x--)
				for(y=width-1;y>=0;y--)
				{
					if(buf1[z][x][y]==0)
						continue;
					sum = MAXSHRT;
					for(m=0;m<mymask->NE;m++)
					{
						tx=x-mymask->mask[m].i;
						ty=y-mymask->mask[m].j;
						tz=z-mymask->mask[m].k;
						if(tz>=0 && tz<length && tx<height && tx>=0 && ty<width && ty>=0)
						{
							if(buf0[tz][tx][ty]>0)
								sum=min(sum,(unsigned int)mymask->mask[m].value + buf1[tz][tx][ty]);
						}
						if (sum < buf1[z][x][y])
						{
							change=True;
							buf1[z][x][y]=sum;
						}
					}
				}

	}





	delete mymask;
	delete ng;
	fprintf(stderr,"\nend dist map.\n");
	return 0;
}


int geodesic_distance_map(unsigned char ***buf0,unsigned int*** &bcd,int height,int width,int length,VOXEL *fref, VOXEL *lref)
//carte de dist par rapport aux points  "ref" a l'interieur de composantes non-nulles
{
	CMask *mymask=NULL;


	if((buf0 == NULL)||(bcd == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}
	if(fref == NULL)
	{
		fprintf(stderr,"\nERREUR: distance_map: liste points reference vide!\n");
		exit(1);
	}
	mymask=new CMask(3);//5-7-11 restreint (26 elmnts par demi-masque)

	if(mymask == NULL)
		return 1;


	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned int sum=MAXINT;
	bool change;

	//initialisation calcul connexite
	long index,conx;//32-bits
	long vd[12], vi[12];//stoquer le voisinage direct et indirect des elmnts 14-25
	bool cnxd[12],cnxi[12];

	memset(vd,0,12*sizeof(long));
	memset(vi,0,12*sizeof(long));

//   for(m=0;m<12;m++)
//     fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);

	vd[0] = 1 | (1<<1) | (1<<3) | (1<<4) | (1<<6) | (1<<7);//14
	vd[1] = 1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) ;//15
	vd[2] = (1<<1) | (1<<2) | (1<<4) | (1<<5) | (1<<7) | (1<<8);//16
	vd[3] = (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8);//17
	vd[4] = (1<<0) | (1<<3) | (1<<6) | (1<<9) | (1<<12);//18
	vd[5] = (1<<0) | (1<<1) | (1<<2) | (1<<9) | (1<<10) | (1<<11);//19
	vd[6] = (1<<2) | (1<<5) | (1<<8) | (1<<11);//20
	vd[7] = (1<<6) | (1<<7) | (1<<8);//21
	vd[8] = (1<<0) | (1<<1) | (1<<9) | (1<<10);//22
	vd[9] = (1<<1) | (1<<2) | (1<<10) | (1<<11);//23
	vd[10] = (1<<0) | (1<<3) | (1<<9) | (1<<12);//24
	vd[11] = (1<<2) | (1<<5) | (1<<11);//25

	//for(m=0;m<12;m++)
	// fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);

	unsigned int val[26];

	fprintf(stderr,"Operating geodesic distance map ...");
//initialize bcd
	//carte dist par rap aux composantes de val zero (complementaire)

	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			memset(bcd[z][x],MAXINT,width*sizeof(unsigned int));
	fprintf(stderr,"Initialize liste...\n");
	VOXEL *vox=NULL;
	vox = fref;//liste des points de reference pour le calcul de la cd geod
	while(vox != NULL)
	{
		bcd[vox->k][vox->i][vox->j]=0;
		vox = vox->suiv;
	}
// 	for(y=0;y<width;y++)
// 	  {
// 	    if(buf0[z][x][y]==ref)
// 	      bcd[z][x][y]=0;

// 	    else
// 	      bcd[z][x][y]=MAXINT;
// 	  }






//distance transform
	change=true;
	int it=0;
	unsigned char eti;
	while(change)
	{
		change=false;
		it++;
		fprintf(stderr,"\rIteration %d forward...          ",it);

//foward scan
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
						continue;
					eti = buf0[z][x][y];
					index = 0;
					memset(val,MAXINT,26*sizeof(unsigned int));

					sum = MAXINT;
					for(m=0;m<14;m++)//
					{
						tx=mymask->mask[m].i+x;
						ty=mymask->mask[m].j+y;
						tz=mymask->mask[m].k+z;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							// sum=min(sum,(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty]);
							if(buf0[tz][tx][ty] != eti)
								continue;

							val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];

							sum = min(sum,val[m]);

							index = index | (1<<m);

						}
					}
// 	    for(m=14;m<26;m++)//
// 	      {
// 		tx=mymask->mask[m].i+x;
// 		ty=mymask->mask[m].j+y;
// 		tz=mymask->mask[m].k+z;
// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
// 		  {

// 		    if(buf0[tz][tx][ty] != eti)
// 		      continue;

// 		    val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];


// 		    index = index | (1<<m);

// 		  }
// 	      }
// 	    //calcul connexite directe elmnts 14-25
// 	    for(m=0;m<12;m++)
// 	      {
// 		conx = index & vd[m];
// 		if(conx != 0)
// 		  cnxd[m] = true;
// 		else
// 		  cnxd[m] = false;
// 	      }
					//calcul connexite indirecte elmnts 14-25
// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
// 	    cnxi[7] = cnxd[3];//21
// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
// 	    cnxi[11] = cnxd[6] || cnxd[9];//25

					//mise a jour connexite
// 	     for(m=0;m<12;m++)
// 	       cnxd[m] = cnxd[m] || cnxi[m];

// 	      //mise a jour dist pour les composantes 14-25
// 	     for(m=14;m<26;m++)
// 	       {
// 		 if(cnxd[m-14])
// 		   sum = min(sum,val[m]);
// 	       }

					if (sum < bcd[z][x][y])
					{
						change=true;
						bcd[z][x][y]=sum;
					}
				}


		//backward scan
		fprintf(stderr,"\rIteration %d backward...          ",it);
		for(z=length-1;z>=0;z--)
			for(x=height-1;x>=0;x--)
				for(y=width-1;y>=0;y--)
				{

					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
						continue;
					index = 0;
					sum = MAXINT;
					memset(val,MAXINT,26*sizeof(unsigned int));

					eti = buf0[z][x][y];
					for(m=0;m<14;m++)//
					{

						tx=x-mymask->mask[m].i;
						ty=y-mymask->mask[m].j;
						tz=z-mymask->mask[m].k;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							// sum=min(sum,(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty]);
							if(buf0[tz][tx][ty] != eti)
								continue;

							val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];

							sum = min(sum,val[m]);
							index = index | (1<<m);

						}
					}
// 	     for(m=14;m<26;m++)//
// 	      {

// 		tx=x-mymask->mask[m].i;
// 		ty=y-mymask->mask[m].j;
// 		tz=z-mymask->mask[m].k;
// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
// 		  {

// 		    if(buf0[tz][tx][ty] != eti)
// 		      continue;

// 		    val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];

// 		    index = index | (1<<m);

// 		  }
// 	      }
// 	    //calcul connexite directe elmnts 14-25
// 	      for(m=0;m<12;m++)
// 	      {
// 		conx = index & vd[m];
// 		if(conx != 0)
// 		  cnxd[m] = true;
// 		else
// 		  cnxd[m] = false;
// 	      }

					//calcul connexite indirecte elmnts 14-25
// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
// 	    cnxi[7] = cnxd[3];//21
// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
// 	    cnxi[11] = cnxd[6] || cnxd[9];//25

					//mise a jour connexite
// 	     for(m=0;m<12;m++)
// 	       cnxd[m] = cnxd[m] || cnxi[m];

// 	      //mise a jour dist pour les composantes 14-25
// 	     for(m=14;m<26;m++)
// 	       {
// 		 if(cnxd[m-14])
// 		   sum = min(sum,val[m]);
// 	       }

					if (sum < bcd[z][x][y])
					{
						change=true;
						bcd[z][x][y]=sum;
					}
				}

	}//while (change...





	delete mymask;

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}


int geodesic_distance_map(unsigned char ***buf0,unsigned short*** &bcd,int height,int width,int length,VOXEL *fref, VOXEL *lref)
//carte de dist par rapport aux points  "ref" a l'interieur de composantes non-nulles
{
	CMask *mymask=NULL;


	if((buf0 == NULL)||(bcd == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}
	if(fref == NULL)
	{
		fprintf(stderr,"\nERREUR: distance_map: liste points reference vide!\n");
		exit(1);
	}
	mymask=new CMask(3);//5-7-11 restreint (26 elmnts par demi-masque)

	if(mymask == NULL)
		return 1;


	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned short sum=MAXSHRT;
	bool change;

	//initialisation calcul connexite
	long index,conx;//32-bits
	long vd[12], vi[12];//stoquer le voisinage direct et indirect des elmnts 14-25
	bool cnxd[12],cnxi[12];

	memset(vd,0,12*sizeof(long));
	memset(vi,0,12*sizeof(long));

//   for(m=0;m<12;m++)
//     fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);

	vd[0] = 1 | (1<<1) | (1<<3) | (1<<4) | (1<<6) | (1<<7);//14
	vd[1] = 1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) ;//15
	vd[2] = (1<<1) | (1<<2) | (1<<4) | (1<<5) | (1<<7) | (1<<8);//16
	vd[3] = (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8);//17
	vd[4] = (1<<0) | (1<<3) | (1<<6) | (1<<9) | (1<<12);//18
	vd[5] = (1<<0) | (1<<1) | (1<<2) | (1<<9) | (1<<10) | (1<<11);//19
	vd[6] = (1<<2) | (1<<5) | (1<<8) | (1<<11);//20
	vd[7] = (1<<6) | (1<<7) | (1<<8);//21
	vd[8] = (1<<0) | (1<<1) | (1<<9) | (1<<10);//22
	vd[9] = (1<<1) | (1<<2) | (1<<10) | (1<<11);//23
	vd[10] = (1<<0) | (1<<3) | (1<<9) | (1<<12);//24
	vd[11] = (1<<2) | (1<<5) | (1<<11);//25

	//for(m=0;m<12;m++)
	// fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);

	unsigned short val[26];

	fprintf(stderr,"Operating geodesic distance map ...");
//initialize bcd
	//carte dist par rap aux composantes de val zero (complementaire)

	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			memset(bcd[z][x],MAXSHRT,width*sizeof(unsigned short));
	fprintf(stderr,"Initialize liste...\n");
	VOXEL *vox=NULL;
	vox = fref;//liste des points de reference pour le calcul de la cd geod
	while(vox != NULL)
	{
		bcd[vox->k][vox->i][vox->j]=0;
		vox = vox->suiv;
	}
// 	for(y=0;y<width;y++)
// 	  {
// 	    if(buf0[z][x][y]==ref)
// 	      bcd[z][x][y]=0;

// 	    else
// 	      bcd[z][x][y]=MAXSHRT;
// 	  }






//distance transform
	change=true;
	int it=0;
	unsigned char eti;
	while(change)
	{
		change=false;
		it++;
		fprintf(stderr,"\rIteration %d forward...          ",it);

//foward scan
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
						continue;
					eti = buf0[z][x][y];
					index = 0;
					memset(val,MAXSHRT,26*sizeof(unsigned short));

					sum = MAXSHRT;
					for(m=0;m<14;m++)//
					{
						tx=mymask->mask[m].i+x;
						ty=mymask->mask[m].j+y;
						tz=mymask->mask[m].k+z;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							// sum=min(sum,(unsigned short)mymask->mask[m].value+bcd[tz][tx][ty]);
							if(buf0[tz][tx][ty] != eti)
								continue;

							val[m]=(unsigned short)mymask->mask[m].value+bcd[tz][tx][ty];

							sum = min(sum,val[m]);

							index = index | (1<<m);

						}
					}
// 	    for(m=14;m<26;m++)//
// 	      {
// 		tx=mymask->mask[m].i+x;
// 		ty=mymask->mask[m].j+y;
// 		tz=mymask->mask[m].k+z;
// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
// 		  {

// 		    if(buf0[tz][tx][ty] != eti)
// 		      continue;

// 		    val[m]=(unsigned short)mymask->mask[m].value+bcd[tz][tx][ty];


// 		    index = index | (1<<m);

// 		  }
// 	      }
// 	    //calcul connexite directe elmnts 14-25
// 	    for(m=0;m<12;m++)
// 	      {
// 		conx = index & vd[m];
// 		if(conx != 0)
// 		  cnxd[m] = true;
// 		else
// 		  cnxd[m] = false;
// 	      }
					//calcul connexite indirecte elmnts 14-25
// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
// 	    cnxi[7] = cnxd[3];//21
// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
// 	    cnxi[11] = cnxd[6] || cnxd[9];//25

					//mise a jour connexite
// 	     for(m=0;m<12;m++)
// 	       cnxd[m] = cnxd[m] || cnxi[m];

// 	      //mise a jour dist pour les composantes 14-25
// 	     for(m=14;m<26;m++)
// 	       {
// 		 if(cnxd[m-14])
// 		   sum = min(sum,val[m]);
// 	       }

					if (sum < bcd[z][x][y])
					{
						change=true;
						bcd[z][x][y]=sum;
					}
				}


		//backward scan
		fprintf(stderr,"\rIteration %d backward...          ",it);
		for(z=length-1;z>=0;z--)
			for(x=height-1;x>=0;x--)
				for(y=width-1;y>=0;y--)
				{

					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
						continue;
					index = 0;
					sum = MAXSHRT;
					memset(val,MAXSHRT,26*sizeof(unsigned short));

					eti = buf0[z][x][y];
					for(m=0;m<14;m++)//
					{

						tx=x-mymask->mask[m].i;
						ty=y-mymask->mask[m].j;
						tz=z-mymask->mask[m].k;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							// sum=min(sum,(unsigned short)mymask->mask[m].value+bcd[tz][tx][ty]);
							if(buf0[tz][tx][ty] != eti)
								continue;

							val[m]=(unsigned short)mymask->mask[m].value+bcd[tz][tx][ty];

							sum = min(sum,val[m]);
							index = index | (1<<m);

						}
					}
// 	     for(m=14;m<26;m++)//
// 	      {

// 		tx=x-mymask->mask[m].i;
// 		ty=y-mymask->mask[m].j;
// 		tz=z-mymask->mask[m].k;
// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
// 		  {

// 		    if(buf0[tz][tx][ty] != eti)
// 		      continue;

// 		    val[m]=(unsigned short)mymask->mask[m].value+bcd[tz][tx][ty];

// 		    index = index | (1<<m);

// 		  }
// 	      }
// 	    //calcul connexite directe elmnts 14-25
// 	      for(m=0;m<12;m++)
// 	      {
// 		conx = index & vd[m];
// 		if(conx != 0)
// 		  cnxd[m] = true;
// 		else
// 		  cnxd[m] = false;
// 	      }

					//calcul connexite indirecte elmnts 14-25
// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
// 	    cnxi[7] = cnxd[3];//21
// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
// 	    cnxi[11] = cnxd[6] || cnxd[9];//25

					//mise a jour connexite
// 	     for(m=0;m<12;m++)
// 	       cnxd[m] = cnxd[m] || cnxi[m];

// 	      //mise a jour dist pour les composantes 14-25
// 	     for(m=14;m<26;m++)
// 	       {
// 		 if(cnxd[m-14])
// 		   sum = min(sum,val[m]);
// 	       }

					if (sum < bcd[z][x][y])
					{
						change=true;
						bcd[z][x][y]=sum;
					}
				}

	}//while (change...





	delete mymask;

	//test depassement dynamique unsigned short
	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			for(y=0;y<width;y++)
			{
				if((buf0[z][x][y]>0) && (bcd[z][x][y]==MAXSHRT))
				{
					fprintf(stderr,"\nWARNING WARNING WARNING WARNING  \n!!!!!!!!!!!!!!!------------------!!!!!!!!!!!!!\nDynamic overflow (unsigned short) in computing the geodesic distance map\n!!!!!!!!!!!!!!!------------------!!!!!!!!!!!!!\nPossible errors\n");
					break;
				}
			}

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}


//generic
//int geodesic_distance_map(unsigned char ***buf0,unsigned int*** &bcd,int height,int width,int length,FNOD *fref, FNOD *lref,int masktype)
////carte de dist par rapport aux points  "ref" a l'interieur de composantes non-nulles
//{
//	CMask *mymask=NULL;
//
//
//	if((buf0 == NULL)||(bcd == NULL))
//	{
//		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
//		exit(1);
//	}
//	if(fref == NULL)
//	{
//		fprintf(stderr,"\nERREUR: distance_map: liste points reference vide!\n");
//		exit(1);
//	}
//	mymask=new CMask(masktype);//3-> 5-7-11 restreint (26 elmnts par demi-masque)
//
//	if(mymask == NULL)
//		return 1;
//
//
//	if(mymask->support==False)
//	{
//		delete mymask;
//		return 1;}
//
//	int x,y,z,m;
//	int tx,ty,tz;
//	unsigned int sum=MAXINT;
//	bool change;
//
//	//initialisation calcul connexite
//	long index,conx;//32-bits
//	//  long vd[12], vi[12];//stoquer le voisinage direct et indirect des elmnts 14-25
//	//  bool cnxd[12],cnxi[12];
//
////   memset(vd,0,12*sizeof(long));
////   memset(vi,0,12*sizeof(long));
//
////   for(m=0;m<12;m++)
////     fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);
//
////   vd[0] = 1 | (1<<1) | (1<<3) | (1<<4) | (1<<6) | (1<<7);//14
////   vd[1] = 1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) ;//15
////   vd[2] = (1<<1) | (1<<2) | (1<<4) | (1<<5) | (1<<7) | (1<<8);//16
////   vd[3] = (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8);//17
////   vd[4] = (1<<0) | (1<<3) | (1<<6) | (1<<9) | (1<<12);//18
////   vd[5] = (1<<0) | (1<<1) | (1<<2) | (1<<9) | (1<<10) | (1<<11);//19
////   vd[6] = (1<<2) | (1<<5) | (1<<8) | (1<<11);//20
////   vd[7] = (1<<6) | (1<<7) | (1<<8);//21
////   vd[8] = (1<<0) | (1<<1) | (1<<9) | (1<<10);//22
////   vd[9] = (1<<1) | (1<<2) | (1<<10) | (1<<11);//23
////   vd[10] = (1<<0) | (1<<3) | (1<<9) | (1<<12);//24
////   vd[11] = (1<<2) | (1<<5) | (1<<11);//25
//
//	//for(m=0;m<12;m++)
//	// fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);
//
//	unsigned int val[26];
//
//	fprintf(stderr,"Operating geodesic distance map ...");
////initialize bcd
//	//carte dist par rap aux composantes de val zero (complementaire)
//
//	for(z=0;z<length;z++)
//		for(x=0;x<height;x++)
//			for(y=0;y<width;y++)
//			{
//				if(buf0[z][x][y] > 0)
//					bcd[z][x][y]=MAXINT;
//				else
//					bcd[z][x][y]=0;
//			}
//	fprintf(stderr,"Initialize liste...\n");
////    FNOD *vox=NULL;
////    TNOD *nod=NULL;
////    vox = fref;//liste des points de reference pour le calcul de la cd geod
////    while(vox != NULL)
////      {
////	nod = vox->adr;
////	if(nod != NULL)
////	  setaxiscd(nod,bcd);
////
////	 vox = vox->suiv;
////      }
//// 	for(y=0;y<width;y++)
//// 	  {
//// 	    if(buf0[z][x][y]==ref)
//// 	      bcd[z][x][y]=0;
//
//// 	    else
//// 	      bcd[z][x][y]=MAXINT;
//// 	  }
//
//
//
//
//
//
////distance transform
//	change=true;
//	int it=0;
//	unsigned char eti;
//	while(change)
//	{
//		change=false;
//		it++;
//		fprintf(stderr,"\rIteration %d forward...          ",it);
//
////foward scan
//		for(z=0;z<length;z++)
//			for(x=0;x<height;x++)
//				for(y=0;y<width;y++)
//				{
//					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
//						continue;
//					eti = buf0[z][x][y];
//					index = 0;
//					memset(val,MAXINT,26*sizeof(unsigned int));
//
//					sum = MAXINT;
//					for(m=0;m<14;m++)//
//					{
//						tx=mymask->mask[m].i+x;
//						ty=mymask->mask[m].j+y;
//						tz=mymask->mask[m].k+z;
//						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
//						{
//							// sum=min(sum,(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty]);
//							if(buf0[tz][tx][ty] != eti)
//								continue;
//
//							val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];
//
//							sum = min(sum,val[m]);
//
//							index = index | (1<<m);
//
//						}
//					}
//// 	    for(m=14;m<26;m++)//
//// 	      {
//// 		tx=mymask->mask[m].i+x;
//// 		ty=mymask->mask[m].j+y;
//// 		tz=mymask->mask[m].k+z;
//// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
//// 		  {
//
//// 		    if(buf0[tz][tx][ty] != eti)
//// 		      continue;
//
//// 		    val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];
//
//
//// 		    index = index | (1<<m);
//
//// 		  }
//// 	      }
//// 	    //calcul connexite directe elmnts 14-25
//// 	    for(m=0;m<12;m++)
//// 	      {
//// 		conx = index & vd[m];
//// 		if(conx != 0)
//// 		  cnxd[m] = true;
//// 		else
//// 		  cnxd[m] = false;
//// 	      }
//					//calcul connexite indirecte elmnts 14-25
//// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
//// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
//// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
//// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
//// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
//// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
//// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
//// 	    cnxi[7] = cnxd[3];//21
//// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
//// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
//// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
//// 	    cnxi[11] = cnxd[6] || cnxd[9];//25
//
//					//mise a jour connexite
//// 	     for(m=0;m<12;m++)
//// 	       cnxd[m] = cnxd[m] || cnxi[m];
//
//// 	      //mise a jour dist pour les composantes 14-25
//// 	     for(m=14;m<26;m++)
//// 	       {
//// 		 if(cnxd[m-14])
//// 		   sum = min(sum,val[m]);
//// 	       }
//
//					if (sum < bcd[z][x][y])
//					{
//						change=true;
//						bcd[z][x][y]=sum;
//					}
//				}
//
//
//		//backward scan
//		fprintf(stderr,"\rIteration %d backward...          ",it);
//		for(z=length-1;z>=0;z--)
//			for(x=height-1;x>=0;x--)
//				for(y=width-1;y>=0;y--)
//				{
//
//					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
//						continue;
//					index = 0;
//					sum = MAXINT;
//					memset(val,MAXINT,26*sizeof(unsigned int));
//
//					eti = buf0[z][x][y];
//					for(m=0;m<14;m++)//
//					{
//
//						tx=x-mymask->mask[m].i;
//						ty=y-mymask->mask[m].j;
//						tz=z-mymask->mask[m].k;
//						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
//						{
//							// sum=min(sum,(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty]);
//							if(buf0[tz][tx][ty] != eti)
//								continue;
//
//							val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];
//
//							sum = min(sum,val[m]);
//							index = index | (1<<m);
//
//						}
//					}
//// 	     for(m=14;m<26;m++)//
//// 	      {
//
//// 		tx=x-mymask->mask[m].i;
//// 		ty=y-mymask->mask[m].j;
//// 		tz=z-mymask->mask[m].k;
//// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
//// 		  {
//
//// 		    if(buf0[tz][tx][ty] != eti)
//// 		      continue;
//
//// 		    val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];
//
//// 		    index = index | (1<<m);
//
//// 		  }
//// 	      }
//// 	    //calcul connexite directe elmnts 14-25
//// 	      for(m=0;m<12;m++)
//// 	      {
//// 		conx = index & vd[m];
//// 		if(conx != 0)
//// 		  cnxd[m] = true;
//// 		else
//// 		  cnxd[m] = false;
//// 	      }
//
//					//calcul connexite indirecte elmnts 14-25
//// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
//// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
//// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
//// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
//// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
//// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
//// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
//// 	    cnxi[7] = cnxd[3];//21
//// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
//// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
//// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
//// 	    cnxi[11] = cnxd[6] || cnxd[9];//25
//
//					//mise a jour connexite
//// 	     for(m=0;m<12;m++)
//// 	       cnxd[m] = cnxd[m] || cnxi[m];
//
//// 	      //mise a jour dist pour les composantes 14-25
//// 	     for(m=14;m<26;m++)
//// 	       {
//// 		 if(cnxd[m-14])
//// 		   sum = min(sum,val[m]);
//// 	       }
//
//					if (sum < bcd[z][x][y])
//					{
//						change=true;
//						bcd[z][x][y]=sum;
//					}
//				}
//
//	}//while (change...
//
//
//
//
//
//	delete mymask;
//
//	fprintf(stderr,"\nend dist map.\n");
//	return 0;
//}


int geodesic_distance_map(unsigned char ***buf0,unsigned int*** &bcd,int height,int width,int length,VOXEL *fref, VOXEL *lref,int masktype)
//carte de dist par rapport aux points  "ref" a l'interieur de composantes non-nulles
{
	CMask *mymask=NULL;


	if((buf0 == NULL)||(bcd == NULL))
	{
		fprintf(stderr,"\nERREUR: distance_map: buffer(s) non-alloue(s) !\n");
		exit(1);
	}
	if(fref == NULL)
	{
		fprintf(stderr,"\nERREUR: distance_map: liste points reference vide!\n");
		exit(1);
	}
	mymask=new CMask(masktype);//3->5-7-11 restreint (26 elmnts par demi-masque)

	if(mymask == NULL)
		return 1;


	if(mymask->support==False)
	{
		delete mymask;
		return 1;}

	int x,y,z,m;
	int tx,ty,tz;
	unsigned int sum=MAXINT;
	bool change;

	//initialisation calcul connexite
	long index,conx;//32-bits
	//  long vd[12], vi[12];//stoquer le voisinage direct et indirect des elmnts 14-25
//   bool cnxd[12],cnxi[12];

//   memset(vd,0,12*sizeof(long));
//   memset(vi,0,12*sizeof(long));

//   for(m=0;m<12;m++)
//     fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);

//   vd[0] = 1 | (1<<1) | (1<<3) | (1<<4) | (1<<6) | (1<<7);//14
//   vd[1] = 1 | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) ;//15
//   vd[2] = (1<<1) | (1<<2) | (1<<4) | (1<<5) | (1<<7) | (1<<8);//16
//   vd[3] = (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8);//17
//   vd[4] = (1<<0) | (1<<3) | (1<<6) | (1<<9) | (1<<12);//18
//   vd[5] = (1<<0) | (1<<1) | (1<<2) | (1<<9) | (1<<10) | (1<<11);//19
//   vd[6] = (1<<2) | (1<<5) | (1<<8) | (1<<11);//20
//   vd[7] = (1<<6) | (1<<7) | (1<<8);//21
//   vd[8] = (1<<0) | (1<<1) | (1<<9) | (1<<10);//22
//   vd[9] = (1<<1) | (1<<2) | (1<<10) | (1<<11);//23
//   vd[10] = (1<<0) | (1<<3) | (1<<9) | (1<<12);//24
//   vd[11] = (1<<2) | (1<<5) | (1<<11);//25

	//for(m=0;m<12;m++)
	// fprintf(stderr,"vd[%d] = %x\n",m,vd[m]);

	unsigned int val[26];

	fprintf(stderr,"Operating geodesic distance map ...");
//initialize bcd
	//carte dist par rap aux composantes de val zero (complementaire)

	for(z=0;z<length;z++)
		for(x=0;x<height;x++)
			memset(bcd[z][x],MAXINT,width*sizeof(unsigned int));
	fprintf(stderr,"Initialize liste...\n");
	VOXEL *vox=NULL;
	vox = fref;//liste des points de reference pour le calcul de la cd geod
	while(vox != NULL)
	{
		bcd[vox->k][vox->i][vox->j]=0;
		vox = vox->suiv;
	}
// 	for(y=0;y<width;y++)
// 	  {
// 	    if(buf0[z][x][y]==ref)
// 	      bcd[z][x][y]=0;

// 	    else
// 	      bcd[z][x][y]=MAXINT;
// 	  }






//distance transform
	change=true;
	int it=0;
	unsigned char eti;
	while(change)
	{
		change=false;
		it++;
		fprintf(stderr,"\rIteration %d forward...          ",it);

//foward scan
		for(z=0;z<length;z++)
			for(x=0;x<height;x++)
				for(y=0;y<width;y++)
				{
					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
						continue;
					eti = buf0[z][x][y];
					index = 0;
					memset(val,MAXINT,26*sizeof(unsigned int));

					sum = MAXINT;
					for(m=0;m<14;m++)//
					{
						tx=mymask->mask[m].i+x;
						ty=mymask->mask[m].j+y;
						tz=mymask->mask[m].k+z;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							// sum=min(sum,(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty]);
							if(buf0[tz][tx][ty] != eti)
								continue;

							val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];

							sum = min(sum,val[m]);

							index = index | (1<<m);

						}
					}
// 	    for(m=14;m<26;m++)//
// 	      {
// 		tx=mymask->mask[m].i+x;
// 		ty=mymask->mask[m].j+y;
// 		tz=mymask->mask[m].k+z;
// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
// 		  {

// 		    if(buf0[tz][tx][ty] != eti)
// 		      continue;

// 		    val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];


// 		    index = index | (1<<m);

// 		  }
// 	      }
// 	    //calcul connexite directe elmnts 14-25
// 	    for(m=0;m<12;m++)
// 	      {
// 		conx = index & vd[m];
// 		if(conx != 0)
// 		  cnxd[m] = true;
// 		else
// 		  cnxd[m] = false;
// 	      }
					//calcul connexite indirecte elmnts 14-25
// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
// 	    cnxi[7] = cnxd[3];//21
// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
// 	    cnxi[11] = cnxd[6] || cnxd[9];//25

					//mise a jour connexite
// 	     for(m=0;m<12;m++)
// 	       cnxd[m] = cnxd[m] || cnxi[m];

// 	      //mise a jour dist pour les composantes 14-25
// 	     for(m=14;m<26;m++)
// 	       {
// 		 if(cnxd[m-14])
// 		   sum = min(sum,val[m]);
// 	       }

					if (sum < bcd[z][x][y])
					{
						change=true;
						bcd[z][x][y]=sum;
					}
				}


		//backward scan
		fprintf(stderr,"\rIteration %d backward...          ",it);
		for(z=length-1;z>=0;z--)
			for(x=height-1;x>=0;x--)
				for(y=width-1;y>=0;y--)
				{

					if((bcd[z][x][y]==0)||(buf0[z][x][y]==0))
						continue;
					index = 0;
					sum = MAXINT;
					memset(val,MAXINT,26*sizeof(unsigned int));

					eti = buf0[z][x][y];
					for(m=0;m<14;m++)//
					{

						tx=x-mymask->mask[m].i;
						ty=y-mymask->mask[m].j;
						tz=z-mymask->mask[m].k;
						if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
						{
							// sum=min(sum,(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty]);
							if(buf0[tz][tx][ty] != eti)
								continue;

							val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];

							sum = min(sum,val[m]);
							index = index | (1<<m);

						}
					}
// 	     for(m=14;m<26;m++)//
// 	      {

// 		tx=x-mymask->mask[m].i;
// 		ty=y-mymask->mask[m].j;
// 		tz=z-mymask->mask[m].k;
// 		if(tz>=0 && tz<length && tx>=0 && tx<height && ty>=0 && ty<width)
// 		  {

// 		    if(buf0[tz][tx][ty] != eti)
// 		      continue;

// 		    val[m]=(unsigned int)mymask->mask[m].value+bcd[tz][tx][ty];

// 		    index = index | (1<<m);

// 		  }
// 	      }
// 	    //calcul connexite directe elmnts 14-25
// 	      for(m=0;m<12;m++)
// 	      {
// 		conx = index & vd[m];
// 		if(conx != 0)
// 		  cnxd[m] = true;
// 		else
// 		  cnxd[m] = false;
// 	      }

					//calcul connexite indirecte elmnts 14-25
// 	    cnxi[0] = cnxd[1] || cnxd[3] || cnxd[4];//14
// 	    cnxi[1] = cnxd[0] || cnxd[2] || cnxd[5];//15
// 	    cnxi[2] = cnxd[1] || cnxd[3] || cnxd[6];//16
// 	    cnxi[3] = cnxd[0] || cnxd[2] || cnxd[7];//17
// 	    cnxi[4] = cnxd[0] || cnxd[10];//18
// 	    cnxi[5] = cnxd[1] || cnxd[8] || cnxd[9];//19
// 	    cnxi[6] = cnxd[2] || cnxd[11];//20
// 	    cnxi[7] = cnxd[3];//21
// 	    cnxi[8] = cnxd[10] || cnxd[5];//22
// 	    cnxi[9] = cnxd[11] || cnxd[5];//23
// 	    cnxi[10] = cnxd[8] || cnxd[4];//24
// 	    cnxi[11] = cnxd[6] || cnxd[9];//25

					//mise a jour connexite
// 	     for(m=0;m<12;m++)
// 	       cnxd[m] = cnxd[m] || cnxi[m];

// 	      //mise a jour dist pour les composantes 14-25
// 	     for(m=14;m<26;m++)
// 	       {
// 		 if(cnxd[m-14])
// 		   sum = min(sum,val[m]);
// 	       }

					if (sum < bcd[z][x][y])
					{
						change=true;
						bcd[z][x][y]=sum;
					}
				}

	}//while (change...





	delete mymask;

	fprintf(stderr,"\nend dist map.\n");
	return 0;
}

//void setaxiscd(TNOD *nod,unsigned int*** &bcd)
//{
//  if(nod != NULL)
//    {
//
//      bcd[(int)round(nod->z)][(int)round(nod->x)][(int)round(nod->y)]=0;
//      setaxiscd(nod->son,bcd);
//      setaxiscd(nod->next_b,bcd);
//    }
//}
