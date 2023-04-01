
#include "nrc_types.h"

void nrc_crank ( unsigned long n, sReal w[], sReal *s )
{
   unsigned long j = 1, ji, jt; 
   sReal t, nrc_rank; 

   *s = 0.0; 
   while ( j < n ) {
      if ( w[j + 1] != w[j] ) {
         w[j]= j; 
         ++ j; 
      } else {
         for ( jt = j + 1; jt <= n && w[jt]== w[j]; jt ++ ); 
         nrc_rank = 0.5*( j + jt - 1 ); 
         for ( ji = j; ji <=( jt - 1 ); ji ++ ) w[ji]= nrc_rank; 
         t = jt - j; 
         *s += t*t*t - t; 
         j = jt; 
      }
   }
   if ( j == n ) w[n]= n; 
}
