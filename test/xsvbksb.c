
#include "nrc_types.h"

/* Driver for routine nrc_svbksb, which calls routine nrc_svdcmp */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 20
#define MP 20
#define MAXSTR 80

int main ( void )
{
   int j, k, l, m, n; 
   sReal wmax, wmin, *w, *x, *c; 
   sReal **a, **b, **u, **v; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   w = nrc_vector ( 1, NP ); 
   x = nrc_vector ( 1, NP ); 
   c = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   b = nrc_matrix ( 1, NP, 1, MP ); 
   u = nrc_matrix ( 1, NP, 1, NP ); 
   v = nrc_matrix ( 1, NP, 1, NP ); 
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
      /* nrc_copy a into u */
      for ( k = 1; k <= n; k ++ )
         for ( l = 1; l <= n; l ++ ) u[k][l]= a[k][l]; 
      /* decompose nrc_matrix a */
      nrc_svdcmp ( u, n, n, w, v ); 
      /* find maximum singular value */
      wmax = 0.0; 
      for ( k = 1; k <= n; k ++ )
         if ( w[k] > wmax ) wmax = w[k]; 
      /* define "small" */
      wmin = wmax*( 1.0e-6 ); 
      /* zero the "small" singular values */
      for ( k = 1; k <= n; k ++ )
         if ( w[k] < wmin ) w[k]= 0.0; 
      /* backsubstitute for each right - hand side nrc_vector */
      for ( l = 1; l <= m; l ++ ) {
         printf ( "\nVector number %2d\n", l ); 
         for ( k = 1; k <= n; k ++ ) c[k]= b[k][l]; 
         nrc_svbksb ( u, w, v, n, n, c, x ); 
         printf ( " solution nrc_vector is:\n" ); 
         for ( k = 1; k <= n; k ++ ) printf ( "%12.6f", x[k] ); 
         printf ( "\n original right - hand side nrc_vector:\n" ); 
         for ( k = 1; k <= n; k ++ ) printf ( "%12.6f", c[k] ); 
         printf ( "\n ( nrc_matrix )*( sol'n nrc_vector ):\n" ); 
         for ( k = 1; k <= n; k ++ ) {
            c[k]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               c[k] += a[k][j]*x[j]; 
         }
         for ( k = 1; k <= n; k ++ ) printf ( "%12.6f", c[k] ); 
         printf ( "\n" ); 
      }
      printf ( "***********************************\n" ); 
      printf ( "press RETURN for next problem\n" ); 
      ( void ) getchar ( ); 
   }
   fclose ( fp ); 
   nrc_free_matrix ( v, 1, NP, 1, NP ); 
   nrc_free_matrix ( u, 1, NP, 1, NP ); 
   nrc_free_matrix ( b, 1, NP, 1, MP ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( c, 1, NP ); 
   nrc_free_vector ( x, 1, NP ); 
   nrc_free_vector ( w, 1, NP ); 
   return 0; 
}
#undef NRANSI
