
#include "nrc_types.h"

void nrc_avevar ( sReal data[], unsigned long n, sReal *ave, sReal *var )
{
   unsigned long j; 
   sReal s, ep; 

   for ( *ave = 0.0, j = 1; j <= n; j ++ ) *ave += data[j]; 
   *ave /= n; 
   *var = ep = 0.0; 
   for ( j = 1; j <= n; j ++ ) {
      s = data[j]-( *ave ); 
      ep += s; 
      *var += s*s; 
   }
   *var =( *var - ep*ep/n )/( n - 1 ); 
}
