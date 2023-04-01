
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_dsvbksb ( dReal **u, dReal w[], dReal **v, int m, int n, dReal b[], dReal x[] )
{
   int jj, j, i; 
   dReal s, *tmp; 

   tmp = nrc_dvector ( 1, n ); 
   for ( j = 1; j <= n; j ++ ) {
      s = 0.0; 
      if ( w[j] ) {
         for ( i = 1; i <= m; i ++ ) s += u[i][j]*b[i]; 
         s /= w[j]; 
      }
      tmp[j]= s; 
   }
   for ( j = 1; j <= n; j ++ ) {
      s = 0.0; 
      for ( jj = 1; jj <= n; jj ++ ) s += v[j][jj]*tmp[jj]; 
      x[j]= s; 
   }
   nrc_free_dvector ( tmp, 1, n ); 
}
#undef NRANSI
