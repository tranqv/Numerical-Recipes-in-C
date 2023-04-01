
#include "nrc_types.h"

/* Driver for routine nrc_simpr */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NVAR 3
#define X1 0.0
#define HTOT 50.0

int main ( void )
{
   int i; 
   sReal a1 = 0.5976, a2 = 1.4023, a3 = 0.0, *y, *yout, *dfdx, **dfdy, *dydx; 

   y = nrc_vector ( 1, NVAR ); 
   yout = nrc_vector ( 1, NVAR ); 
   dfdx = nrc_vector ( 1, NVAR ); 
   dfdy = nrc_matrix ( 1, NVAR, 1, NVAR ); 
   dydx = nrc_vector ( 1, NVAR ); 
   y[1]= y[2]= 1.0; 
   y[3]= 0.0; 
   nrc_derivs ( X1, y, dydx ); 
   nrc_jacobn ( X1, y, dfdx, dfdy, NVAR ); 
   printf ( "Test Problem:\n" ); 
   for ( i = 5; i <= 50; i += 5 ) {
      nrc_simpr ( y, dydx, dfdx, dfdy, NVAR, X1, HTOT, i, yout, nrc_derivs ); 
      printf ( "\n%s %5.2f %s %5.2f %s %2d %s \n", 
         "x =", X1, " to ", X1 + HTOT, " in ", i, " steps" ); 
      printf ( "%14s %9s\n", "integration", "nrc_bessj" ); 
      printf ( "%12.6f %12.6f\n", yout[1], a1 ); 
      printf ( "%12.6f %12.6f\n", yout[2], a2 ); 
      printf ( "%12.6f %12.6f\n", yout[3], a3 ); 
   }
   nrc_free_vector ( dydx, 1, NVAR ); 
   nrc_free_matrix ( dfdy, 1, NVAR, 1, NVAR ); 
   nrc_free_vector ( dfdx, 1, NVAR ); 
   nrc_free_vector ( yout, 1, NVAR ); 
   nrc_free_vector ( y, 1, NVAR ); 
   return 0; 
}
#undef NRANSI
