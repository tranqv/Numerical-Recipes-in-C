
#include "nrc_types.h"

/* Driver for routine nrc_bnldev */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define N 20
#define NPTS 1000
#define ISCAL 200
#define NN 100
#define LLEN 50

int main ( void )
{
   char txt[LLEN + 1]; 
   int i, j, k, klim, dist[N + 1]; 
   long idum =( - 133 ); 
   sReal pp, xm, dd; 

   for ( ; ;  ) {
      for ( j = 0; j <= N; j ++ ) dist[j]= 0; 
      do {
         printf ( "Mean of binomial distribution ( 0.0 to %d.0 )", N ); 
         printf ( " - Negative to end:\n" ); 
         scanf ( "%f", &xm ); 
      } while ( xm > N ); 
      if ( xm < 0.0 ) break; 
      pp = xm/NN; 
      for ( i = 1; i <= NPTS; i ++ ) {
         j = nrc_bnldev ( pp, NN, &idum ); 
         if ( j >= 0 && j <= N ) ++ dist[j]; 
      }
      printf ( "Binomial - distributed deviate,  mean %5.2f of %6d points\n", 
         xm, NPTS ); 
      printf ( "%4s %8s %10s\n", "x", "p ( x )", "graph:" ); 
      for ( j = 0; j < N; j ++ ) {
         for ( k = 0; k <= LLEN; k ++ ) txt[k]=' '; 
         dd =( sReal ) dist[j]/NPTS; 
         klim =( int ) ( ISCAL*dd + 1 ); 
         if ( klim > LLEN ) klim = LLEN; 
         for ( k = 1; k <= klim; k ++ ) txt[k]='*'; 
         txt[LLEN]='\0'; 
         printf ( "%4d %9.4f   %s\n", j, dd, txt ); 
      }
   }
   return 0; 
}
#undef NRANSI
