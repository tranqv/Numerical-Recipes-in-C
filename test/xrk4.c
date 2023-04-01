
#include "nrc_types.h"

/* Driver for routine nrc_rk4 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 4

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   dydx[1] = - y[2]; 
   dydx[2]= y[1]-( 1.0/x )*y[2]; 
   dydx[3]= y[2]-( 2.0/x )*y[3]; 
   dydx[4]= y[3]-( 3.0/x )*y[4]; 
}

int main ( void )
{
   int i, j; 
   sReal h, x = 1.0, *y, *dydx, *yout; 

   y = nrc_vector ( 1, N ); 
   dydx = nrc_vector ( 1, N ); 
   yout = nrc_vector ( 1, N ); 
   y[1]= nrc_bessj0 ( x ); 
   y[2]= nrc_bessj1 ( x ); 
   y[3]= nrc_bessj ( 2, x ); 
   y[4]= nrc_bessj ( 3, x ); 
   nrc_derivs ( x, y, dydx ); 
   printf ( "\n%16s %5s %12s %12s %12s\n", 
      "Bessel function:", "j0", "j1", "j3", "j4" ); 
   for ( i = 1; i <= 5; i ++ ) {
      h = 0.2*i; 
      nrc_rk4 ( y, dydx, N, x, h, yout, nrc_derivs ); 
      printf ( "\nfor a step size of: %6.2f\n", h ); 
      printf ( "%12s", "nrc_rk4:" ); 
      for ( j = 1; j <= 4; j ++ ) printf ( " %12.6f", yout[j] ); 
      printf ( "\n%12s %12.6f %12.6f %12.6f %12.6f\n", "actual:", 
         nrc_bessj0 ( x + h ), nrc_bessj1 ( x + h ), nrc_bessj ( 2, x + h ), nrc_bessj ( 3, x + h ) ); 
   }
   nrc_free_vector ( yout, 1, N ); 
   nrc_free_vector ( dydx, 1, N ); 
   nrc_free_vector ( y, 1, N ); 
   return 0; 
}
#undef NRANSI
