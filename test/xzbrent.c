
#include "nrc_types.h"

/* Driver for routine nrc_zbrent */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 100
#define NBMAX 20
#define X1 1.0
#define X2 50.0

static sReal fx ( sReal x )
{
   return nrc_bessj0 ( x ); 
}

int main ( void )
{
   int i, nb = NBMAX; 
   sReal tol, root, *xb1, *xb2; 

   xb1 = nrc_vector ( 1, NBMAX ); 
   xb2 = nrc_vector ( 1, NBMAX ); 
   nrc_zbrak ( fx, X1, X2, N, xb1, xb2, &nb ); 
   printf ( "\nRoots of nrc_bessj0:\n" ); 
   printf ( "%21s %15s\n", "x", "f ( x )" ); 
   for ( i = 1; i <= nb; i ++ ) {
      tol =( 1.0e-6 )*( xb1[i]+ xb2[i] )/2.0; 
      root = nrc_zbrent ( fx, xb1[i], xb2[i], tol ); 
      printf ( "root %3d %14.6f %14.6f\n", i, root, fx ( root ) ); 
   }
   nrc_free_vector ( xb2, 1, NBMAX ); 
   nrc_free_vector ( xb1, 1, NBMAX ); 
   return 0; 
}
#undef NRANSI
