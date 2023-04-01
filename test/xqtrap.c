
#include "nrc_types.h"

/* Driver for routine nrc_qtrap */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define PIO2 1.5707963267948966192313216916397514420986

/* Test function */
sReal func ( sReal x )
{
   return x*x*( x*x - 2.0 )*sin ( x ); 
}

/* Integral of test function */
sReal fint ( sReal x )
{
   return 4.0*x*( x*x - 7.0 )*sin ( x )-( pow ( x, 4.0 )- 14.0*x*x + 28.0 )*cos ( x ); 
}

int main ( void )
{
   sReal a = 0.0, b = PIO2, s; 

   printf ( "Integral of func computed with QTRAP\n\n" ); 
   printf ( "Actual value of integral is %12.6f\n", fint ( b )- fint ( a ) ); 
   s = nrc_qtrap ( func, a, b ); 
   printf ( "Result from routine QTRAP is %12.6f\n", s ); 
   return 0; 
}
#undef NRANSI
