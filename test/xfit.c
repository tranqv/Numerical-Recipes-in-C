
#include "nrc_types.h"

/* Driver for routine nrc_fit */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPT 100
#define SPREAD 0.5

int main ( void )
{
   long idum =( - 117 ); 
   int i, mwt; 
   sReal a, b, chi2, q, siga, sigb, *x, *y, *sig; 

   x = nrc_vector ( 1, NPT ); 
   y = nrc_vector ( 1, NPT ); 
   sig = nrc_vector ( 1, NPT ); 
   for ( i = 1; i <= NPT; i ++ ) {
      x[i]= 0.1*i; 
      y[i] = - 2.0*x[i]+ 1.0 + SPREAD*nrc_gasdev ( &idum ); 
      sig[i]= SPREAD; 
   }
   for ( mwt = 0; mwt <= 1; mwt ++ ) {
      nrc_fit ( x, y, NPT, sig, mwt, &a, &b, &siga, &sigb, &chi2, &q ); 
      if ( mwt == 0 )
         printf ( "\nIgnoring standard deviations\n" ); 
      else
         printf ( "\nIncluding standard deviations\n" ); 
      printf ( "%12s %9.6f %18s %9.6f \n", 
         "a =  ", a, "uncertainty:", siga ); 
      printf ( "%12s %9.6f %18s %9.6f \n", 
         "b =  ", b, "uncertainty:", sigb ); 
      printf ( "%19s %14.6f \n", "chi - squared: ", chi2 ); 
      printf ( "%23s %10.6f \n", "goodness - of - nrc_fit: ", q ); 
   }
   nrc_free_vector ( sig, 1, NPT ); 
   nrc_free_vector ( y, 1, NPT ); 
   nrc_free_vector ( x, 1, NPT ); 
   return 0; 
}
#undef NRANSI
