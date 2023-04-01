
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_mprove ( sReal **a, sReal **alud, int n, int indx[], sReal b[], sReal x[] )
{
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   int j, i; 
   dReal sdp; 
   sReal *r; 

   r = nrc_vector ( 1, n ); 
   for ( i = 1; i <= n; i ++ ) {
      sdp = - b[i]; 
      for ( j = 1; j <= n; j ++ ) sdp += a[i][j]*x[j]; 
      r[i]= sdp; 
   }
   nrc_lubksb ( alud, n, indx, r ); 
   for ( i = 1; i <= n; i ++ ) x[i] -= r[i]; 
   nrc_free_vector ( r, 1, n ); 
}
#undef NRANSI
