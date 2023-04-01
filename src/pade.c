
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define BIG    1.0e30

void nrc_pade ( dReal cof[], int n, sReal *nrc_resid )
{
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d ); 
   void nrc_mprove ( sReal **a, sReal **alud, int n, int indx[], sReal b[], 
      sReal x[] ); 
   int j, k, *indx; 
   sReal d, rr, rrold, sum, **q, **qlu, *x, *y, *z; 

   indx = nrc_ivector ( 1, n ); 
   q = nrc_matrix ( 1, n, 1, n ); 
   qlu = nrc_matrix ( 1, n, 1, n ); 
   x = nrc_vector ( 1, n ); 
   y = nrc_vector ( 1, n ); 
   z = nrc_vector ( 1, n ); 
   for ( j = 1; j <= n; j ++ ) {
      y[j]= x[j]= cof[n + j]; 
      for ( k = 1; k <= n; k ++ ) {
         q[j][k]= cof[j - k + n]; 
         qlu[j][k]= q[j][k]; 
      }
   }
   nrc_ludcmp ( qlu, n, indx, &d ); 
   nrc_lubksb ( qlu, n, indx, x ); 
   rr = BIG; 
   do {
      rrold = rr; 
      for ( j = 1; j <= n; j ++ ) z[j]= x[j]; 
      nrc_mprove ( q, qlu, n, indx, y, x ); 
      for ( rr = 0.0, j = 1; j <= n; j ++ )
         rr += SQR ( z[j]- x[j] ); 
   } while ( rr < rrold ); 
   *nrc_resid = sqrt ( rrold ); 
   for ( k = 1; k <= n; k ++ ) {
      for ( sum = cof[k], j = 1; j <= k; j ++ ) sum -= z[j]*cof[k - j]; 
      y[k]= sum; 
   }
   for ( j = 1; j <= n; j ++ ) {
      cof[j]= y[j]; 
      cof[j + n] = - z[j]; 
   }
   nrc_free_vector ( z, 1, n ); 
   nrc_free_vector ( y, 1, n ); 
   nrc_free_vector ( x, 1, n ); 
   nrc_free_matrix ( qlu, 1, n, 1, n ); 
   nrc_free_matrix ( q, 1, n, 1, n ); 
   nrc_free_ivector ( indx, 1, n ); 
}
#undef BIG
#undef NRANSI
