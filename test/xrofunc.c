
#include "nrc_types.h"

/* Driver for routine nrc_rofunc */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define SPREAD 0.05
#define NDATA 100

int ndatat; /* defining declaration */
sReal *xt, *yt, aa, abdevt; /* defining declaration */

int main ( void )
{
   long idum =( - 11 ); 
   int i; 
   sReal b, nrc_rf, *x, *y; 

   x = nrc_vector ( 1, NDATA ); 
   y = nrc_vector ( 1, NDATA ); 
   ndatat = NDATA; 
   xt = x; 
   yt = y; 
   for ( i = 1; i <= NDATA; i ++ ) {
      x[i]= 0.1*i; 
      y[i] = - 2.0*x[i]+ 1.0 + SPREAD*nrc_gasdev ( &idum ); 
   }
   printf ( "%9s %9s %12s %10s\n", "b", "a", "ROFUNC", "ABDEVT" ); 
   for ( i = - 5; i <= 5; i ++ ) {
      b = - 2.0 + 0.02*i; 
      nrc_rf = nrc_rofunc ( b ); 
      printf ( "%10.2f %9.2f %11.2f %10.2f\n", 
         b, aa, nrc_rf, abdevt ); 
   }
   nrc_free_vector ( y, 1, NDATA ); 
   nrc_free_vector ( x, 1, NDATA ); 
   return 0; 
}
#undef NRANSI
