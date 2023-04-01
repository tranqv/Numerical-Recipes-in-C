
#include "nrc_types.h"

/* Driver for routine nrc_chint */

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

sReal fint ( sReal x )
{
   return 4.0*x*( x*x - 7.0 )*sin ( x )-( x*x*( x*x - 14.0 )+ 28.0 )*cos ( x ); 
}

int main ( void )
{
   int i, mval; 
   sReal a =( - PIO2 ), b = PIO2, x; 
   sReal c[NVAL], cint[NVAL]; 

   nrc_chebft ( a, b, c, NVAL, func ); 
   /* test integral */
   for ( ; ;  ) {
      printf ( "\nHow many terms in Chebyshev evaluation?\n" ); 
      printf ( "Enter n between 6 and %2d. ( n = 0 to end ).\n", NVAL ); 
      scanf ( "%d", &mval ); 
      if ( ( mval <= 0 ) || ( mval > NVAL ) ) break; 
      nrc_chint ( a, b, c, cint, mval ); 
      printf ( "\n%9s %14s %16s\n", "x", "actual", "Cheby. integ." ); 
      for ( i = - 8; i <= 8; i ++ ) {
         x = i*PIO2/10.0; 
         printf ( "%12.6f %12.6f %12.6f\n", 
            x, fint ( x )- fint ( - PIO2 ), nrc_chebev ( a, b, cint, mval, x ) ); 
      }
   }
   return 0; 
}
#undef NRANSI
