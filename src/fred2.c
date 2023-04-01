
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_fred2 ( int n, sReal a, sReal b, sReal t[], sReal f[], sReal w[], 
   sReal ( *g )( sReal ), sReal ( *ak )( sReal, sReal ) )
{
   void nrc_gauleg ( sReal x1, sReal x2, sReal x[], sReal w[], int n ); 
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d ); 
   int i, j, *indx; 
   sReal d, **omk; 

   indx = nrc_ivector ( 1, n ); 
   omk = nrc_matrix ( 1, n, 1, n ); 
   nrc_gauleg ( a, b, t, w, n ); 
   for ( i = 1; i <= n; i ++ ) {
      for ( j = 1; j <= n; j ++ )
         omk[i][j]=( sReal )( i == j )-( *ak )( t[i], t[j] )*w[j]; 
      f[i]=( *g )( t[i] ); 
   }
   nrc_ludcmp ( omk, n, indx, &d ); 
   nrc_lubksb ( omk, n, indx, f ); 
   nrc_free_matrix ( omk, 1, n, 1, n ); 
   nrc_free_ivector ( indx, 1, n ); 
}
#undef NRANSI
