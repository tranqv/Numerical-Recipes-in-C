
#include "nrc_types.h"

/* Driver for routine nrc_zrhqr */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define M 4     /* degree of polynomial */
#define MP1 (M+1)   /* no. of polynomial coefficients */

int main ( void )
{
   static sReal a[MP1]={- 1.0, 0.0, 0.0, 0.0, 1.0}; 
   sReal *rti, *rtr; 
   int i; 

   rti = nrc_vector ( 1, M ); 
   rtr = nrc_vector ( 1, M ); 
   printf ( "\nRoots of polynomial x^4 - 1\n" ); 
   printf ( "\n%15s %15s\n", "Real", "nrc_cmplx" ); 
      nrc_zrhqr ( a, M, rtr, rti ); 
      for ( i = 1; i <= M; i ++ ) {
         printf ( "%5d %12.6f %12.6f\n", i, rtr[i], rti[i] ); 
      }
   nrc_free_vector ( rtr, 1, M ); 
   nrc_free_vector ( rti, 1, M ); 
   return 0; 
}
#undef NRANSI
