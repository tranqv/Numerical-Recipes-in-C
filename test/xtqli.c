
#include "nrc_types.h"

/* Driver for routine nrc_tqli */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 10
#define TINY 1.0e-6

int main ( void )
{
   int i, j, k; 
   sReal *d, *e, *f, **a; 
   static sReal c[NP][NP]={
      5.0, 4.3, 3.0, 2.0, 1.0, 0.0, - 1.0, - 2.0, - 3.0, - 4.0, 
      4.3, 5.1, 4.0, 3.0, 2.0, 1.0, 0.0, - 1.0, - 2.0, - 3.0, 
      3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0, - 1.0, - 2.0, 
      2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0, - 1.0, 
      1.0, 2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0, 
      0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 
      - 1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 
      - 2.0, - 1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 
      - 3.0, - 2.0, - 1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 4.0, 
      - 4.0, - 3.0, - 2.0, - 1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0}; 

   d = nrc_vector ( 1, NP ); 
   e = nrc_vector ( 1, NP ); 
   f = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   for ( i = 1; i <= NP; i ++ )
      for ( j = 1; j <= NP; j ++ ) a[i][j]= c[i - 1][j - 1]; 
   nrc_tred2 ( a, NP, d, e ); 
   nrc_tqli ( d, e, NP, a ); 
   printf ( "\nEigenvectors for a real symmetric nrc_matrix\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) {
         f[j]= 0.0; 
         for ( k = 1; k <= NP; k ++ )
            f[j] += ( c[j - 1][k - 1]*a[k][i] ); 
      }
      printf ( "%s %3d %s %10.6f\n", "eigenvalue", i, " =", d[i] ); 
      printf ( "%11s %14s %9s\n", "nrc_vector", "mtrx*vect.", "ratio" ); 
      for ( j = 1; j <= NP; j ++ ) {
         if ( fabs ( a[j][i] ) < TINY )
            printf ( "%12.6f %12.6f %12s\n", 
               a[j][i], f[j], "div. by 0" ); 
         else
            printf ( "%12.6f %12.6f %12.6f\n", 
               a[j][i], f[j], f[j]/a[j][i] ); 
      }
      printf ( "Press ENTER to continue...\n" ); 
      ( void ) getchar ( ); 
   }
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( f, 1, NP ); 
   nrc_free_vector ( e, 1, NP ); 
   nrc_free_vector ( d, 1, NP ); 
   return 0; 
}
#undef NRANSI
