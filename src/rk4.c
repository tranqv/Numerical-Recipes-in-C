
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_rk4 ( sReal y[], sReal dydx[], int n, sReal x, sReal h, sReal yout[], 
   void ( *nrc_derivs )( sReal, sReal [], sReal [] ) )
{
   int i; 
   sReal xh, hh, h6, *dym, *dyt, *yt; 

   dym = nrc_vector ( 1, n ); 
   dyt = nrc_vector ( 1, n ); 
   yt = nrc_vector ( 1, n ); 
   hh = h*0.5; 
   h6 = h/6.0; 
   xh = x + hh; 
   for ( i = 1; i <= n; i ++ ) yt[i]= y[i]+ hh*dydx[i]; 
   ( *nrc_derivs )( xh, yt, dyt ); 
   for ( i = 1; i <= n; i ++ ) yt[i]= y[i]+ hh*dyt[i]; 
   ( *nrc_derivs )( xh, yt, dym ); 
   for ( i = 1; i <= n; i ++ ) {
      yt[i]= y[i]+ h*dym[i]; 
      dym[i] += dyt[i]; 
   }
   ( *nrc_derivs )( x + h, yt, dyt ); 
   for ( i = 1; i <= n; i ++ )
      yout[i]= y[i]+ h6*( dydx[i]+ dyt[i]+ 2.0*dym[i] ); 
   nrc_free_vector ( yt, 1, n ); 
   nrc_free_vector ( dyt, 1, n ); 
   nrc_free_vector ( dym, 1, n ); 
}
#undef NRANSI
