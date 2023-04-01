
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define MF 3
#define BI (1.0/256)

void nrc_mpsqrt ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
   int m )
{
   void nrc_mplsh ( unsigned char u[], int n ); 
   void nrc_mpmov ( unsigned char u[], unsigned char v[], int n ); 
   void nrc_mpmul ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
      int m ); 
   void nrc_mpneg ( unsigned char u[], int n ); 
   void nrc_mpsdv ( unsigned char w[], unsigned char u[], int n, int iv, int *ir ); 
   int i, ir, j, mm; 
   sReal fu, fv; 
   unsigned char *r, *s; 

   r = nrc_cvector ( 1, n << 1 ); 
   s = nrc_cvector ( 1, n << 1 ); 
   mm = IMIN ( m, MF ); 
   fv =( sReal ) v[mm]; 
   for ( j = mm - 1; j >= 1; j -- ) {
      fv *= BI; 
      fv += v[j]; 
   }
   fu = 1.0/sqrt ( fv ); 
   for ( j = 1; j <= n; j ++ ) {
      i =( int ) fu; 
      u[j]=( unsigned char ) i; 
      fu = 256.0*( fu - i ); 
   }
   for ( ; ; ) {
      nrc_mpmul ( r, u, u, n, n ); 
      nrc_mplsh ( r, n ); 
      nrc_mpmul ( s, r, v, n, IMIN ( m, n ) ); 
      nrc_mplsh ( s, n ); 
      nrc_mpneg ( s, n ); 
      s[1] -= 253; 
      nrc_mpsdv ( s, s, n, 2, &ir ); 
      for ( j = 2; j < n; j ++ ) {
         if ( s[j] ) {
            nrc_mpmul ( r, s, u, n, n ); 
            nrc_mpmov ( u, &r[1], n ); 
            break; 
         }
      }
      if ( j < n ) continue; 
      nrc_mpmul ( r, u, v, n, IMIN ( m, n ) ); 
      nrc_mpmov ( w, &r[1], n ); 
      nrc_free_cvector ( s, 1, n << 1 ); 
      nrc_free_cvector ( r, 1, n << 1 ); 
      return; 
   }
}
#undef MF
#undef BI
#undef NRANSI
