
#include "nrc_types.h"

/* Driver for routine nrc_splie2 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define M 10
#define N 10

int main ( void )
{
   int i, j; 
   sReal x1x2, *x1, *x2, **y, **y2; 

   x1 = nrc_vector ( 1, N ); 
   x2 = nrc_vector ( 1, N ); 
   y = nrc_matrix ( 1, M, 1, N ); 
   y2 = nrc_matrix ( 1, M, 1, N ); 
   for ( i = 1; i <= M; i ++ ) x1[i]= 0.2*i; 
   for ( i = 1; i <= N; i ++ ) x2[i]= 0.2*i; 
   for ( i = 1; i <= M; i ++ )
      for ( j = 1; j <= N; j ++ ) {
         x1x2 = x1[i]*x2[j]; 
         y[i][j]= x1x2*x1x2; 
      }
   nrc_splie2 ( x1, x2, y, M, N, y2 ); 
   printf ( "\nsecond derivatives from SPLIE2\n" ); 
   printf ( "natural nrc_spline assumed\n" ); 
   for ( i = 1; i <= 5; i ++ ) {
      for ( j = 1; j <= 5; j ++ ) printf ( "%12.6f", y2[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "\nactual second derivatives\n" ); 
   for ( i = 1; i <= 5; i ++ ) {
      for ( j = 1; j <= 5; j ++ ) printf ( "%12.6f", 2.0*x1[i]*x1[i] ); 
      printf ( "\n" ); 
   }
   nrc_free_matrix ( y2, 1, M, 1, N ); 
   nrc_free_matrix ( y, 1, M, 1, N ); 
   nrc_free_vector ( x2, 1, N ); 
   nrc_free_vector ( x1, 1, N ); 
   return 0; 
}
#undef NRANSI
