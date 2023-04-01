
#include "nrc_types.h"

#include <math.h>
#define MAXIT 30

sReal nrc_rtsec ( sReal ( *func )( sReal ), sReal x1, sReal x2, sReal xacc )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal fl, f, dx, swap, xl, rts; 

   fl =( *func )( x1 ); 
   f =( *func )( x2 ); 
   if ( fabs ( fl ) < fabs ( f ) ) {
      rts = x1; 
      xl = x2; 
      swap = fl; 
      fl = f; 
      f = swap; 
   } else {
      xl = x1; 
      rts = x2; 
   }
   for ( j = 1; j <= MAXIT; j ++ ) {
      dx =( xl - rts )*f/( f - fl ); 
      xl = rts; 
      fl = f; 
      rts += dx; 
      f =( *func )( rts ); 
      if ( fabs ( dx ) < xacc || f == 0.0 ) return rts; 
   }
   nrc_error ( "Maximum number of iterations exceeded in nrc_rtsec" ); 
   return 0.0; 
}
#undef MAXIT
