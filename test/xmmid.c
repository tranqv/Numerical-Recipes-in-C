
#include "nrc_types.h"

/* Driver for routine nrc_mmid */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NVAR 4
#define X1 1.0
#define HTOT 0.5

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   dydx[1] = - y[2]; 
   dydx[2]= y[1]-( 1.0/x )*y[2]; 
   dydx[3]= y[2]-( 2.0/x )*y[3]; 
   dydx[4]= y[3]-( 3.0/x )*y[4]; 
}

int main ( void )
{
   int i; 
   sReal b1, b2, b3, b4, xf = X1 + HTOT, *y, *yout, *dydx; 

   y = nrc_vector ( 1, NVAR ); 
   yout = nrc_vector ( 1, NVAR ); 
   dydx = nrc_vector ( 1, NVAR ); 
   y[1]= nrc_bessj0 ( X1 ); 
   y[2]= nrc_bessj1 ( X1 ); 
   y[3]= nrc_bessj ( 2, X1 ); 
   y[4]= nrc_bessj ( 3, X1 ); 
   nrc_derivs ( X1, y, dydx ); 
   b1 = nrc_bessj0 ( xf ); 
   b2 = nrc_bessj1 ( xf ); 
   b3 = nrc_bessj ( 2, xf ); 
   b4 = nrc_bessj ( 3, xf ); 
   printf ( "First four Bessel functions:\n" ); 
   for ( i = 5; i <= 50; i += 5 ) {
      nrc_mmid ( y, dydx, NVAR, X1, HTOT, i, yout, nrc_derivs ); 
      printf ( "\n%s %5.2f %s %5.2f %s %2d %s \n", 
         "x =", X1, " to ", X1 + HTOT, " in ", i, " steps" ); 
      printf ( "%14s %9s\n", "integration", "nrc_bessj" ); 
      printf ( "%12.6f %12.6f\n", yout[1], b1 ); 
      printf ( "%12.6f %12.6f\n", yout[2], b2 ); 
      printf ( "%12.6f %12.6f\n", yout[3], b3 ); 
      printf ( "%12.6f %12.6f\n", yout[4], b4 ); 
      printf ( "\nPress RETURN to continue...\n" ); 
      ( void ) getchar ( ); 
   }
   nrc_free_vector ( dydx, 1, NVAR ); 
   nrc_free_vector ( yout, 1, NVAR ); 
   nrc_free_vector ( y, 1, NVAR ); 
   return 0; 
}
#undef NRANSI
