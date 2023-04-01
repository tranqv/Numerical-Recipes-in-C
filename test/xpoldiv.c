
#include "nrc_types.h"

/* Driver for routine nrc_poldiv */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 5
#define NV 3

int main ( void )
{
   int i; 
   static sReal u[N + 1]={- 1.0, 5.0, - 10.0, 10.0, - 5.0, 1.0}; 
   static sReal v[NV + 1]={1.0, 3.0, 3.0, 1.0}; 
   sReal *q, *r; 

   q = nrc_vector ( 0, N ); 
   r = nrc_vector ( 0, N ); 
   nrc_poldiv ( u, N, v, NV, q, r ); 
   printf ( "\n%10s %10s %10s %10s %10s %10s\n\n", 
      "x^0", "x^1", "x^2", "x^3", "x^4", "x^5" ); 
   printf ( "quotient polynomial coefficients:\n" ); 
   for ( i = 0; i <= 5; i ++ ) printf ( "%10.2f ", q[i] ); 
   printf ( "\nexpected quotient coefficients:\n" ); 
   printf ( "%10.2f %10.2f %10.2f %10.2f %10.2f %10.2f\n\n", 
      31.0, - 8.0, 1.0, 0.0, 0.0, 0.0 ); 
   printf ( "remainder polynomial coefficients:\n" ); 
   for ( i = 0; i <= 3; i ++ ) printf ( "%10.2f ", r[i] ); 
   printf ( "\nexpected remainder coefficients:\n" ); 
   printf ( "%10.2f %10.2f %10.2f %10.2f\n", - 32.0, - 80.0, - 80.0, 0.0 ); 
   nrc_free_vector ( r, 0, N ); 
   nrc_free_vector ( q, 0, N ); 
   return 0; 
}
#undef NRANSI
