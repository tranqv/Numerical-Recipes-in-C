
#include "nrc_types.h"

/* Driver for routine nrc_tptest */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 500
#define EPS 0.01
#define NSHFT 11
#define ANOISE 0.3

int main ( void )
{
   long idum =( - 5 ); 
   int i, j; 
   sReal ave1, ave2, ave3; 
   sReal offset, prob1, prob2, shift, t1, t2; 
   sReal var1, var2, var3, *data1, *data2, *data3; 

   data1 = nrc_vector ( 1, NPTS ); 
   data2 = nrc_vector ( 1, NPTS ); 
   data3 = nrc_vector ( 1, NPTS ); 
   printf ( "%29s %31s\n", "Correlated:", "Uncorrelated:" ); 
   printf ( "%7s %11s %17s %11s %17s\n", 
      "Shift", "t", "Probability", "t", "Probability" ); 
   offset =( NSHFT/2 )*EPS; 
   for ( j = 1; j <= NPTS; j ++ ) {
      data1[j]= nrc_gasdev ( &idum ); 
      data2[j]= data1[j]+ ANOISE*nrc_gasdev ( &idum ); 
      data3[j]= nrc_gasdev ( &idum ); 
      data3[j] += ANOISE*nrc_gasdev ( &idum ); 
   }
   nrc_avevar ( data1, NPTS, &ave1, &var1 ); 
   nrc_avevar ( data2, NPTS, &ave2, &var2 ); 
   nrc_avevar ( data3, NPTS, &ave3, &var3 ); 
   for ( j = 1; j <= NPTS; j ++ ) {
      data1[j] -= ave1 - offset; 
      data2[j] -= ave2; 
      data3[j] -= ave3; 
   }
   for ( i = 1; i <= NSHFT; i ++ ) {
      shift = i*EPS; 
      for ( j = 1; j <= NPTS; j ++ ) {
         data2[j] += EPS; 
         data3[j] += EPS; 
      }
      nrc_tptest ( data1, data2, NPTS, &t1, &prob1 ); 
      nrc_tptest ( data1, data3, NPTS, &t2, &prob2 ); 
      printf ( "%6.2f %14.4f %12.4f %16.4f %12.4f\n", 
         shift, t1, prob1, t2, prob2 ); 
   }
   nrc_free_vector ( data3, 1, NPTS ); 
   nrc_free_vector ( data2, 1, NPTS ); 
   nrc_free_vector ( data1, 1, NPTS ); 
   return 0; 
}
#undef NRANSI
