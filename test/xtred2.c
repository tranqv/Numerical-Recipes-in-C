
#include "nrc_types.h"

/* Driver for routine nrc_tred2 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 10

int main ( void )
{
   int i, j, k, l, m; 
   sReal *d, *e, **a, **f; 
   static sReal c[NP][NP]={
      5.0,  4.3,  3.0,  2.0,  1.0,  0.0, - 1.0, - 2.0, - 3.0, - 4.0, 
      4.3,  5.1,  4.0,  3.0,  2.0,  1.0,  0.0, - 1.0, - 2.0, - 3.0, 
      3.0,  4.0,  5.0,  4.0,  3.0,  2.0,  1.0,  0.0, - 1.0, - 2.0, 
      2.0,  3.0,  4.0,  5.0,  4.0,  3.0,  2.0,  1.0,  0.0, - 1.0, 
      1.0,  2.0,  3.0,  4.0,  5.0,  4.0,  3.0,  2.0,  1.0,  0.0, 
      0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  4.0,  3.0,  2.0,  1.0, 
      - 1.0,  0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  4.0,  3.0,  2.0, 
      - 2.0, - 1.0,  0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  4.0,  3.0, 
      - 3.0, - 2.0, - 1.0,  0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  4.0, 
      - 4.0, - 3.0, - 2.0, - 1.0,  0.0,  1.0,  2.0,  3.0,  4.0,  5.0}; 

   d = nrc_vector ( 1, NP ); 
   e = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   f = nrc_matrix ( 1, NP, 1, NP ); 
   for ( i = 1; i <= NP; i ++ )
      for ( j = 1; j <= NP; j ++ ) a[i][j]= c[i - 1][j - 1]; 
   nrc_tred2 ( a, NP, d, e ); 
   printf ( "diagonal elements\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      printf ( "%12.6f", d[i] ); 
      if ( ( i % 5 ) == 0 ) printf ( "\n" ); 
   }
   printf ( "off - diagonal elements\n" ); 
   for ( i = 2; i <= NP; i ++ ) {
      printf ( "%12.6f", e[i] ); 
      if ( ( i % 5 ) == 0 ) printf ( "\n" ); 
   }
   /* Check transformation nrc_matrix */
   for ( j = 1; j <= NP; j ++ ) {
      for ( k = 1; k <= NP; k ++ ) {
         f[j][k]= 0.0; 
         for ( l = 1; l <= NP; l ++ ) {
            for ( m = 1; m <= NP; m ++ )
               f[j][k] += a[l][j]*c[l - 1][m - 1]*a[m][k]; 
         }
      }
   }
   /* How does it look? */
   printf ( "tridiagonal nrc_matrix\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%7.2f", f[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_matrix ( f, 1, NP, 1, NP ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( e, 1, NP ); 
   nrc_free_vector ( d, 1, NP ); 
   return 0; 
}
#undef NRANSI
