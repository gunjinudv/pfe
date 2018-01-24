#ifndef _MATALLOC
#define _MATALLOC

void *** mat3Dalloc(unsigned int m_type,int Depth,int Haut,int Larg);
void ** mat2Dalloc(unsigned int m_type,int Haut,int Larg);
void  mat3Dfree(void*** &buf,int Depth,int Haut,int Larg);
void  mat2Dfree(void** &buf,int Haut,int Larg);
#endif
