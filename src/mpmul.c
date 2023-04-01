
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define RX 256.0

void nrc_mpmul ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
   int m )
{
   void nrc_drealft ( dReal data[], unsigned long n, int isign ); 
   int j, mn, nn = 1; 
   dReal cy, t, *a, *b; 

   mn = IMAX ( m, n ); 
   while ( nn < mn ) nn <<= 1; 
   nn <<= 1; 
   a = nrc_dvector ( 1, nn ); 
   b = nrc_dvector ( 1, nn ); 
   for ( j = 1; j <= n; j ++ )
      a[j]=( dReal ) u[j]; 
   for ( j = n + 1; j <= nn; j ++ ) a[j]= 0.0; 
   for ( j = 1; j <= m; j ++ )
      b[j]=( dReal ) v[j]; 
   for ( j = m + 1; j <= nn; j ++ ) b[j]= 0.0; 
   nrc_drealft ( a, nn, 1 ); 
   nrc_drealft ( b, nn, 1 ); 
   b[1] *= a[1]; 
   b[2] *= a[2]; 
   for ( j = 3; j <= nn; j += 2 ) {
      b[j]=( t = b[j] )*a[j]- b[j + 1]*a[j + 1]; 
      b[j + 1]= t*a[j + 1]+ b[j + 1]*a[j]; 
   }
   nrc_drealft ( b, nn, - 1 ); 
   cy = 0.0; 
   for ( j = nn; j >= 1; j -- ) {
      t = b[j]/( nn >> 1 )+ cy + 0.5; 
      cy =( unsigned long ) ( t/RX ); 
      b[j]= t - cy*RX; 
   }
   if ( cy >= RX ) nrc_error ( "cannot happen in fftmul" ); 
   w[1]=( unsigned char ) cy; 
   for ( j = 2; j <= n + m; j ++ )
      w[j]=( unsigned char ) b[j - 1]; 
   nrc_free_dvector ( b, 1, nn ); 
   nrc_free_dvector ( a, 1, nn ); 
}
#undef RX
#undef NRANSI
