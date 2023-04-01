
#include "nrc_types.h"

#include <math.h>
#define PI 3.141592653589793238462643383279502884197

sReal nrc_poidev ( sReal xm, long *idum )
{
   sReal nrc_gammln ( sReal xx ); 
   sReal nrc_ran1 ( long *idum ); 
   static sReal sq, alxm, g, oldm =( - 1.0 ); 
   sReal em, t, y; 

   if ( xm < 12.0 ) {
      if ( xm != oldm ) {
         oldm = xm; 
         g = exp ( - xm ); 
      }
      em = - 1; 
      t = 1.0; 
      do {
         ++ em; 
         t *= nrc_ran1 ( idum ); 
      } while ( t > g ); 
   } else {
      if ( xm != oldm ) {
         oldm = xm; 
         sq = sqrt ( 2.0*xm ); 
         alxm = log ( xm ); 
         g = xm*alxm - nrc_gammln ( xm + 1.0 ); 
      }
      do {
         do {
            y = tan ( PI*nrc_ran1 ( idum ) ); 
            em = sq*y + xm; 
         } while ( em < 0.0 ); 
         em = floor ( em ); 
         t = 0.9*( 1.0 + y*y )*exp ( em*alxm - nrc_gammln ( em + 1.0 )- g ); 
      } while ( nrc_ran1 ( idum ) > t ); 
   }
   return em; 
}
#undef PI
