
#include "nrc_types.h"

/* Driver for routine nrc_stoerm */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NVAR 4
#define X1 0.0
#define HTOT 1.570796

sReal d2y1 ( sReal x )
{
   return sin ( x )+ x; 
}

sReal d2y2 ( sReal x )
{
   return cos ( x )+ x*x - 2; 
}

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   dydx[1]= x - y[1]; 
   dydx[2]= x*x - y[2]; 
}

int main ( void )
{
   int i; 
   sReal a1, a2, xf, *y, *yout, *d2y; 

   y = nrc_vector ( 1, NVAR ); 
   yout = nrc_vector ( 1, NVAR ); 
   d2y = nrc_vector ( 1, NVAR ); 
   y[1]= 0.0; 
   y[2] = - 1.0; 
   y[3]= 2.0; 
   y[4]= 0.0; 
   nrc_derivs ( X1, y, d2y ); 
   xf = X1 + HTOT; 
   a1 = d2y1 ( xf ); 
   a2 = d2y2 ( xf ); 
   printf ( "Stoermer's Rule:\n" ); 
   for ( i = 5; i <= 45; i += 10 ) {
      nrc_stoerm ( y, d2y, NVAR, X1, HTOT, i, yout, nrc_derivs ); 
      printf ( "\n%s %5.2f %s %5.2f %s %2d %s \n", 
         "x =", X1, " to ", X1 + HTOT, " in ", i, " steps" ); 
      printf ( "%14s %9s\n", "integration", "answers" ); 
      printf ( "%12.6f %12.6f\n", yout[1], a1 ); 
      printf ( "%12.6f %12.6f\n", yout[2], a2 ); 
   }
   nrc_free_vector ( d2y, 1, NVAR ); 
   nrc_free_vector ( yout, 1, NVAR ); 
   nrc_free_vector ( y, 1, NVAR ); 
   return 0; 
}
#undef NRANSI
