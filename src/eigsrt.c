
#include "nrc_types.h"

void nrc_eigsrt ( sReal d[], sReal **v, int n )
{
   int k, j, i; 
   sReal p; 

   for ( i = 1; i < n; i ++ ) {
      p = d[k = i]; 
      for ( j = i + 1; j <= n; j ++ )
         if ( d[j] >= p ) p = d[k = j]; 
      if ( k != i ) {
         d[k]= d[i]; 
         d[i]= p; 
         for ( j = 1; j <= n; j ++ ) {
            p = v[j][i]; 
            v[j][i]= v[j][k]; 
            v[j][k]= p; 
         }
      }
   }
}
