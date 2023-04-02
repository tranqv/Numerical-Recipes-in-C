
#include "nrc_types.h"

/* Driver for routine nrc_gauher */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 64
#define SQRTPI 1.7724539

sReal func ( sReal x )
{
   return cos ( x ); 
}

int main ( void )
{
   int i, n; 
   sReal check, xx, *x, *w; 

   x = nrc_vector ( 1, NP ); 
   w = nrc_vector ( 1, NP ); 
   for ( ; ; ) {
      printf ( "Enter N\n" ); 
      if ( scanf ( "%d", &n ) == EOF ) break; 

      if ( n < 0 ) return 1; 

      nrc_gauher ( x, w, n ); 
      printf ( "%3s %10s %14s\n", "#", "x ( i )", "w ( i )" ); 
      for ( i = 1; i <= n; i ++ ) printf ( "%3d %14.6e %14.6e\n", i, x[i], w[i] ); 
      for ( check = 0.0, i = 1; i <= n; i ++ ) check += w[i]; 
      printf ( "\nCheck value: %15.7e should be: %15.7e\n", check, SQRTPI ); 
      /* demonstrate the use of GAUHER for an integral */
      for ( xx = 0.0, i = 1; i <= n; i ++ ) xx += w[i]*func ( x[i] ); 
      printf ( "\nIntegral from nrc_gauher: %12.6f\n", xx ); 
      printf ( "Actual value:         %12.6f\n", SQRTPI*exp ( - 0.25 ) ); 
   }
   nrc_free_vector ( w, 1, NP ); 
   nrc_free_vector ( x, 1, NP ); 
   return 0; 
}
#undef NRANSI
