
#include "nrc_types.h"

/* Driver for routine nrc_gaujac */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 64
#define PIBY2 1.5707963267948966192313216916397514420986

sReal func ( sReal ak, sReal x )
{
   return 1.0/sqrt ( 1.0 - ak*ak*( 1.0 + x )/2.0 ); 
}

int main ( void )
{
   int i, n; 
   sReal ak, alf =( - 0.5 ), bet =( - 0.5 ), checkw, checkx, xx, *x, *w; 

   x = nrc_vector ( 1, NP ); 
   w = nrc_vector ( 1, NP ); 
   for ( ; ; ) {
      printf ( "Enter N\n" ); 
      if ( scanf ( "%d", &n ) == EOF ) break; 

      if ( n < 0 ) return 1; 

      nrc_gaujac ( x, w, n, alf, bet ); 
      printf ( "%3s %10s %14s\n", "#", "x ( i )", "w ( i )" ); 
      for ( i = 1; i <= n; i ++ ) printf ( "%3d %14.6e %14.6e\n", i, x[i], w[i] ); 
      checkx = checkw = 0.0; 
      for ( i = 1; i <= n; i ++ ) {
         checkx += x[i]; 
         checkw += w[i]; 
      }
      printf ( "\nCheck value: %15.7e should be: %15.7e\n", 
         checkx, n*( bet - alf )/( alf + bet + 2*n ) ); 
      printf ( "\nCheck value: %15.7e should be: %15.7e\n", 
         checkw, exp ( nrc_gammln ( 1.0 + alf )+ nrc_gammln ( 1.0 + bet )-
         nrc_gammln ( 2.0 + alf + bet ) )*pow ( 2.0, alf + bet + 1.0 ) ); 
      /* demonstrate the use of GAUJAC for an integral */
      ak = 0.5; 
      for ( xx = 0.0, i = 1; i <= n; i ++ ) xx += w[i]*func ( ak, x[i] ); 
      printf ( "\nIntegral from nrc_gaujac: %12.6f\n", xx ); 
      printf ( "Actual value:         %12.6f\n", 2.0*nrc_ellf ( PIBY2, ak ) ); 
   }
   nrc_free_vector ( w, 1, NP ); 
   nrc_free_vector ( x, 1, NP ); 
   return 0; 
}
#undef NRANSI
