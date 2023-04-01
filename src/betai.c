
#include "nrc_types.h"

#include <math.h>

sReal nrc_betai ( sReal a, sReal b, sReal x )
{
   sReal nrc_betacf ( sReal a, sReal b, sReal x ); 
   sReal nrc_gammln ( sReal xx ); 
   void nrc_error ( char error_text[] ); 
   sReal bt; 

   if ( x < 0.0 || x > 1.0 ) nrc_error ( "Bad x in routine nrc_betai" ); 
   if ( x == 0.0 || x == 1.0 ) bt = 0.0; 
   else
      bt = exp ( nrc_gammln ( a + b )- nrc_gammln ( a )- nrc_gammln ( b )+ a*log ( x )+ b*log ( 1.0 - x ) ); 
   if ( x < ( a + 1.0 )/( a + b + 2.0 ) )
      return bt*nrc_betacf ( a, b, x )/a; 
   else
      return 1.0 - bt*nrc_betacf ( b, a, 1.0 - x )/b; 
}
