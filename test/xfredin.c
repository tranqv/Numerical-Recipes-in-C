
#include "nrc_types.h"

/* Driver for routine nrc_fredin */

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
   sReal a = 0.0, ans, b = PI/2.0, x, *f; 
   sReal *t, *w; 

   t = nrc_vector ( 1, N ); 
   f = nrc_vector ( 1, N ); 
   w = nrc_vector ( 1, N ); 
   nrc_fred2 ( N, a, b, t, f, w, g, ak ); 
   for ( ; ; ) {
      printf ( "Enter T between 0 and PI/2\n" ); 
      if ( scanf ( "%lf", &x ) == EOF ) break; 
      ans = nrc_fredin ( x, N, a, b, t, f, w, g, ak ); 
      printf ( "T, Calculated answer, True answer\n" ); 
      printf ( "%10.6f %10.6f %10.6f\n", x, ans, sqrt ( x ) ); 
   }
   nrc_free_vector ( w, 1, N ); 
   nrc_free_vector ( f, 1, N ); 
   nrc_free_vector ( t, 1, N ); 
   return 0; 
}
#undef NRANSI
