
#include "nrc_types.h"

/* Driver for routine nrc_ftest */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 1000
#define MPTS 500
#define EPS 0.01
#define NVAL 11

int main ( void )
{
   long idum =( - 13 ); 
   int i, j; 
   sReal f, factor, prob, vrnce, *data1, *data2, *data3; 

   data1 = nrc_vector ( 1, NPTS ); 
   data2 = nrc_vector ( 1, MPTS ); 
   data3 = nrc_vector ( 1, MPTS ); 
   /* Generate two gaussian distributions with different variances */
   printf ( "\n%16s %5.2f\n", "Variance 1 = ", 1.0 ); 
   printf ( "%13s %11s %16s\n", "Variance 2", "Ratio", "Probability" ); 
   for ( j = 1; j <= NPTS; j ++ ) data1[j]= nrc_gasdev ( &idum ); 
   for ( j = 1; j <= MPTS; j ++ ) data2[j]= nrc_gasdev ( &idum ); 
   for ( i = 1; i <= NVAL; i ++ ) {
      vrnce = 1.0 +( i - 1 )*EPS; 
      factor = sqrt ( vrnce ); 
      for ( j = 1; j <= MPTS; j ++ ) data3[j]= factor*data2[j]; 
      nrc_ftest ( data1, NPTS, data3, MPTS, &f, &prob ); 
      printf ( "%11.4f %13.4f %13.4f\n", vrnce, f, prob ); 
   }
   nrc_free_vector ( data3, 1, MPTS ); 
   nrc_free_vector ( data2, 1, MPTS ); 
   nrc_free_vector ( data1, 1, NPTS ); 
   return 0; 
}
#undef NRANSI
