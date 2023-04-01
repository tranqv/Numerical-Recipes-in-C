
#include "nrc_types.h"

/* Driver for routine nrc_lubksb */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 20
#define MAXSTR 80

int main ( void )
{
   int j, k, l, m, n, *indx; 
   sReal p, *x, **a, **b, **c; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   indx = nrc_ivector ( 1, NP ); 
   x = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   b = nrc_matrix ( 1, NP, 1, NP ); 
   c = nrc_matrix ( 1, NP, 1, NP ); 
   if ( ( fp = fopen ( "matrx1.dat", "r" ) ) == NULL )
      nrc_error ( "Data file matrx1.dat not found\n" ); 
   while ( !feof ( fp ) ) {
      fgets ( dummy, MAXSTR, fp ); 
      fgets ( dummy, MAXSTR, fp ); 
      fscanf ( fp, "%d %d ", &n, &m ); 
      fgets ( dummy, MAXSTR, fp ); 
      for ( k = 1; k <= n; k ++ )
         for ( l = 1; l <= n; l ++ ) fscanf ( fp, "%lf ", &a[k][l] ); 
      fgets ( dummy, MAXSTR, fp ); 
      for ( l = 1; l <= m; l ++ )
         for ( k = 1; k <= n; k ++ ) fscanf ( fp, "%lf ", &b[k][l] ); 
      /* Save nrc_matrix a for later testing */
      for ( l = 1; l <= n; l ++ )
         for ( k = 1; k <= n; k ++ ) c[k][l]= a[k][l]; 
      /* Do LU decomposition */
      nrc_ludcmp ( c, n, indx, &p ); 
      /* Solve equations for each right - hand nrc_vector */
      for ( k = 1; k <= m; k ++ ) {
         for ( l = 1; l <= n; l ++ ) x[l]= b[l][k]; 
         nrc_lubksb ( c, n, indx, x ); 
         /* Test results with original nrc_matrix */
         printf ( "right - hand side nrc_vector:\n" ); 
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", b[l][k] ); 
         printf ( "\n%s%s\n", "result of nrc_matrix applied", 
            " to sol'n nrc_vector" ); 
         for ( l = 1; l <= n; l ++ ) {
            b[l][k]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               b[l][k] += ( a[l][j]*x[j] ); 
         }
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", b[l][k] ); 
         printf ( "\n*********************************\n" ); 
      }
      printf ( "press RETURN for next problem:\n" ); 
      ( void ) getchar (  ); 
   }
   fclose ( fp ); 
   nrc_free_matrix ( c, 1, NP, 1, NP ); 
   nrc_free_matrix ( b, 1, NP, 1, NP ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( x, 1, NP ); 
   nrc_free_ivector ( indx, 1, NP ); 
   return 0; 
}
#undef NRANSI
