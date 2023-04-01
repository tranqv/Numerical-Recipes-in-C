
#include "nrc_types.h"

#include <math.h>
#define JMAX 40

sReal nrc_rtbis ( sReal ( *func )( sReal ), sReal x1, sReal x2, sReal xacc )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal dx, f, fmid, xmid, rtb; 

   f =( *func )( x1 ); 
   fmid =( *func )( x2 ); 
   if ( f*fmid >= 0.0 ) nrc_error ( "Root must be bracketed for bisection in nrc_rtbis" ); 
   rtb = f < 0.0 ? ( dx = x2 - x1, x1 ) : ( dx = x1 - x2, x2 ); 
   for ( j = 1; j <= JMAX; j ++ ) {
      fmid =( *func )( xmid = rtb +( dx *= 0.5 ) ); 
      if ( fmid <= 0.0 ) rtb = xmid; 
      if ( fabs ( dx ) < xacc || fmid == 0.0 ) return rtb; 
   }
   nrc_error ( "Too many bisections in nrc_rtbis" ); 
   return 0.0; 
}
#undef JMAX
