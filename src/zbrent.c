
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define ITMAX 100
#define EPS     NR_CONST_EPSI

sReal nrc_zbrent ( sReal ( *func )( sReal ), sReal x1, sReal x2, sReal tol )
{
   int iter; 
   sReal a = x1, b = x2, c = x2, d, e, min1, min2; 
   sReal fa =( *func )( a ), fb =( *func )( b ), fc, p, q, r, s, tol1, xm; 

   if ( ( fa > 0.0 && fb > 0.0 ) || ( fa < 0.0 && fb < 0.0 ) )
      nrc_error ( "Root must be bracketed in nrc_zbrent" ); 
   fc = fb; 
   for ( iter = 1; iter <= ITMAX; iter ++ ) {
      if ( ( fb > 0.0 && fc > 0.0 ) || ( fb < 0.0 && fc < 0.0 ) ) {
         c = a; 
         fc = fa; 
         e = d = b - a; 
      }
      if ( fabs ( fc ) < fabs ( fb ) ) {
         a = b; 
         b = c; 
         c = a; 
         fa = fb; 
         fb = fc; 
         fc = fa; 
      }
      tol1 = 2.0*EPS*fabs ( b )+ 0.5*tol; 
      xm = 0.5*( c - b ); 
      if ( fabs ( xm ) <= tol1 || fb == 0.0 ) return b; 
      if ( fabs ( e ) >= tol1 && fabs ( fa ) > fabs ( fb ) ) {
         s = fb/fa; 
         if ( a == c ) {
            p = 2.0*xm*s; 
            q = 1.0 - s; 
         } else {
            q = fa/fc; 
            r = fb/fc; 
            p = s*( 2.0*xm*q*( q - r )-( b - a )*( r - 1.0 ) ); 
            q =( q - 1.0 )*( r - 1.0 )*( s - 1.0 ); 
         }
         if ( p > 0.0 ) q = - q; 
         p = fabs ( p ); 
         min1 = 3.0*xm*q - fabs ( tol1*q ); 
         min2 = fabs ( e*q ); 
         if ( 2.0*p < ( min1 < min2 ? min1 : min2 ) ) {
            e = d; 
            d = p/q; 
         } else {
            d = xm; 
            e = d; 
         }
      } else {
         d = xm; 
         e = d; 
      }
      a = b; 
      fa = fb; 
      if ( fabs ( d ) > tol1 )
         b += d; 
      else
         b += SIGN ( tol1, xm ); 
      fb =( *func )( b ); 
   }
   nrc_error ( "Maximum number of iterations exceeded in nrc_zbrent" ); 
   return 0.0; 
}
#undef ITMAX
#undef EPS
#undef NRANSI
