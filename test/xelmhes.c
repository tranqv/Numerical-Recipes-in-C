
#include "nrc_types.h"

/* Driver for routine nrc_elmhes */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5

int main ( void )
{
   int i, j; 
   static sReal b[NP][NP]=
      {1.0, 2.0, 300.0, 4.0, 5.0, 
      2.0, 3.0, 400.0, 5.0, 6.0, 
      3.0, 4.0, 5.0, 6.0, 7.0, 
      4.0, 5.0, 600.0, 7.0, 8.0, 
      5.0, 6.0, 700.0, 8.0, 9.0}; 
   sReal **a; 

   a = nrc_convert_matrix ( &b[0][0], 1, NP, 1, NP ); 
   printf ( "***** original nrc_matrix *****\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.2f", a[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "***** balance nrc_matrix *****\n" ); 
   nrc_balanc ( a, NP ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.2f", a[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "***** reduce to hessenberg form *****\n" ); 
   nrc_elmhes ( a, NP ); 
   for ( j = 1; j <= NP - 2; j ++ )
      for ( i = j + 2; i <= NP; i ++ )
         a[i][j]= 0.0; 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.2e", a[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_convert_matrix ( a, 1, NP, 1, NP ); 
   return 0; 
}
#undef NRANSI
