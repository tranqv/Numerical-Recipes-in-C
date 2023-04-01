
#include "nrc_types.h"

/* Driver for routine nrc_cholsl */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 3

int main ( void )
{
   int i, j, k; 
   sReal sum, **a, **atest, **chol, *p, *x; 
   static sReal aorig[N + 1][N + 1]=
      {0.0, 0.0, 0.0, 0.0, 
      0.0, 100.0, 15.0, 0.01, 
      0.0, 15.0, 2.3, 0.01, 
      0.0, 0.01, 0.01, 1.0}; 
   static sReal b[N + 1]={0.0, 0.4, 0.02, 99.0}; 

   a = nrc_matrix ( 1, N, 1, N ); 
   atest = nrc_matrix ( 1, N, 1, N ); 
   chol = nrc_matrix ( 1, N, 1, N ); 
   p = nrc_vector ( 1, N ); 
   x = nrc_vector ( 1, N ); 
   for ( i = 1; i <= N; i ++ )
      for ( j = 1; j <= N; j ++ ) a[i][j]= aorig[i][j]; 
   nrc_choldc ( a, N, p ); 
   printf ( "Original nrc_matrix:\n" ); 
   for ( i = 1; i <= N; i ++ ) {
      for ( j = 1; j <= N; j ++ ) {
         chol[i][j]=( ( i > j ) ? a[i][j] : ( i == j ? p[i] : 0.0 ) ); 
         if ( i > j ) chol[i][j]= a[i][j]; 
         else chol[i][j]=( i == j ? p[i] : 0.0 ); 
         printf ( "%16.6e", aorig[i][j] ); 
      }
      printf ( "\n" ); 
   }
   printf ( "\n" ); 
   printf ( "Product of Cholesky factors:\n" ); 
   for ( i = 1; i <= N; i ++ ) {
      for ( j = 1; j <= N; j ++ ) {
         for ( sum = 0.0, k = 1; k <= N; k ++ ) sum += chol[i][k]*chol[j][k]; 
         atest[i][j]= sum; 
         printf ( "%16.6e", atest[i][j] ); 
      }
      printf ( "\n" ); 
   }
   printf ( "\n" ); 
   printf ( "Check solution nrc_vector:\n" ); 
   nrc_cholsl ( a, N, p, b, x ); 
   for ( i = 1; i <= N; i ++ ) {
      for ( sum = 0.0, j = 1; j <= N; j ++ ) sum += aorig[i][j]*x[j]; 
      p[i]= sum; 
      printf ( "%16.6e%16.6e\n", p[i], b[i] ); 
   }
   nrc_free_vector ( x, 1, N ); 
   nrc_free_vector ( p, 1, N ); 
   nrc_free_matrix ( chol, 1, N, 1, N ); 
   nrc_free_matrix ( atest, 1, N, 1, N ); 
   nrc_free_matrix ( a, 1, N, 1, N ); 
   return 0; 
}
#undef NRANSI
