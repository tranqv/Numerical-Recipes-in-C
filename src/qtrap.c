
#include "nrc_types.h"

#include <math.h>
#define EPS    1.0e-10
#define JMAX 20

sReal nrc_qtrap ( sReal ( *func )( sReal ), sReal a, sReal b )
{
   sReal nrc_trapzd ( sReal ( *func )( sReal ), sReal a, sReal b, int n ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal s, olds = 0.0; 

   for ( j = 1; j <= JMAX; j ++ ) {
      s = nrc_trapzd ( func, a, b, j ); 
      if ( j > 5 )
         if ( fabs ( s - olds ) < EPS*fabs ( olds ) ||
            ( s == 0.0 && olds == 0.0 ) ) return s; 
      olds = s; 
   }
   nrc_error ( "Too many steps in routine nrc_qtrap" ); 
   return 0.0; 
}
#undef EPS
#undef JMAX
