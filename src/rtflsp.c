
#include "nrc_types.h"

#include <math.h>
#define MAXIT 30

sReal nrc_rtflsp ( sReal ( *func )( sReal ), sReal x1, sReal x2, sReal xacc )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal fl, fh, xl, xh, swap, dx, del, f, rtf; 

   fl =( *func )( x1 ); 
   fh =( *func )( x2 ); 
   if ( fl*fh > 0.0 ) nrc_error ( "Root must be bracketed in nrc_rtflsp" ); 
   if ( fl < 0.0 ) {
      xl = x1; 
      xh = x2; 
   } else {
      xl = x2; 
      xh = x1; 
      swap = fl; 
      fl = fh; 
      fh = swap; 
   }
   dx = xh - xl; 
   for ( j = 1; j <= MAXIT; j ++ ) {
      rtf = xl + dx*fl/( fl - fh ); 
      f =( *func )( rtf ); 
      if ( f < 0.0 ) {
         del = xl - rtf; 
         xl = rtf; 
         fl = f; 
      } else {
         del = xh - rtf; 
         xh = rtf; 
         fh = f; 
      }
      dx = xh - xl; 
      if ( fabs ( del ) < xacc || f == 0.0 ) return rtf; 
   }
   nrc_error ( "Maximum number of iterations exceeded in nrc_rtflsp" ); 
   return 0.0; 
}
#undef MAXIT
