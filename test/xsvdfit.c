
#include "nrc_types.h"

/* Driver for routine nrc_svdfit */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPT 100
#define SPREAD 0.02
#define NPOL 5

int main ( void )
{
   long idum =( - 911 ); 
   int i; 
   sReal chisq, *x, *y, *sig, *a, *w, **cvm, **u, **v; 

   x = nrc_vector ( 1, NPT ); 
   y = nrc_vector ( 1, NPT ); 
   sig = nrc_vector ( 1, NPT ); 
   a = nrc_vector ( 1, NPOL ); 
   w = nrc_vector ( 1, NPOL ); 
   cvm = nrc_matrix ( 1, NPOL, 1, NPOL ); 
   u = nrc_matrix ( 1, NPT, 1, NPOL ); 
   v = nrc_matrix ( 1, NPOL, 1, NPOL ); 
   for ( i = 1; i <= NPT; i ++ ) {
      x[i]= 0.02*i; 
      y[i]= 1.0 + x[i]*( 2.0 + x[i]*( 3.0 + x[i]*( 4.0 + x[i]*5.0 ) ) ); 
      y[i] *= ( 1.0 + SPREAD*nrc_gasdev ( &idum ) ); 
      sig[i]= y[i]*SPREAD; 
   }
   nrc_svdfit ( x, y, sig, NPT, a, NPOL, u, v, w, &chisq, nrc_fpoly ); 
   nrc_svdvar ( v, NPOL, w, cvm ); 
   printf ( "\npolynomial nrc_fit:\n\n" ); 
   for ( i = 1; i <= NPOL; i ++ )
      printf ( "%12.6f %s %10.6f\n", a[i], "  +-", sqrt ( cvm[i][i] ) ); 
   printf ( "\nChi - squared %12.6f\n", chisq ); 
   nrc_svdfit ( x, y, sig, NPT, a, NPOL, u, v, w, &chisq, nrc_fleg ); 
   nrc_svdvar ( v, NPOL, w, cvm ); 
   printf ( "\nLegendre polynomial nrc_fit:\n\n" ); 
   for ( i = 1; i <= NPOL; i ++ )
      printf ( "%12.6f %s %10.6f\n", a[i], "  +-", sqrt ( cvm[i][i] ) ); 
   printf ( "\nChi - squared %12.6f\n", chisq ); 
   nrc_free_matrix ( v, 1, NPOL, 1, NPOL ); 
   nrc_free_matrix ( u, 1, NPT, 1, NPOL ); 
   nrc_free_matrix ( cvm, 1, NPOL, 1, NPOL ); 
   nrc_free_vector ( w, 1, NPOL ); 
   nrc_free_vector ( a, 1, NPOL ); 
   nrc_free_vector ( sig, 1, NPT ); 
   nrc_free_vector ( y, 1, NPT ); 
   nrc_free_vector ( x, 1, NPT ); 
   return 0; 
}
#undef NRANSI
