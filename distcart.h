#ifndef DISTCARTHEADER
#define DISTCARTHEADER


class CHAMFER {
public:
  int nbvois;
  int *posi, *posj, *val;
CHAMFER(int type);
~CHAMFER();
};

  
  
void  distcart(GImage *Iin, int** &buf,unsigned char val_obj);
int**  geodistcart(GImage *Iin, int **buf_in,unsigned char val_obj);
int**  topodistcart(GImage *Iin, GImage *Imsk,unsigned char val_obj);
int**  compodistcart(GImage *Iin, int **buf_in,int **b_dist,unsigned char val_obj);
int**  sumdistcart(GImage *Iin1,GImage *Iin2, unsigned char val_ref1,unsigned char val_ref2);
#endif
