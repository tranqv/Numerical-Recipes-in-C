
#include "nrc_types.h"

#include <math.h>
#define ITMAX 100
#define EPS     NR_CONST_EPSI

void nrc_gser ( sReal *gamser, sReal a, sReal x, sReal *gln )
{
   sReal nrc_gammln ( sReal xx ); 
   void nrc_error ( char error_text[] ); 
   int n; 
   sReal sum, del, ap; 

   *gln = nrc_gammln ( a ); 
   if ( x <= 0.0 ) {
      if ( x < 0.0 ) nrc_error ( "x less than 0 in routine nrc_gser" ); 
      *gamser = 0.0; 
      return; 
   } else {
      ap = a; 
      del = sum = 1.0/a; 
      for ( n = 1; n <= ITMAX; n ++ ) {
         ++ ap; 
         del *= x/ap; 
         sum += del; 
         if ( fabs ( del ) < fabs ( sum )*EPS ) {
            *gamser = sum*exp ( - x + a*log ( x )-( *gln ) ); 
            return; 
         }
      }
      nrc_error ( "a too large, ITMAX too small in routine nrc_gser" ); 
      return; 
   }
}
#undef ITMAX
#undef EPS
