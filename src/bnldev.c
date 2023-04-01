
#include "nrc_types.h"

#include <math.h>
#define PI 3.141592653589793238462643383279502884197

sReal nrc_bnldev ( sReal pp, int n, long *idum )
{
   sReal nrc_gammln ( sReal xx ); 
   sReal nrc_ran1 ( long *idum ); 
   int j; 
   static int nold =( - 1 ); 
   sReal am, em, g, angle, p, bnl, sq, t, y; 
   static sReal pold =( - 1.0 ), pc, plog, pclog, en, oldg; 

   p =( pp <= 0.5 ? pp : 1.0 - pp ); 
   am = n*p; 
   if ( n < 25 ) {
      bnl = 0.0; 
      for ( j = 1; j <= n; j ++ )
         if ( nrc_ran1 ( idum ) < p ) ++ bnl; 
   } else if ( am < 1.0 ) {
      g = exp ( - am ); 
      t = 1.0; 
      for ( j = 0; j <= n; j ++ ) {
         t *= nrc_ran1 ( idum ); 
         if ( t < g ) break; 
      }
      bnl =( j <= n ? j : n ); 
   } else {
      if ( n != nold ) {
         en = n; 
         oldg = nrc_gammln ( en + 1.0 ); 
         nold = n; 
      } if ( p != pold ) {
         pc = 1.0 - p; 
         plog = log ( p ); 
         pclog = log ( pc ); 
         pold = p; 
      }
      sq = sqrt ( 2.0*am*pc ); 
      do {
         do {
            angle = PI*nrc_ran1 ( idum ); 
            y = tan ( angle ); 
            em = sq*y + am; 
         } while ( em < 0.0 || em >= ( en + 1.0 ) ); 
         em = floor ( em ); 
         t = 1.2*sq*( 1.0 + y*y )*exp ( oldg - nrc_gammln ( em + 1.0 )
            - nrc_gammln ( en - em + 1.0 )+ em*plog +( en - em )*pclog ); 
      } while ( nrc_ran1 ( idum ) > t ); 
      bnl = em; 
   }
   if ( p != pp ) bnl = n - bnl; 
   return bnl; 
}
#undef PI
