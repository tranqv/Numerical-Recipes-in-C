
#include "nrc_types.h"

/* Driver for routine nrc_fred2 */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 8
#define PI 3.141592653589793238462643383279502884197

sReal g ( sReal t )
{
   return sqrt ( t )- pow ( PI/2.0, 2.25 )*pow ( t, 0.75 )/2.25; 
}

sReal ak ( sReal t, sReal s )
{
   return pow ( t*s, 0.75 ); 
}

int main ( void )
{
   int i; 
   sReal a = 0.0, b = PI/2.0, *f; 
   sReal *t, *w; 

   t = nrc_vector ( 1, N ); 
   f = nrc_vector ( 1, N ); 
   w = nrc_vector ( 1, N ); 
   nrc_fred2 ( N, a, b, t, f, w, g, ak ); 
   /* Compare with exact solution */
   printf ( "Abscissa, Calc soln, True soln\n" ); 
   for ( i = 1; i <= N; i ++ ) printf ( "%10.6f %10.6f %10.6f\n", t[i], f[i], sqrt ( t[i] ) ); 
   nrc_free_vector ( w, 1, N ); 
   nrc_free_vector ( f, 1, N ); 
   nrc_free_vector ( t, 1, N ); 
   return 0; 
}
#undef NRANSI
