
#include "nrc_types.h"

#define FUNC(x) ((*func)(x))

sReal nrc_trapzd ( sReal ( *func )( sReal ), sReal a, sReal b, int n )
{
   sReal x, tnm, sum, del; 
   static sReal s; 
   int it, j; 

   if ( n == 1 ) {
      return ( s = 0.5*( b - a )*( FUNC ( a )+ FUNC ( b ) ) ); 
   } else {
      for ( it = 1, j = 1; j < n - 1; j ++ ) it <<= 1; 
      tnm = it; 
      del =( b - a )/tnm; 
      x = a + 0.5*del; 
      for ( sum = 0.0, j = 1; j <= it; j ++, x += del ) sum += FUNC ( x ); 
      s = 0.5*( s +( b - a )*sum/tnm ); 
      return s; 
   }
}
#undef FUNC
