
#include "nrc_types.h"

/* Driver for routine nrc_ksone */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 1000
#define EPS 0.1

sReal func ( sReal x )
{
   return 1.0 - nrc_erfcc ( x/sqrt ( 2.0 ) ); 
}

int main ( void )
{
   long idum =( - 5 ); 
   int i, j; 
   sReal d, factr, prob, varnce, *data; 

   data = nrc_vector ( 1, NPTS ); 
   printf ( "%19s %16s %15s\n\n", 
      "variance ratio", "k - s statistic", "probability" ); 
   for ( i = 1; i <= 11; i ++ ) {
      varnce = 1.0 +( i - 1 )*EPS; 
      factr = sqrt ( varnce ); 
      for ( j = 1; j <= NPTS; j ++ )
         data[j]= factr*fabs ( nrc_gasdev ( &idum ) ); 
      nrc_ksone ( data, NPTS, func, &d, &prob ); 
      printf ( "%16.6f %16.6f %16.6f \n", varnce, d, prob ); 
   }
   nrc_free_vector ( data, 1, NPTS ); 
   return 0; 
}
#undef NRANSI
