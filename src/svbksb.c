
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_svbksb ( sReal **u, sReal w[], sReal **v, int m, int n, sReal b[], sReal x[] )
{
   int jj, j, i; 
   sReal s, *tmp; 

   tmp = nrc_vector ( 1, n ); 
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
   nrc_free_vector ( tmp, 1, n ); 
}
#undef NRANSI
