
#include "nrc_types.h"

/* Driver for routine nrc_polcoe */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 4
#define PI 3.1415926

int main ( void )
{
   int i, j, nfunc; 
   sReal f, sum, x, *coeff, *xa, *ya; 

   coeff = nrc_vector ( 0, NP ); 
   xa = nrc_vector ( 0, NP ); 
   ya = nrc_vector ( 0, NP ); 
   for ( nfunc = 1; nfunc <= 2; nfunc ++ ) {
      if ( nfunc == 1 ) {
         printf ( "sine function from 0 to PI\n\n" ); 
         for ( i = 0; i <= NP; i ++ ) {
            xa[i]=( i + 1 )*PI/( NP + 1 ); 
            ya[i]= sin ( xa[i] ); 
         }
      } else if ( nfunc == 2 ) {
         printf ( "exponential function from 0 to 1\n\n" ); 
         for ( i = 0; i <= NP; i ++ ) {
            xa[i]= 1.0*( i + 1 )/( NP + 1 ); 
            ya[i]= exp ( xa[i] ); 
         }
      } else {
         break; 
      }
      nrc_polcoe ( xa, ya, NP, coeff ); 
      printf ( "  coefficients\n" ); 
      for ( i = 0; i <= NP; i ++ ) printf ( "%12.6f", coeff[i] ); 
      printf ( "\n\n%9s %13s %15s\n", "x", "f ( x )", "polynomial" ); 
      for ( i = 1; i <= 10; i ++ ) {
         if ( nfunc == 1 ) {
            x =( - 0.05 + i/10.0 )*PI; 
            f = sin ( x ); 
         } else if ( nfunc == 2 ) {
            x = - 0.05 + i/10.0; 
            f = exp ( x ); 
         }
         sum = coeff[NP]; 
         for ( j = NP - 1; j >= 0; j -- )
            sum = coeff[j]+ sum*x; 
         printf ( "%12.6f %12.6f %12.6f\n", x, f, sum ); 
      }
      printf ( "\n************************************\n" ); 
      printf ( "press RETURN\n" ); 
      ( void ) getchar (  ); 
   }
   nrc_free_vector ( ya, 0, NP ); 
   nrc_free_vector ( xa, 0, NP ); 
   nrc_free_vector ( coeff, 0, NP ); 
   return 0; 
}
#undef NRANSI
