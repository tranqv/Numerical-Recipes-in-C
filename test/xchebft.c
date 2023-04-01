
#include "nrc_types.h"

/* Driver for routine nrc_chebft */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define NVAL 40
#define PIO2 1.5707963267948966192313216916397514420986

sReal func ( sReal x )
{
   return x*x*( x*x - 2.0 )*sin ( x ); 
}

int main ( void )
{
   sReal a =( - PIO2 ), b = PIO2, dum, f; 
   sReal t0, t1, term, x, y, c[NVAL]; 
   int i, j, mval; 

   nrc_chebft ( a, b, c, NVAL, func ); 
   /* test result */
   for ( ; ;  ) {
      printf ( "\nHow many terms in Chebyshev evaluation?\n" ); 
      printf ( "Enter n between 6 and %2d. ( n = 0 to end ).\n", NVAL ); 
      scanf ( "%d", &mval ); 
      if ( ( mval <= 0 ) || ( mval > NVAL ) ) break; 
      printf ( "\n%9s %14s %16s\n", "x", "actual", "chebyshev nrc_fit" ); 
      for ( i = - 8; i <= 8; i ++ ) {
         x = i*PIO2/10.0; 
         y =( x - 0.5*( b + a ) )/( 0.5*( b - a ) ); 
         /* Evaluate Chebyshev polynomial without CHEBEV */
         t0 = 1.0; 
         t1 = y; 
         f = c[1]*t1 + c[0]*0.5; 
         for ( j = 2; j < mval; j ++ ) {
            dum = t1; 
            t1 = 2.0*y*t1 - t0; 
            t0 = dum; 
            term = c[j]*t1; 
            f += term; 
         }
         printf ( "%12.6f %12.6f %12.6f\n", x, func ( x ), f ); 
      }
   }
   return 0; 
}
#undef NRANSI
