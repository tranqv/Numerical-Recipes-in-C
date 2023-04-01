
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define MF 4
#define BI (1.0/256)

void nrc_mpinv ( unsigned char u[], unsigned char v[], int n, int m )
{
   void nrc_mpmov ( unsigned char u[], unsigned char v[], int n ); 
   void nrc_mpmul ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
      int m ); 
   void nrc_mpneg ( unsigned char u[], int n ); 
   unsigned char *rr, *s; 
   int i, j, maxmn, mm; 
   sReal fu, fv; 

   maxmn = IMAX ( n, m ); 
   rr = nrc_cvector ( 1, 1 +( maxmn << 1 ) ); 
   s = nrc_cvector ( 1, maxmn ); 
   mm = IMIN ( MF, m ); 
   fv =( sReal ) v[mm]; 
   for ( j = mm - 1; j >= 1; j -- ) {
      fv *= BI; 
      fv += v[j]; 
   }
   fu = 1.0/fv; 
   for ( j = 1; j <= n; j ++ ) {
      i =( int ) fu; 
      u[j]=( unsigned char ) i; 
      fu = 256.0*( fu - i ); 
   }
   for ( ; ; ) {
      nrc_mpmul ( rr, u, v, n, m ); 
      nrc_mpmov ( s, &rr[1], n ); 
      nrc_mpneg ( s, n ); 
      s[1] -= 254; 
      nrc_mpmul ( rr, s, u, n, n ); 
      nrc_mpmov ( u, &rr[1], n ); 
      for ( j = 2; j < n; j ++ )
         if ( s[j] ) break; 
      if ( j == n ) {
         nrc_free_cvector ( s, 1, maxmn ); 
         nrc_free_cvector ( rr, 1, 1 +( maxmn << 1 ) ); 
         return; 
      }
   }
}
#undef MF
#undef BI
#undef NRANSI
