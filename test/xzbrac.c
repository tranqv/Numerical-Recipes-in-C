
#include "nrc_types.h"

/* Driver for routine nrc_zbrac */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

static sReal fx ( sReal x )
{
   return nrc_bessj0 ( x ); 
}

int main ( void )
{
   int succes, i; 
   sReal x1, x2; 

   printf ( "%21s %23s\n", "bracketing values:", "function values:" ); 
   printf ( "%6s %10s %21s %12s\n", "x1", "x2", "nrc_bessj0 ( x1 )", "nrc_bessj0 ( x2 )" ); 
   for ( i = 1; i <= 10; i ++ ) {
      x1 = i; 
      x2 = x1 + 1.0; 
      succes = nrc_zbrac ( fx, &x1, &x2 ); 
      if ( succes ) {
         printf ( "%7.2f %10.2f %6s %12.6f %12.6f \n", 
            x1, x2, " ", fx ( x1 ), fx ( x2 ) ); 
      }
   }
   return 0; 
}
#undef NRANSI
