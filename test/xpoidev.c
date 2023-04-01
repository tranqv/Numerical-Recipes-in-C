
#include "nrc_types.h"

/* Driver for routine nrc_poidev */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define N 20
#define NPTS 10000
#define ISCAL 200
#define LLEN 50

int main ( void )
{
   char txt[LLEN + 1]; 
   long idum =( - 13 ); 
   int i, j, k, klim, dist[N + 1]; 
   sReal xm, dd; 

   for ( ; ;  ) {
      for ( j = 0; j <= N; j ++ ) dist[j]= 0; 
      do {
         printf ( "Mean of Poisson distribution ( 0.0 < x <%d.0 ) ", N ); 
         printf ( "- Negative to end:\n" ); 
         scanf ( "%f", &xm ); 
      } while ( xm > N ); 
      if ( xm < 0.0 ) break; 
      for ( i = 1; i <= NPTS; i ++ ) {
         j =( int ) ( 0.5 + nrc_poidev ( xm, &idum ) ); 
         if ( ( j >= 0 ) && ( j <= N ) ) ++ dist[j]; 
      }
      printf ( "Poisson - distributed deviate,  mean %5.2f of %6d points\n", 
         xm, NPTS ); 
      printf ( "%5s %8s %10s\n", "x", "p ( x )", "graph:" ); 
      for ( j = 0; j <= N; j ++ ) {
         dd =( sReal ) dist[j]/NPTS; 
         for ( k = 0; k <= LLEN; k ++ ) txt[k]=' '; 
         klim =( int ) ( ISCAL*dd ); 
         if ( klim > LLEN ) klim = LLEN; 
         for ( k = 1; k <= klim; k ++ ) txt[k]='*'; 
         txt[LLEN]='\0'; 
         printf ( "%6d %8.4f   %s\n", j, dd, txt ); 
      }
   }
   return 0; 
}
#undef NRANSI
