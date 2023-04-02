
#include "nrc_types.h"

/* Driver for routine nrc_orthog */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 64

sReal func ( sReal x )
{
   return 1.0/SQR ( 1.0 + x ); 
}

int main ( void )
{
   int i, n; 
   sReal amu0, check, xx, *a, *b, *x, *w, *anu, *alpha, *nrc_beta; 

   a = nrc_vector ( 1, NP ); 
   b = nrc_vector ( 1, NP ); 
   x = nrc_vector ( 1, NP ); 
   w = nrc_vector ( 1, NP ); 
   anu = nrc_vector ( 1, 2*NP ); 
   alpha = nrc_vector ( 1, 2*NP - 1 ); 
   nrc_beta = nrc_vector ( 1, 2*NP - 1 ); 

   /* Test with w[x] = - log x */
   for ( ; ; ) {
      printf ( "Enter N\n" ); 
      if ( scanf ( "%d", &n ) == EOF ) break; 

      if ( n < 0 ) return 1 ; 

      alpha[1]= 0.5; 
      nrc_beta[1]= 1.0; 
      for ( i = 2; i <= 2*n - 1; i ++ ) {
         alpha[i]= 0.5; 
         nrc_beta[i]= 1.0/( 4.0*( 4.0 - 1.0/( ( i - 1 )*( i - 1 ) ) ) ); 
      }
      anu[1]= 1.0; 
      anu[2] = - 0.25; 
      for ( i = 2; i <= 2*n - 1; i ++ ) anu[i + 1] = - anu[i]*i*( i - 1 )/( 2.0*( i + 1 )*( 2*i - 1 ) ); 
      nrc_orthog ( n, anu, alpha, nrc_beta, a, b ); 
      amu0 = 1.0; 
      nrc_gaucof ( n, a, b, amu0, x, w ); 
      printf ( "%3s %10s %14s\n", "#", "x ( i )", "w ( i )" ); 
      for ( i = 1; i <= n; i ++ ) printf ( "%3d %14.6e %14.6e\n", i, x[i], w[i] ); 
      for ( check = 0.0, i = 1; i <= n; i ++ ) check += w[i]; 
      printf ( "\nCheck value: %15.7e should be: %15.7e\n", check, amu0 ); 
      /* demonstrate the use of ORTHOG for an integral */
      for ( xx = 0.0, i = 1; i <= n; i ++ ) xx += w[i]*func ( x[i] ); 
      printf ( "\nIntegral from nrc_orthog: %12.6f\n", xx ); 
      printf ( "Actual value:         %12.6f\n", log ( 2.0 ) ); 
   }
   nrc_free_vector ( nrc_beta, 1, 2*NP - 1 ); 
   nrc_free_vector ( alpha, 1, 2*NP - 1 ); 
   nrc_free_vector ( anu, 1, 2*NP ); 
   nrc_free_vector ( w, 1, NP ); 
   nrc_free_vector ( x, 1, NP ); 
   nrc_free_vector ( b, 1, NP ); 
   nrc_free_vector ( a, 1, NP ); 
   return 0; 
}
#undef NRANSI
