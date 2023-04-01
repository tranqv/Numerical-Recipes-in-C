
#include "nrc_types.h"

/* Driver for routine nrc_irbit1 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define NBIN 15
#define NTRIES 10000

int main ( void )
{
   int i, iflg, ipts = 0, j, n; 
   unsigned long iseed = 12345; 
   sReal twoinv, delay[NBIN + 1]; 

   /* Calculate distribution of runs of zeros */
   for ( i = 1; i <= NBIN; i ++ ) delay[i]= 0.0; 
   printf ( "distribution of runs of n zeros\n" ); 
   printf ( "%6s %22s %18s\n", "n", "probability", "expected" ); 
   for ( i = 1; i <= NTRIES; i ++ ) {
      if ( nrc_irbit1 ( &iseed ) == 1 ) {
         ++ ipts; 
         iflg = 0; 
         for ( j = 1; j <= NBIN; j ++ ) {
            if ( ( nrc_irbit1 ( &iseed ) == 1 ) && ( iflg == 0 ) ) {
               iflg = 1; 
               ++ delay[j]; 
            }
         }
      }
   }
   twoinv = 0.5; 
   for ( n = 1; n <= NBIN; n ++ ) {
      printf ( "%6d %19.4f %20.4f\n", 
         ( n - 1 ), delay[n]/ipts, twoinv ); 
      twoinv /= 2.0; 
   }
   return 0; 
}
#undef NRANSI
