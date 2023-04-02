
#include "nrc_types.h"

/* Driver for routine nrc_gaussj */

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
   sReal **a, **ai, **u, **b, **x, **t; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   a = nrc_matrix ( 1, NP, 1, NP ); 
   ai = nrc_matrix ( 1, NP, 1, NP ); 
   u = nrc_matrix ( 1, NP, 1, NP ); 
   b = nrc_matrix ( 1, NP, 1, MP ); 
   x = nrc_matrix ( 1, NP, 1, MP ); 
   t = nrc_matrix ( 1, NP, 1, MP ); 
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
      /* save matrices for later testing of results */
      for ( l = 1; l <= n; l ++ ) {
         for ( k = 1; k <= n; k ++ ) ai[k][l]= a[k][l]; 
         for ( k = 1; k <= m; k ++ ) x[l][k]= b[l][k]; 
      }
      /* invert nrc_matrix */
      nrc_gaussj ( ai, n, x, m ); 
      printf ( "\nInverse of nrc_matrix a : \n" ); 
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ ) printf ( "%12.6f", ai[k][l] ); 
         printf ( "\n" ); 
      }
      /* check inverse */
      printf ( "\na times a - inverse:\n" ); 
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ ) {
            u[k][l]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               u[k][l] += ( a[k][j]*ai[j][l] ); 
         }
         for ( l = 1; l <= n; l ++ ) printf ( "%12.6f", u[k][l] ); 
         printf ( "\n" ); 
      }
      /* check nrc_vector solutions */
      printf ( "\nCheck the following for equality:\n" ); 
      printf ( "%21s %14s\n", "original", "nrc_matrix*sol'n" ); 
      for ( l = 1; l <= m; l ++ ) {
         printf ( "nrc_vector %2d: \n", l ); 
         for ( k = 1; k <= n; k ++ ) {
            t[k][l]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               t[k][l] += ( a[k][j]*x[j][l] ); 
            printf ( "%8s %12.6f %12.6f\n", " ", 
               b[k][l], t[k][l] ); 
         }
      }
      printf ( "***********************************\n" ); 
      printf ( "press RETURN for next problem:\n" ); 
      ( void ) getchar ( ); 
   }
   fclose ( fp ); 
   nrc_free_matrix ( t, 1, NP, 1, MP ); 
   nrc_free_matrix ( x, 1, NP, 1, MP ); 
   nrc_free_matrix ( b, 1, NP, 1, MP ); 
   nrc_free_matrix ( u, 1, NP, 1, NP ); 
   nrc_free_matrix ( ai, 1, NP, 1, NP ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   return 0; 
}
#undef NRANSI
