
#include "nrc_types.h"

/* Driver for routine nrc_gamdev */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define N 20
#define NPTS 10000
#define ISCAL 200
#define LLEN 50

int main ( void )
{
   char words[LLEN + 1]; 
   long idum =( - 13 ); 
   int i, ia, j, k, klim, dist[N + 1]; 
   sReal dd; 

   for ( ; ; ) {
      for ( j = 0; j <= N; j ++ ) dist[j]= 0; 
      do {
         printf ( "Select order of Gamma distribution ( n = 1..%d ), - 1 to end\n", N ); 
         scanf ( "%d", &ia ); 
      } while ( ia > N ); 
      if ( ia < 0 ) break; 
      for ( i = 1; i <= NPTS; i ++ ) {
         j =( int ) nrc_gamdev ( ia, &idum ); 
         if ( ( j >= 0 ) && ( j <= N ) ) ++ dist[j]; 
      }
      printf ( "\ngamma - distribution deviate, order %2d of %6d points\n", 
         ia, NPTS ); 
      printf ( "%6s %7s %9s \n", "x", "p ( x )", "graph:" ); 
      for ( j = 0; j < N; j ++ ) {
         dd =( sReal ) dist[j]/NPTS; 
         for ( k = 1; k <= 50; k ++ ) words[k]=' '; 
         klim =( int ) ( ISCAL*dd ); 
         if ( klim > LLEN ) klim = LLEN; 
         for ( k = 1; k <= klim; k ++ ) words[k]='*'; 
         printf ( "%6d %8.4f ", j, dd ); 
         for ( k = 1; k <= klim; k ++ ) printf ( "%c", words[k] ); 
         printf ( "\n" ); 
      }
   }
   return 0; 
}
#undef NRANSI
