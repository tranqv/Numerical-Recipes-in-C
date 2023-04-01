
#include "nrc_types.h"

#define LOBYTE(x) ((unsigned char) ((x) & 0xff))
#define HIBYTE(x) ((unsigned char) ((x) >> 8 & 0xff))


void nrc_mpadd ( unsigned char w[], unsigned char u[], unsigned char v[], int n )
{
   int j; 
   unsigned short ireg = 0; 

   for ( j = n; j >= 1; j -- ) {
      ireg = u[j]+ v[j]+ HIBYTE ( ireg ); 
      w[j + 1]= LOBYTE ( ireg ); 
   }
   w[1]= HIBYTE ( ireg ); 
}

void nrc_mpsub ( int *is, unsigned char w[], unsigned char u[], unsigned char v[], 
   int n )
{
   int j; 
   unsigned short ireg = 256; 

   for ( j = n; j >= 1; j -- ) {
      ireg = 255 + u[j]- v[j]+ HIBYTE ( ireg ); 
      w[j]= LOBYTE ( ireg ); 
   }
   *is = HIBYTE ( ireg )- 1; 
}

void nrc_mpsad ( unsigned char w[], unsigned char u[], int n, int iv )
{
   int j; 
   unsigned short ireg; 

   ireg = 256*iv; 
   for ( j = n; j >= 1; j -- ) {
      ireg = u[j]+ HIBYTE ( ireg ); 
      w[j + 1]= LOBYTE ( ireg ); 
   }
   w[1]= HIBYTE ( ireg ); 
}

void nrc_mpsmu ( unsigned char w[], unsigned char u[], int n, int iv )
{
   int j; 
   unsigned short ireg = 0; 

   for ( j = n; j >= 1; j -- ) {
      ireg = u[j]*iv + HIBYTE ( ireg ); 
      w[j + 1]= LOBYTE ( ireg ); 
   }
   w[1]= HIBYTE ( ireg ); 
}

void nrc_mpsdv ( unsigned char w[], unsigned char u[], int n, int iv, int *ir )
{
   int i, j; 

   *ir = 0; 
   for ( j = 1; j <= n; j ++ ) {
      i = 256*( *ir )+ u[j]; 
      w[j]=( unsigned char ) ( i/iv ); 
      *ir = i % iv; 
   }
}

void nrc_mpneg ( unsigned char u[], int n )
{
   int j; 
   unsigned short ireg = 256; 

   for ( j = n; j >= 1; j -- ) {
      ireg = 255 - u[j]+ HIBYTE ( ireg ); 
      u[j]= LOBYTE ( ireg ); 
   }
}

void nrc_mpmov ( unsigned char u[], unsigned char v[], int n )
{
   int j; 

   for ( j = 1; j <= n; j ++ ) u[j]= v[j]; 
}

void nrc_mplsh ( unsigned char u[], int n )
{
   int j; 

   for ( j = 1; j <= n; j ++ ) u[j]= u[j + 1]; 
}
#undef LOBYTE
#undef HIBYTE
