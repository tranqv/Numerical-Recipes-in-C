
#include "nrc_types.h"

/* Driver for routine nrc_svdcmp */

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
   sReal *w, **a, **u, **v; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   w = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, MP, 1, NP ); 
   u = nrc_matrix ( 1, MP, 1, NP ); 
   v = nrc_matrix ( 1, NP, 1, NP ); 
   /* read input matrices */
   if ( ( fp = fopen ( "matrx3.dat", "r" ) ) == NULL )
      nrc_error ( "Data file matrx3.dat not found\n" ); 
   while ( !feof ( fp ) ) {
      fgets ( dummy, MAXSTR, fp ); 
      fgets ( dummy, MAXSTR, fp ); 
      fscanf ( fp, "%d %d ", &m, &n ); 
      fgets ( dummy, MAXSTR, fp ); 
      /* nrc_copy original nrc_matrix into u */
      for ( k = 1; k <= m; k ++ )
         for ( l = 1; l <= n; l ++ ) {
            fscanf ( fp, "%lf ", &a[k][l] ); 
            u[k][l]= a[k][l]; 
         }
      /* perform decomposition */
      nrc_svdcmp ( u, m, n, w, v ); 
      /* write results */
      printf ( "Decomposition matrices:\n" ); 
      printf ( "Matrix u\n" ); 
      for ( k = 1; k <= m; k ++ ) {
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", u[k][l] ); 
         printf ( "\n" ); 
      }
      printf ( "Diagonal of nrc_matrix w\n" ); 
      for ( k = 1; k <= n; k ++ )
         printf ( "%12.6f", w[k] ); 
      printf ( "\nMatrix v - transpose\n" ); 
      for ( k = 1; k <= n; k ++ ) {
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", v[l][k] ); 
         printf ( "\n" ); 
      }
      printf ( "\nCheck product against original nrc_matrix:\n" ); 
      printf ( "Original nrc_matrix:\n" ); 
      for ( k = 1; k <= m; k ++ ) {
         for ( l = 1; l <= n; l ++ )
            printf ( "%12.6f", a[k][l] ); 
         printf ( "\n" ); 
      }
      printf ( "Product u*w*( v - transpose ):\n" ); 
      for ( k = 1; k <= m; k ++ ) {
         for ( l = 1; l <= n; l ++ ) {
            a[k][l]= 0.0; 
            for ( j = 1; j <= n; j ++ )
               a[k][l] += u[k][j]*w[j]*v[l][j]; 
         }
         for ( l = 1; l <= n; l ++ ) printf ( "%12.6f", a[k][l] ); 
         printf ( "\n" ); 
      }
      printf ( "***********************************\n" ); 
      printf ( "press RETURN for next problem\n" ); 
      ( void ) getchar (  ); 
   }
   fclose ( fp ); 
   nrc_free_matrix ( v, 1, NP, 1, NP ); 
   nrc_free_matrix ( u, 1, MP, 1, NP ); 
   nrc_free_matrix ( a, 1, MP, 1, NP ); 
   nrc_free_vector ( w, 1, NP ); 
   return 0; 
}
#undef NRANSI
