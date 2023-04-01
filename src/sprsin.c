
#include "nrc_types.h"

#include <math.h>

void nrc_sprsin ( sReal **a, int n, sReal thresh, unsigned long nmax, sReal sa[], 
   unsigned long ija[] )
{
   void nrc_error ( char error_text[] ); 
   int i, j; 
   unsigned long k; 

   for ( j = 1; j <= n; j ++ ) sa[j]= a[j][j]; 
   ija[1]= n + 2; 
   k = n + 1; 
   for ( i = 1; i <= n; i ++ ) {
      for ( j = 1; j <= n; j ++ ) {
         if ( fabs ( a[i][j] ) >= thresh && i != j ) {
            if ( ++ k > nmax ) nrc_error ( "nrc_sprsin: nmax too small" ); 
            sa[k]= a[i][j]; 
            ija[k]= j; 
         }
      }
      ija[i + 1]= k + 1; 
   }
}
