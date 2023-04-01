
#include "nrc_types.h"

/* Driver for routine nrc_amoeba */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MP 4
#define NP 3
#define FTOL 1.0e-6

sReal func ( sReal x[] )
{
   return 0.6 - nrc_bessj0 ( SQR ( x[1]- 0.5 )+ SQR ( x[2]- 0.6 )+ SQR ( x[3]- 0.7 ) ); 
}

int main ( void )
{
   int i, nfunc, j, ndim = NP; 
   sReal *x, *y, **p; 

   x = nrc_vector ( 1, NP ); 
   y = nrc_vector ( 1, MP ); 
   p = nrc_matrix ( 1, MP, 1, NP ); 
   for ( i = 1; i <= MP; i ++ ) {
      for ( j = 1; j <= NP; j ++ )
         x[j]= p[i][j]=( i == ( j + 1 ) ? 1.0 : 0.0 ); 
      y[i]= func ( x ); 
   }
   nrc_amoeba ( p, y, ndim, FTOL, func, &nfunc ); 
   printf ( "\nNumber of function evaluations: %3d\n", nfunc ); 
   printf ( "Vertices of final 3 - d simplex and\n" ); 
   printf ( "function values at the vertices:\n\n" ); 
   printf ( "%3s %10s %12s %12s %14s\n\n", 
      "i", "x[i]", "y[i]", "z[i]", "function" ); 
   for ( i = 1; i <= MP; i ++ ) {
      printf ( "%3d ", i ); 
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.6f ", p[i][j] ); 
      printf ( "%12.6f\n", y[i] ); 
   }
   printf ( "\nTrue minimum is at ( 0.5, 0.6, 0.7 )\n" ); 
   nrc_free_matrix ( p, 1, MP, 1, NP ); 
   nrc_free_vector ( y, 1, MP ); 
   nrc_free_vector ( x, 1, NP ); 
   return 0; 
}
#undef NRANSI
