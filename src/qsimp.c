
#include "nrc_types.h"

#include <math.h>
#define EPS    1.0e-10
#define JMAX 20

sReal nrc_qsimp ( sReal ( *func )( sReal ), sReal a, sReal b )
{
   sReal nrc_trapzd ( sReal ( *func )( sReal ), sReal a, sReal b, int n ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal s, st, ost = 0.0, os = 0.0; 

   for ( j = 1; j <= JMAX; j ++ ) {
      st = nrc_trapzd ( func, a, b, j ); 
      s =( 4.0*st - ost )/3.0; 
      if ( j > 5 )
         if ( fabs ( s - os ) < EPS*fabs ( os ) ||
            ( s == 0.0 && os == 0.0 ) ) return s; 
      os = s; 
      ost = st; 
   }
   nrc_error ( "Too many steps in routine nrc_qsimp" ); 
   return 0.0; 
}
#undef EPS
#undef JMAX
