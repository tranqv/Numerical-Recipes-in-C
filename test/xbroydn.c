
#include "nrc_types.h"

/* Driver for routine nrc_broydn */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

void funcv ( int n, sReal x[], sReal f[] )
{
   f[1]= SQR ( x[1] )+ SQR ( x[2] )- 2.0; 
   f[2]= exp ( x[1]- 1.0 )+ x[2]*SQR ( x[2] )- 2.0; 
}

#define N 2

int main ( void )
{
   int i, check; 
   sReal *x, *f; 

   x = nrc_vector ( 1, N ); 
   f = nrc_vector ( 1, N ); 
   x[1]= 2.0; 
   x[2]= 0.5; 
   nrc_broydn ( x, N, &check, funcv ); 
   funcv ( N, x, f ); 
   if ( check ) printf ( "Convergence problems.\n" ); 
   printf ( "%7s %3s %12s\n", "Index", "x", "f" ); 
   for ( i = 1; i <= N; i ++ ) printf ( "%5d %12.6f %12.6f\n", i, x[i], f[i] ); 
   nrc_free_vector ( f, 1, N ); 
   nrc_free_vector ( x, 1, N ); 
   return 0; 
}
#undef NRANSI
