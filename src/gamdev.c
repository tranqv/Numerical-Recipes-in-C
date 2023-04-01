
#include "nrc_types.h"

#include <math.h>

sReal nrc_gamdev ( int ia, long *idum )
{
   sReal nrc_ran1 ( long *idum ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal am, e, s, v1, v2, x, y; 

   if ( ia < 1 ) nrc_error ( "Error in routine nrc_gamdev" ); 
   if ( ia < 6 ) {
      x = 1.0; 
      for ( j = 1; j <= ia; j ++ ) x *= nrc_ran1 ( idum ); 
      x = - log ( x ); 
   } else {
      do {
         do {
            do {
               v1 = nrc_ran1 ( idum ); 
               v2 = 2.0*nrc_ran1 ( idum )- 1.0; 
            } while ( v1*v1 + v2*v2 > 1.0 ); 
            y = v2/v1; 
            am = ia - 1; 
            s = sqrt ( 2.0*am + 1.0 ); 
            x = s*y + am; 
         } while ( x <= 0.0 ); 
         e =( 1.0 + y*y )*exp ( am*log ( x/am )- s*y ); 
      } while ( nrc_ran1 ( idum ) > e ); 
   }
   return x; 
}
