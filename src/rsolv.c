
#include "nrc_types.h"

void nrc_rsolv ( sReal **a, int n, sReal d[], sReal b[] )
{
   int i, j; 
   sReal sum; 

   b[n] /= d[n]; 
   for ( i = n - 1; i >= 1; i -- ) {
      for ( sum = 0.0, j = i + 1; j <= n; j ++ ) sum += a[i][j]*b[j]; 
      b[i]=( b[i]- sum )/d[i]; 
   }
}
