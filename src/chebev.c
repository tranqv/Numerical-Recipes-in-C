
#include "nrc_types.h"

sReal nrc_chebev ( sReal a, sReal b, sReal c[], int m, sReal x )
{
   void nrc_error ( char error_text[] ); 
   sReal d = 0.0, dd = 0.0, sv, y, y2; 
   int j; 

   if ( ( x - a )*( x - b ) > 0.0 ) nrc_error ( "x not in range in routine nrc_chebev" ); 
   y2 = 2.0*( y =( 2.0*x - a - b )/( b - a ) ); 
   for ( j = m - 1; j >= 1; j -- ) {
      sv = d; 
      d = y2*d - dd + c[j]; 
      dd = sv; 
   }
   return y*d - dd + 0.5*c[0]; 
}
