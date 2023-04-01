
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_voltra ( int n, int m, sReal t0, sReal h, sReal *t, sReal **f, 
   sReal ( *g )( int, sReal ), sReal ( *ak )( int, int, sReal, sReal ) )
{
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d ); 
   int i, j, k, l, *indx; 
   sReal d, sum, **a, *b; 

   indx = nrc_ivector ( 1, m ); 
   a = nrc_matrix ( 1, m, 1, m ); 
   b = nrc_vector ( 1, m ); 
   t[1]= t0; 
   for ( k = 1; k <= m; k ++ ) f[k][1]=( *g )( k, t[1] ); 
   for ( i = 2; i <= n; i ++ ) {
      t[i]= t[i - 1]+ h; 
      for ( k = 1; k <= m; k ++ ) {
         sum =( *g )( k, t[i] ); 
         for ( l = 1; l <= m; l ++ ) {
            sum += 0.5*h*( *ak )( k, l, t[i], t[1] )*f[l][1]; 
            for ( j = 2; j < i; j ++ )
               sum += h*( *ak )( k, l, t[i], t[j] )*f[l][j]; 
            a[k][l]=( k == l )- 0.5*h*( *ak )( k, l, t[i], t[i] ); 
         }
         b[k]= sum; 
      }
      nrc_ludcmp ( a, m, indx, &d ); 
      nrc_lubksb ( a, m, indx, b ); 
      for ( k = 1; k <= m; k ++ ) f[k][i]= b[k]; 
   }
   nrc_free_vector ( b, 1, m ); 
   nrc_free_matrix ( a, 1, m, 1, m ); 
   nrc_free_ivector ( indx, 1, m ); 
}
#undef NRANSI
