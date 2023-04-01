
#include "nrc_types.h"

sReal nrc_gammq ( sReal a, sReal x )
{
   void nrc_gcf ( sReal *gammcf, sReal a, sReal x, sReal *gln ); 
   void nrc_gser ( sReal *gamser, sReal a, sReal x, sReal *gln ); 
   void nrc_error ( char error_text[] ); 
   sReal gamser, gammcf, gln; 

   if ( x < 0.0 || a <= 0.0 ) nrc_error ( "Invalid arguments in routine nrc_gammq" ); 
   if ( x < ( a + 1.0 ) ) {
      nrc_gser ( &gamser, a, x, &gln ); 
      return 1.0 - gamser; 
   } else {
      nrc_gcf ( &gammcf, a, x, &gln ); 
      return gammcf; 
   }
}
