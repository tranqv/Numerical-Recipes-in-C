
#include "nrc_types.h"

/* Driver for routine nrc_midpnt */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define NMAX 10

/* Test function */
sReal func ( sReal x )
{
   return 1.0/sqrt ( x ); 
}

/* Integral of test function */
sReal fint ( sReal x )
{
   return 2.0*sqrt ( x ); 
}

int main ( void )
{
   sReal a = 0.0, b = 1.0, s; 
   int i; 

   printf ( "\nIntegral of func computed with MIDPNT\n" ); 
   printf ( "Actual value of integral is %7.4f\n", ( fint ( b )- fint ( a ) ) ); 
   printf ( "%6s %29s \n", "n", "Approx. integral" ); 
   for ( i = 1; i <= NMAX; i ++ ) {
      s = nrc_midpnt ( func, a, b, i ); 
      printf ( "%6d %24.6f\n", i, s ); 
   }
   return 0; 
}
#undef NRANSI
