
#include "nrc_types.h"

/* Driver for routine nrc_svdvar */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 6
#define MA 3

int main ( void )
{
   int i, j; 
   sReal **cvm, **v; 
   static sReal vtemp[NP][NP]=
      {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
      2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 
      3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 
      4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 
      5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 
      6.0, 6.0, 6.0, 6.0, 6.0, 6.0}; 
   static sReal w[NP + 1]=
      {0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0}; 
   static sReal tru[MA][MA]=
      {1.25, 2.5, 3.75, 
      2.5, 5.0, 7.5, 
      3.75, 7.5, 11.25}; 

   cvm = nrc_matrix ( 1, MA, 1, MA ); 
   v = nrc_convert_matrix ( &vtemp[0][0], 1, NP, 1, NP ); 
   printf ( "\nmatrix v\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.6f", v[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "\nvector w\n" ); 
   for ( i = 1; i <= NP; i ++ ) printf ( "%12.6f", w[i] ); 
   printf ( "\n" ); 
   nrc_svdvar ( v, MA, w, cvm ); 
   printf ( "\ncovariance nrc_matrix from nrc_svdvar\n" ); 
   for ( i = 1; i <= MA; i ++ ) {
      for ( j = 1; j <= MA; j ++ ) printf ( "%12.6f", cvm[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "\nexpected covariance nrc_matrix\n" ); 
   for ( i = 1; i <= MA; i ++ ) {
      for ( j = 1; j <= MA; j ++ ) printf ( "%12.6f", tru[i - 1][j - 1] ); 
      printf ( "\n" ); 
   }
   nrc_free_convert_matrix ( v, 1, NP, 1, NP ); 
   nrc_free_matrix ( cvm, 1, MA, 1, MA ); 
   return 0; 
}
#undef NRANSI
