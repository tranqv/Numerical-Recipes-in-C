
#include "nrc_types.h"

#include <math.h>
#define JMAX 20

sReal nrc_rtnewt ( void ( *funcd )( sReal, sReal *, sReal * ), sReal x1, sReal x2, 
   sReal xacc )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal df, dx, f, rtn; 

   rtn = 0.5*( x1 + x2 ); 
   for ( j = 1; j <= JMAX; j ++ ) {
      ( *funcd )( rtn, &f, &df ); 
      dx = f/df; 
      rtn -= dx; 
      if ( ( x1 - rtn )*( rtn - x2 ) < 0.0 )
         nrc_error ( "Jumped out of brackets in nrc_rtnewt" ); 
      if ( fabs ( dx ) < xacc ) return rtn; 
   }
   nrc_error ( "Maximum number of iterations exceeded in nrc_rtnewt" ); 
   return 0.0; 
}
#undef JMAX
