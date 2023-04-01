
#include "nrc_types.h"

#define FUNC(x) ((*func)(x))

sReal nrc_midpnt ( sReal ( *func )( sReal ), sReal a, sReal b, int n )
{
   sReal x, tnm, sum, del, ddel; 
   static sReal s; 
   int it, j; 

   if ( n == 1 ) {
      return ( s =( b - a )*FUNC ( 0.5*( a + b ) ) ); 
   } else {
      for ( it = 1, j = 1; j < n - 1; j ++ ) it *= 3; 
      tnm = it; 
      del =( b - a )/( 3.0*tnm ); 
      ddel = del + del; 
      x = a + 0.5*del; 
      sum = 0.0; 
      for ( j = 1; j <= it; j ++ ) {
         sum += FUNC ( x ); 
         x += ddel; 
         sum += FUNC ( x ); 
         x += del; 
      }
      s =( s +( b - a )*sum/tnm )/3.0; 
      return s; 
   }
}
#undef FUNC
