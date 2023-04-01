
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_vander ( dReal x[], dReal w[], dReal q[], int n )
{
   int i, j, k; 
   dReal b, s, t, xx; 
   dReal *c; 

   c = nrc_dvector ( 1, n ); 
   if ( n == 1 ) w[1]= q[1]; 
   else {
      for ( i = 1; i <= n; i ++ ) c[i]= 0.0; 
      c[n] = - x[1]; 
      for ( i = 2; i <= n; i ++ ) {
         xx = - x[i]; 
         for ( j =( n + 1 - i ); j <=( n - 1 ); j ++ ) c[j] += xx*c[j + 1]; 
         c[n] += xx; 
      }
      for ( i = 1; i <= n; i ++ ) {
         xx = x[i]; 
         t = b = 1.0; 
         s = q[n]; 
         for ( k = n; k >= 2; k -- ) {
            b = c[k]+ xx*b; 
            s += q[k - 1]*b; 
            t = xx*t + b; 
         }
         w[i]= s/t; 
      }
   }
   nrc_free_dvector ( c, 1, n ); 
}
#undef NRANSI
