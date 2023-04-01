
#include "nrc_types.h"

/* Driver for routine nrc_qrdcmp */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 20
#define MAXSTR 80

int main ( void )
{
   int j, k, l, m, n, sing; 
   sReal *x, **a, **ai, **b, *c, *d; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   x = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   b = nrc_matrix ( 1, NP, 1, NP ); 
   ai = nrc_matrix ( 1, NP, 1, NP ); 
   c = nrc_vector ( 1, NP ); 
   d = nrc_vector ( 1, NP ); 
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
         for ( k = 1; k <= n; k ++ ) ai[k][l]= a[k][l]; 
      /* Do qr decomposition */
      nrc_qrdcmp ( a, n, c, d, &sing ); 
      if ( sing ) fprintf ( stderr, "Singularity in QR decomposition.\n" ); 
      /* Solve equations for each right - hand nrc_vector */
      for ( k = 1; k <= m; k ++ ) {
         for ( l = 1; l <= n; l ++ ) x[l]= b[l][k]; 
         nrc_qrsolv ( a, n, c, d, x ); 
         /* Test results with original nrc_matrix */
         printf ( "right - hand side nrc_vector:\n" ); 
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", b[l][k] ); 
         printf ( "\n%s%s\n", "result of nrc_matrix applied", 
            " to sol'n nrc_vector" ); 
         for ( l = 1; l <= n; l ++ ) {
            b[l][k]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               b[l][k] += ( ai[l][j]*x[j] ); 
         }
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", b[l][k] ); 
         printf ( "\n*********************************\n" ); 
      }
      printf ( "press RETURN for next problem:\n" ); 
      ( void ) getchar (  ); 
   }
   fclose ( fp ); 
   nrc_free_vector ( d, 1, NP ); 
   nrc_free_vector ( c, 1, NP ); 
   nrc_free_matrix ( ai, 1, NP, 1, NP ); 
   nrc_free_matrix ( b, 1, NP, 1, NP ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( x, 1, NP ); 
   return 0; 
}
#undef NRANSI
