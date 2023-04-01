
#include "nrc_types.h"

/* Driver for routine nrc_anneal */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NCITY 10

int main ( void )
{
   int i, ii, *iorder; 
   long idum =( - 111 ); 
   sReal *x, *y; 

   iorder = nrc_ivector ( 1, NCITY ); 
   x = nrc_vector ( 1, NCITY ); 
   y = nrc_vector ( 1, NCITY ); 
   for ( i = 1; i <= NCITY; i ++ ) {
      x[i]= nrc_ran3 ( &idum ); 
      y[i]= nrc_ran3 ( &idum ); 
      iorder[i]= i; 
   }
   nrc_anneal ( x, y, iorder, NCITY ); 
   printf ( "*** System Frozen ***\n" ); 
   printf ( "Final path:\n" ); 
   printf ( "%8s %9s %12s\n", "city", "x", "y" ); 
   for ( i = 1; i <= NCITY; i ++ ) {
      ii = iorder[i]; 
      printf ( "%4d %10.4f %10.4f\n", ii, x[ii], y[ii] ); 
   }
   nrc_free_vector ( y, 1, NCITY ); 
   nrc_free_vector ( x, 1, NCITY ); 
   nrc_free_ivector ( iorder, 1, NCITY ); 
   return 0; 
}
#undef NRANSI
