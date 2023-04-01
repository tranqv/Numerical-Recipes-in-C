
#include "nrc_types.h"

/* Driver for routine nrc_tutest */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 5000
#define MPTS 1000
#define EPS 0.02
#define VAR1 1.0
#define VAR2 4.0
#define NSHFT 10

int main ( void )
{
   long idum =( - 51773 ); 
   int i, j; 
   sReal fctr1, fctr2, prob, t, *data1, *data2; 

   data1 = nrc_vector ( 1, NPTS ); 
   data2 = nrc_vector ( 1, MPTS ); 
   /* Generate two gaussian distributions of different variance */
   fctr1 = sqrt ( VAR1 ); 
   for ( i = 1; i <= NPTS; i ++ ) data1[i]= fctr1*nrc_gasdev ( &idum ); 
   fctr2 = sqrt ( VAR2 ); 
   for ( i = 1; i <= MPTS; i ++ )
      data2[i]= NSHFT/2.0*EPS + fctr2*nrc_gasdev ( &idum ); 
   printf ( "\nDistribution #1 : variance = %6.2f\n", VAR1 ); 
   printf ( "Distribution #2 : variance = %6.2f\n\n", VAR2 ); 
   printf ( "%7s %8s %16s\n", "shift", "t", "probability" ); 
   for ( i = 1; i <= NSHFT + 1; i ++ ) {
      nrc_tutest ( data1, NPTS, data2, MPTS, &t, &prob ); 
      printf ( "%6.2f %10.2f %11.2f\n", ( i - 1 )*EPS, t, prob ); 
      for ( j = 1; j <= NPTS; j ++ ) data1[j] += EPS; 
   }
   nrc_free_vector ( data2, 1, MPTS ); 
   nrc_free_vector ( data1, 1, NPTS ); 
   return 0; 
}
#undef NRANSI
