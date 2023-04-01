
#include "nrc_types.h"

/* Driver for routine nrc_balanc */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5

int main ( void )
{
   int i, j; 
   sReal *c, *r, **a; 

   c = nrc_vector ( 1, NP ); 
   r = nrc_vector ( 1, NP ); 
   a = nrc_matrix ( 1, NP, 1, NP ); 
   for ( i = 1; i <= NP; i ++ )
      for ( j = 1; j <= NP; j ++ )
         a[i][j] = ( ( ( i & 1 ) && !( j & 1 ) ) ? 100.0 : 1.0 ); 
   /* Write norms */
   for ( i = 1; i <= NP; i ++ ) {
      r[i]= c[i]= 0.0; 
      for ( j = 1; j <= NP; j ++ ) {
         r[i] += fabs ( a[i][j] ); 
         c[i] += fabs ( a[j][i] ); 
      }
   }
   printf ( "rows:\n" ); 
   for ( i = 1; i <= NP; i ++ ) printf ( "%12.2f", r[i] ); 
   printf ( "\ncolumns:\n" ); 
   for ( i = 1; i <= NP; i ++ ) printf ( "%12.2f", c[i] ); 
   printf ( "\n\n***** Balancing nrc_matrix *****\n\n" ); 
   nrc_balanc ( a, NP ); 
   /* Write norms */
   for ( i = 1; i <= NP; i ++ ) {
      r[i]= c[i]= 0.0; 
      for ( j = 1; j <= NP; j ++ ) {
         r[i] += fabs ( a[i][j] ); 
         c[i] += fabs ( a[j][i] ); 
      }
   }
   printf ( "rows:\n" ); 
   for ( i = 1; i <= NP; i ++ ) printf ( "%12.2f", r[i] ); 
   printf ( "\ncolumns:\n" ); 
   for ( i = 1; i <= NP; i ++ ) printf ( "%12.2f", c[i] ); 
   printf ( "\n" ); 
   nrc_free_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( r, 1, NP ); 
   nrc_free_vector ( c, 1, NP ); 
   return 0; 
}
#undef NRANSI
