
#include "nrc_types.h"

#include <math.h>
#define MAXIT 100

sReal nrc_rtsafe ( void ( *funcd )( sReal, sReal *, sReal * ), sReal x1, sReal x2, 
   sReal xacc )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal df, dx, dxold, f, fh, fl; 
   sReal temp, xh, xl, rts; 

   ( *funcd )( x1, &fl, &df ); 
   ( *funcd )( x2, &fh, &df ); 
   if ( ( fl > 0.0 && fh > 0.0 ) || ( fl < 0.0 && fh < 0.0 ) )
      nrc_error ( "Root must be bracketed in nrc_rtsafe" ); 
   if ( fl == 0.0 ) return x1; 
   if ( fh == 0.0 ) return x2; 
   if ( fl < 0.0 ) {
      xl = x1; 
      xh = x2; 
   } else {
      xh = x1; 
      xl = x2; 
   }
   rts = 0.5*( x1 + x2 ); 
   dxold = fabs ( x2 - x1 ); 
   dx = dxold; 
   ( *funcd )( rts, &f, &df ); 
   for ( j = 1; j <= MAXIT; j ++ ) {
      if ( ( ( ( rts - xh )*df - f )*( ( rts - xl )*df - f ) > 0.0 )
         || ( fabs ( 2.0*f ) > fabs ( dxold*df ) ) ) {
         dxold = dx; 
         dx = 0.5*( xh - xl ); 
         rts = xl + dx; 
         if ( xl == rts ) return rts; 
      } else {
         dxold = dx; 
         dx = f/df; 
         temp = rts; 
         rts -= dx; 
         if ( temp == rts ) return rts; 
      }
      if ( fabs ( dx ) < xacc ) return rts; 
      ( *funcd )( rts, &f, &df ); 
      if ( f < 0.0 )
         xl = rts; 
      else
         xh = rts; 
   }
   nrc_error ( "Maximum number of iterations exceeded in nrc_rtsafe" ); 
   return 0.0; 
}
#undef MAXIT
