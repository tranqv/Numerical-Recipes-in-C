
#include "nrc_types.h"

/* Driver for routine nrc_chstwo */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NBINS 10
#define NPTS 2000

int main ( void )
{
   long idum =( - 17 ); 
   int i, ibin, j; 
   sReal chsq, df, prob, x, *bins1, *bins2; 

   bins1 = nrc_vector ( 1, NBINS ); 
   bins2 = nrc_vector ( 1, NBINS ); 
   for ( j = 1; j <= NBINS; j ++ ) {
      bins1[j]= 0.0; 
      bins2[j]= 0.0; 
   }
   for ( i = 1; i <= NPTS; i ++ ) {
      x = nrc_expdev ( &idum ); 
      ibin =( int ) ( x*NBINS/3.0 + 1 ); 
      if ( ibin <= NBINS ) ++ bins1[ibin]; 
      x = nrc_expdev ( &idum ); 
      ibin =( int ) ( x*NBINS/3.0 + 1 ); 
      if ( ibin <= NBINS ) ++ bins2[ibin]; 
   }
   nrc_chstwo ( bins1, bins2, NBINS, 0, &df, &chsq, &prob ); 
   printf ( "\n%15s %15s\n", "dataset 1", "dataset 2" ); 
   for ( i = 1; i <= NBINS; i ++ )
      printf ( "%13.2f %15.2f\n", bins1[i], bins2[i] ); 
   printf ( "\n%18s %12.4f\n", "chi - squared:", chsq ); 
   printf ( "%18s %12.4f\n", "probability:", prob ); 
   nrc_free_vector ( bins2, 1, NBINS ); 
   nrc_free_vector ( bins1, 1, NBINS ); 
   return 0; 
}
#undef NRANSI
