
#include "nrc_types.h"

#include <math.h>

dReal nrc_snrm ( unsigned long n, dReal sx[], int itol )
{
   unsigned long i, isamax; 
   dReal ans; 

   if ( itol <= 3 ) {
      ans = 0.0; 
      for ( i = 1; i <= n; i ++ ) ans += sx[i]*sx[i]; 
      return sqrt ( ans ); 
   } else {
      isamax = 1; 
      for ( i = 1; i <= n; i ++ ) {
         if ( fabs ( sx[i] ) > fabs ( sx[isamax] ) ) isamax = i; 
      }
      return fabs ( sx[isamax] ); 
   }
}
