
#include "nrc_types.h"

/* Driver for routine nrc_ludcmp */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 20
#define MAXSTR 80

int main ( void )
{
   int j, k, l, m, n, dum, *indx, *jndx; 
   sReal d, **a, **xl, **xu, **x; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   indx = nrc_ivector ( 1, NP ); 
   jndx = nrc_ivector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   xl = nrc_matrix ( 1, NP, 1, NP ); 
   xu = nrc_matrix ( 1, NP, 1, NP ); 
   x = nrc_matrix ( 1, NP, 1, NP ); 
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
         for ( k = 1; k <= n; k ++ ) fscanf ( fp, "%lf ", &x[k][l] ); 
      /* Print out a - nrc_matrix for comparison with product of
         lower and upper decomposition matrices */
      printf ( "original nrc_matrix:\n" ); 
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ ) printf ( "%12.6f", a[k][l] ); 
         printf ( "\n" ); 
      }
      /* Perform the decomposition */
      nrc_ludcmp ( a, n, indx, &d ); 
      /* Compose separately the lower and upper matrices */
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ ) {
            if ( l > k ) {
               xu[k][l]= a[k][l]; 
               xl[k][l]= 0.0; 
            } else if ( l < k ) {
               xu[k][l]= 0.0; 
               xl[k][l]= a[k][l]; 
            } else {
               xu[k][l]= a[k][l]; 
               xl[k][l]= 1.0; 
            }
         }
      }
      /* Compute product of lower and upper matrices for
         comparison with original nrc_matrix */
      for ( k = 1; k <= n; k ++ ) {
         jndx[k]= k; 
         for ( l = 1; l <= n; l ++ ) {
            x[k][l]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               x[k][l] += ( xl[k][j]*xu[j][l] ); 
         }
      }
      printf ( "\n%s%s\n", "product of lower and upper ", 
          "matrices ( rows unscrambled ):" ); 
      for ( k = 1; k <= n; k ++ ) {
         dum = jndx[indx[k]]; 
         jndx[indx[k]]= jndx[k]; 
         jndx[k]= dum; 
      }
      for ( k = 1; k <= n; k ++ )
         for ( j = 1; j <= n; j ++ )
            if ( jndx[j] == k ) {
               for ( l = 1; l <= n; l ++ )
                  printf ( "%12.6f", x[j][l] ); 
               printf ( "\n" ); 
            }
      printf ( "\nlower nrc_matrix of the decomposition:\n" ); 
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ ) printf ( "%12.6f", xl[k][l] ); 
         printf ( "\n" ); 
      }
      printf ( "\nupper nrc_matrix of the decomposition:\n" ); 
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ ) printf ( "%12.6f", xu[k][l] ); 
         printf ( "\n" ); 
      }
      printf ( "\n***********************************\n" ); 
      printf ( "press return for next problem:\n" ); 
      ( void ) getchar ( ); 
   }
   fclose ( fp ); 
   nrc_free_matrix ( x, 1, NP, 1, NP ); 
   nrc_free_matrix ( xu, 1, NP, 1, NP ); 
   nrc_free_matrix ( xl, 1, NP, 1, NP ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_ivector ( jndx, 1, NP ); 
   nrc_free_ivector ( indx, 1, NP ); 
   return 0; 
}
#undef NRANSI
