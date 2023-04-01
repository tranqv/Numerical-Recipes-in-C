
#include "nrc_types.h"

/* Driver for routine nrc_irbit2 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define NBIN 15
#define NTRIES 10000

static unsigned long twoton[16]={0x1L, 0x2L, 0x4L, 0x8L, 0x10L, 0x20L, 0x40L, 0x80L, 
   0x100L, 0x200L, 0x400L, 0x800L, 0x1000L, 0x2000L, 0x4000L, 0x8000L}; 

int main ( void )
{
   int i, iflg, ipts = 0, j, n; 
   unsigned long iseed = 111; 
   sReal delay[NBIN + 1]; 

   /* Calculate distribution of runs of zeros */
   for ( i = 1; i <= NBIN; i ++ ) delay[i]= 0.0; 
   for ( i = 1; i <= NTRIES; i ++ ) {
      if ( nrc_irbit2 ( &iseed ) == 1 ) {
         ++ ipts; 
         iflg = 0; 
         for ( j = 1; j <= NBIN; j ++ ) {
            if ( ( nrc_irbit2 ( &iseed ) == 1 ) && ( iflg == 0 ) ) {
               iflg = 1; 
               ++ delay[j]; 
            }
         }
      }
   }
   printf ( "distribution of runs of n zeros\n" ); 
   printf ( "%6s %22s %18s \n", "n", "probability", "expected" ); 
   for ( n = 1; n <= NBIN; n ++ )
      printf ( "%6d %19.4f %20.4f\n", 
         ( n - 1 ), delay[n]/ipts, 1.0/( dReal ) twoton[n] ); 
   return 0; 
}
#undef NRANSI
