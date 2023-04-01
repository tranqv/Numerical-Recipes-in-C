
#include "nrc_types.h"

void nrc_poldiv ( sReal u[], int n, sReal v[], int nv, sReal q[], sReal r[] )
{
   int k, j; 

   for ( j = 0; j <= n; j ++ ) {
      r[j]= u[j]; 
      q[j]= 0.0; 
   }
   for ( k = n - nv; k >= 0; k -- ) {
      q[k]= r[nv + k]/v[nv]; 
      for ( j = nv + k - 1; j >= k; j -- ) r[j] -= q[k]*v[j - k]; 
   }
   for ( j = nv; j <= n; j ++ ) r[j]= 0.0; 
}
