
#include "nrc_types.h"

#include <math.h>

sReal nrc_bessk0 ( sReal x )
{
   sReal nrc_bessi0 ( sReal x ); 
   dReal y, ans; 

   if ( x <= 2.0 ) {
      y = x*x/4.0; 
      ans =( - log ( x/2.0 )*nrc_bessi0 ( x ) )+( - 0.577215664901532860606512090082402431042 + y*( 0.42278420
         + y*( 0.23069756 + y*( 0.3488590e-1 + y*( 0.262698e-2
         + y*( 0.10750e-3 + y*0.74e-5 ) ) ) ) ) ); 
   } else {
      y = 2.0/x; 
      ans =( exp ( - x )/sqrt ( x ) )*( 1.25331413731550025120788264240552262650 + y*( - 0.7832358e-1
         + y*( 0.2189568e-1 + y*( - 0.1062446e-1 + y*( 0.587872e-2
         + y*( - 0.251540e-2 + y*0.53208e-3 ) ) ) ) ) ); 
   }
   return ans; 
}
