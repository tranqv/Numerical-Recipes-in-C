
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define M 64
#define NDFT 1024
#define MPOL 6
#define TWOPI (2.0*3.141592653589793238462643383279502884197)

void nrc_dftint ( sReal ( *func )( sReal ), sReal a, sReal b, sReal w, sReal *cosint, 
   sReal *sinint )
{
   void nrc_dftcor ( sReal w, sReal delta, sReal a, sReal b, sReal endpts[], 
      sReal *corre, sReal *corim, sReal *corfac ); 
   void nrc_polint ( sReal xa[], sReal ya[], int n, sReal x, sReal *y, sReal *dy ); 
   void nrc_realft ( sReal data[], unsigned long n, int isign ); 
   static int init = 0; 
   int j, nn; 
   static sReal aold = - 1.e30, bold = - 1.e30, delta, ( *funcold )( sReal ); 
   static sReal data[NDFT + 1], endpts[9]; 
   sReal c, cdft, cerr, corfac, corim, corre, en, s; 
   sReal sdft, serr, *cpol, *spol, *xpol; 

   cpol = nrc_vector ( 1, MPOL ); 
   spol = nrc_vector ( 1, MPOL ); 
   xpol = nrc_vector ( 1, MPOL ); 
   if ( init != 1 || a != aold || b != bold || func != funcold ) {
      init = 1; 
      aold = a; 
      bold = b; 
      funcold = func; 
      delta =( b - a )/M; 
      for ( j = 1; j <= M + 1; j ++ )
         data[j]=( *func )( a +( j - 1 )*delta ); 
      for ( j = M + 2; j <= NDFT; j ++ )
         data[j]= 0.0; 
      for ( j = 1; j <= 4; j ++ ) {
         endpts[j]= data[j]; 
         endpts[j + 4]= data[M - 3 + j]; 
      }
      nrc_realft ( data, NDFT, 1 ); 
      data[2]= 0.0; 
   }
   en = w*delta*NDFT/TWOPI + 1.0; 
   nn = IMIN ( IMAX ( ( int )( en - 0.5*MPOL + 1.0 ), 1 ), NDFT/2 - MPOL + 1 ); 
   for ( j = 1; j <= MPOL; j ++, nn ++ ) {
      cpol[j]= data[2*nn - 1]; 
      spol[j]= data[2*nn]; 
      xpol[j]= nn; 
   }
   nrc_polint ( xpol, cpol, MPOL, en, &cdft, &cerr ); 
   nrc_polint ( xpol, spol, MPOL, en, &sdft, &serr ); 
   nrc_dftcor ( w, delta, a, b, endpts, &corre, &corim, &corfac ); 
   cdft *= corfac; 
   sdft *= corfac; 
   cdft += corre; 
   sdft += corim; 
   c = delta*cos ( w*a ); 
   s = delta*sin ( w*a ); 
   *cosint = c*cdft - s*sdft; 
   *sinint = s*cdft + c*sdft; 
   nrc_free_vector ( cpol, 1, MPOL ); 
   nrc_free_vector ( spol, 1, MPOL ); 
   nrc_free_vector ( xpol, 1, MPOL ); 
}
#undef M
#undef NDFT
#undef MPOL
#undef TWOPI
#undef NRANSI
