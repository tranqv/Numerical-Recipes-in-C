
#include "nrc_types.h"

/* Driver for routine nrc_covsrt */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MA 10
#define MFIT 5

int main ( void )
{
   int i, j, *ia; 
   sReal **covar; 

   ia = nrc_ivector ( 1, MA ); 
   covar = nrc_matrix ( 1, MA, 1, MA ); 
   for ( i = 1; i <= MA; i ++ )
      for ( j = 1; j <= MA; j ++ ) {
         covar[i][j]= 0.0; 
         if ( ( i <= MFIT ) && ( j <= MFIT ) )
            covar[i][j]= i + j - 1; 
      }
   printf ( "\noriginal nrc_matrix\n" ); 
   for ( i = 1; i <= MA; i ++ ) {
      for ( j = 1; j <= MA; j ++ ) printf ( "%4.1f", covar[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "press RETURN to continue...\n" ); 
   ( void ) getchar ( ); 
   printf ( "\nTest #1 - full fitting\n" ); 
   for ( i = 1; i <= MA; i ++ ) ia[i]= 1; 
   nrc_covsrt ( covar, MA, ia, MA ); 
   for ( i = 1; i <= MA; i ++ ) {
      for ( j = 1; j <= MA; j ++ ) printf ( "%4.1f", covar[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "press RETURN to continue...\n" ); 
   ( void ) getchar ( ); 
   printf ( "\nTest #2 - nrc_spread\n" ); 
   for ( i = 1; i <= MA; i ++ )
      for ( j = 1; j <= MA; j ++ ) {
         covar[i][j]= 0.0; 
         if ( ( i <= MFIT ) && ( j <= MFIT ) ) covar[i][j]= i + j - 1; 
      }
   for ( i = 1; i <= MA; i += 2 ) ia[i]= 0; 
   nrc_covsrt ( covar, MA, ia, MFIT ); 
   for ( i = 1; i <= MA; i ++ ) {
      for ( j = 1; j <= MA; j ++ ) printf ( "%4.1f", covar[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_matrix ( covar, 1, MA, 1, MA ); 
   nrc_free_ivector ( ia, 1, MA ); 
   return 0; 
}
#undef NRANSI
