
#include "nrc_types.h"

/* Driver for routine nrc_trapzd */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define NMAX 14
#define PIO2 1.5707963267948966192313216916397514420986

/* Test function */
sReal func ( sReal x )
{
   return ( x*x )*( x*x - 2.0 )*sin ( x ); 
}

/* Integral of test function */
sReal fint ( sReal x )
{
   return 4.0*x*( x*x - 7.0 )*sin ( x )-( pow ( x, 4.0 )- 14.0*( x*x )+ 28.0 )*cos ( x ); 
}

int main ( void )
{
   int i; 
   sReal a = 0.0, b = PIO2, s; 

   printf ( "\nIntegral of func with 2^( n - 1 ) points\n" ); 
   printf ( "Actual value of integral is %10.6f\n", fint ( b )- fint ( a ) ); 
   printf ( "%6s %24s\n", "n", "approx. integral" ); 
   for ( i = 1; i <= NMAX; i ++ ) {
      s = nrc_trapzd ( func, a, b, i ); 
      printf ( "%6d %20.6f\n", i, s ); 
   }
   return 0; 
}
#undef NRANSI
