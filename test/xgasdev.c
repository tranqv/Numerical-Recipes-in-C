
#include "nrc_types.h"

/* Driver for routine nrc_gasdev */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define N 20
#define NOVER2 (N/2)
#define NPTS 10000
#define ISCAL 400
#define LLEN 50

int main ( void )
{
   char words[LLEN + 1]; 
   int i, j, k, klim, dist[N + 1]; 
   long idum =( - 13 ); 
   sReal dd, x; 

   for ( j = 0; j <= N; j ++ ) dist[j]= 0; 
   for ( i = 1; i <= NPTS; i ++ ) {
      x = 0.25*N*nrc_gasdev ( &idum ); 
      j =( int )( x > 0 ? x + 0.5 : x - 0.5 ); 
      if ( ( j >= - NOVER2 ) && ( j <= NOVER2 ) ) ++ dist[j + NOVER2]; 
   }
   printf ( "Normally distributed deviate of %6d points\n", NPTS ); 
   printf ( "%5s %10s %9s\n", "x", "p ( x )", "graph:" ); 
   for ( j = 0; j <= N; j ++ ) {
      dd =( sReal ) dist[j]/NPTS; 
      for ( k = 1; k <= LLEN; k ++ ) words[k]=' '; 
      klim =( int ) ( ISCAL*dd ); 
      if ( klim > LLEN )  klim = LLEN; 
      for ( k = 1; k <= klim; k ++ ) words[k]='*'; 
      printf ( "%8.4f %8.4f  ", j/( 0.25*N ), dd ); 
      for ( k = 1; k <= LLEN; k ++ ) printf ( "%c", words[k] ); 
      printf ( "\n" ); 
   }
   return 0; 
}
#undef NRANSI
