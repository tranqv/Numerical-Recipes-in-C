
#include "nrc_types.h"

sReal nrc_erff ( sReal x )
{
   sReal nrc_gammp ( sReal a, sReal x ); 

   return x < 0.0 ? - nrc_gammp ( 0.5, x*x ) : nrc_gammp ( 0.5, x*x ); 
}
