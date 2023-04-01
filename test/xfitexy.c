
#include "nrc_types.h"

/* Driver for routine nrc_fitexy */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPT 30

int main ( void )
{
   long idum =( - 1 ); 
   int j; 
   sReal a, b, chi2, q, sa, sb, siga, sigb; 
   sReal *x, *y, *dx, *dy, *dz; 

   x = nrc_vector ( 1, NPT ); 
   y = nrc_vector ( 1, NPT ); 
   dx = nrc_vector ( 1, NPT ); 
   dy = nrc_vector ( 1, NPT ); 
   dz = nrc_vector ( 1, NPT ); 
   for ( j = 1; j <= NPT; j ++ ) {
      dx[j]= 0.1 + nrc_ran1 ( &idum ); 
      dy[j]= 0.1 + nrc_ran1 ( &idum ); 
      dz[j]= 0.0; 
      x[j]= 10.0 + 10.0*nrc_gasdev ( &idum ); 
      y[j]= 2.0*x[j]- 5.0 + dy[j]*nrc_gasdev ( &idum ); 
      x[j] += dx[j]*nrc_gasdev ( &idum ); 
   }
   printf ( "Values of a, b, siga, sigb, chi2, q:\n" ); 
   printf ( "Fit with x and y errors gives:\n" ); 
   nrc_fitexy ( x, y, NPT, dx, dy, &a, &b, &siga, &sigb, &chi2, &q ); 
   printf ( "%11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n\n", 
      a, b, siga, sigb, chi2, q ); 
   printf ( "Setting x errors to zero gives:\n" ); 
   nrc_fitexy ( x, y, NPT, dz, dy, &a, &b, &siga, &sigb, &chi2, &q ); 
   printf ( "%11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n", 
      a, b, siga, sigb, chi2, q ); 
   printf ( "...to be compared with nrc_fit result:\n" ); 
   nrc_fit ( x, y, NPT, dy, 1, &a, &b, &siga, &sigb, &chi2, &q ); 
   printf ( "%11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n\n", 
      a, b, siga, sigb, chi2, q ); 
   printf ( "Setting y errors to zero gives:\n" ); 
   nrc_fitexy ( x, y, NPT, dx, dz, &a, &b, &siga, &sigb, &chi2, &q ); 
   printf ( "%11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n", 
      a, b, siga, sigb, chi2, q ); 
   printf ( "...to be compared with nrc_fit result:\n" ); 
   nrc_fit ( y, x, NPT, dx, 1, &a, &b, &siga, &sigb, &chi2, &q ); 
   sa = sqrt ( siga*siga + SQR ( sigb*( a/b ) ) )/b; 
   sb = sigb/( b*b ); 
   printf ( "%11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n", 
      - a/b, 1.0/b, sa, sb, chi2, q ); 
   nrc_free_vector ( dz, 1, NPT ); 
   nrc_free_vector ( dy, 1, NPT ); 
   nrc_free_vector ( dx, 1, NPT ); 
   nrc_free_vector ( y, 1, NPT ); 
   nrc_free_vector ( x, 1, NPT ); 
   return 0; 
}
#undef NRANSI
