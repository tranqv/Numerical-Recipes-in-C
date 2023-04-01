
#include "nrc_types.h"

/* Driver for routine nrc_ttest */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 1024
#define MPTS 512
#define EPS 0.02
#define NSHFT 10

int main ( void )
{
   long idum =( - 5 ); 
   int i, j; 
   sReal prob, t, *data1, *data2; 

   data1 = nrc_vector ( 1, NPTS ); 
   data2 = nrc_vector ( 1, MPTS ); 
   /* Generate gaussian distributed data */
   printf ( "%6s %8s %16s\n", "shift", "t", "probability" ); 
   for ( i = 1; i <= NPTS; i ++ ) data1[i]= nrc_gasdev ( &idum ); 
   for ( i = 1; i <= MPTS; i ++ ) data2[i]=( NSHFT/2.0 )*EPS + nrc_gasdev ( &idum ); 
   for ( i = 1; i <= NSHFT + 1; i ++ ) {
      nrc_ttest ( data1, NPTS, data2, MPTS, &t, &prob ); 
      printf ( "%6.2f %10.2f %10.2f\n", ( i - 1 )*EPS, t, prob ); 
      for ( j = 1; j <= NPTS; j ++ ) data1[j] += EPS; 
   }
   nrc_free_vector ( data2, 1, MPTS ); 
   nrc_free_vector ( data1, 1, NPTS ); 
   return 0; 
}
#undef NRANSI
