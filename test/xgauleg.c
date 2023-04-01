
#include "nrc_types.h"

/* Driver for routine nrc_gauleg */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPOINT 10
#define X1 0.0
#define X2 1.0
#define X3 10.0

sReal func ( sReal x )
{
   return x*exp ( - x ); 
}

int main ( void )
{
   int i; 
   sReal xx = 0.0; 
   sReal *x, *w; 

   x = nrc_vector ( 1, NPOINT ); 
   w = nrc_vector ( 1, NPOINT ); 
   nrc_gauleg ( X1, X2, x, w, NPOINT ); 
   printf ( "\n%2s %10s %12s\n", "#", "x[i]", "w[i]" ); 
   for ( i = 1; i <= NPOINT; i ++ )
      printf ( "%2d %12.6f %12.6f\n", i, x[i], w[i] ); 
   /* Demonstrate the use of nrc_gauleg for integration */
   nrc_gauleg ( X1, X3, x, w, NPOINT ); 
   for ( i = 1; i <= NPOINT; i ++ )
      xx += ( w[i]*func ( x[i] ) ); 
   printf ( "\nIntegral from GAULEG: %12.6f\n", xx ); 
   printf ( "Actual value: %12.6f\n", 
      ( 1.0 + X1 )*exp ( - X1 )-( 1.0 + X3 )*exp ( - X3 ) ); 
   nrc_free_vector ( w, 1, NPOINT ); 
   nrc_free_vector ( x, 1, NPOINT ); 
   return 0; 
}
#undef NRANSI
