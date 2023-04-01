
#include "nrc_types.h"

sReal nrc_erffc ( sReal x )
{
   sReal nrc_gammp ( sReal a, sReal x ); 
   sReal nrc_gammq ( sReal a, sReal x ); 

   return x < 0.0 ? 1.0 + nrc_gammp ( 0.5, x*x ) : nrc_gammq ( 0.5, x*x ); 
}
