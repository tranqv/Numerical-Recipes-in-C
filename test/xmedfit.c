
#include "nrc_types.h"

/* Driver for routine nrc_medfit */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPT 100
#define SPREAD 0.1
#define NDATA NPT

int main ( void )
{
   long idum =( - 1984 ); 
   int i, mwt = 1; 
   sReal a, abdev, b, chi2, q, siga, sigb; 
   sReal *x, *y, *sig; 

   x = nrc_vector ( 1, NDATA ); 
   y = nrc_vector ( 1, NDATA ); 
   sig = nrc_vector ( 1, NDATA ); 
   for ( i = 1; i <= NPT; i ++ ) {
      x[i]= 0.1*i; 
      y[i] = - 2.0*x[i]+ 1.0 + SPREAD*nrc_gasdev ( &idum ); 
      sig[i]= SPREAD; 
   }
   nrc_fit ( x, y, NPT, sig, mwt, &a, &b, &siga, &sigb, &chi2, &q ); 
   printf ( "\nAccording to routine FIT the result is:\n" ); 
   printf ( "   a =  %8.4f   uncertainty:  %8.4f\n", a, siga ); 
   printf ( "   b =  %8.4f   uncertainty:  %8.4f\n", b, sigb ); 
   printf ( "   chi - squared:  %8.4f  for  %4d  points\n", chi2, NPT ); 
   printf ( "   goodness - of - nrc_fit:  %8.4f\n", q ); 
   printf ( "\nAccording to routine MEDFIT the result is:\n" ); 
   nrc_medfit ( x, y, NPT, &a, &b, &abdev ); 
   printf ( "   a =  %8.4f\n", a ); 
   printf ( "   b =  %8.4f\n", b ); 
   printf ( "   absolute deviation ( per data point ): %8.4f\n", abdev ); 
   printf ( "   ( note: gaussian SPREAD is %8.4f )\n", SPREAD ); 
   nrc_free_vector ( sig, 1, NDATA ); 
   nrc_free_vector ( y, 1, NDATA ); 
   nrc_free_vector ( x, 1, NDATA ); 
   return 0; 
}
#undef NRANSI
