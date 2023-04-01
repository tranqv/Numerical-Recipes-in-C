
#include "nrc_types.h"

#include <math.h>
#define R 0.61803399
#define C (1.0-R)
#define SHFT2(a,b,c) (a)=(b);(b)=(c);
#define SHFT3(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

sReal nrc_golden ( sReal ax, sReal bx, sReal cx, sReal ( *f )( sReal ), sReal tol, 
   sReal *xmin )
{
   sReal nrc_f1, nrc_f2, x0, x1, x2, x3; 

   x0 = ax; 
   x3 = cx; 
   if ( fabs ( cx - bx ) > fabs ( bx - ax ) ) {
      x1 = bx; 
      x2 = bx + C*( cx - bx ); 
   } else {
      x2 = bx; 
      x1 = bx - C*( bx - ax ); 
   }
   nrc_f1 =( *f )( x1 ); 
   nrc_f2 =( *f )( x2 ); 
   while ( fabs ( x3 - x0 ) > tol*( fabs ( x1 )+ fabs ( x2 ) ) ) {
      if ( nrc_f2 < nrc_f1 ) {
         SHFT3 ( x0, x1, x2, R*x1 + C*x3 )
         SHFT2 ( nrc_f1, nrc_f2, ( *f )( x2 ) )
      } else {
         SHFT3 ( x3, x2, x1, R*x2 + C*x0 )
         SHFT2 ( nrc_f2, nrc_f1, ( *f )( x1 ) )
      }
   }
   if ( nrc_f1 < nrc_f2 ) {
      *xmin = x1; 
      return nrc_f1; 
   } else {
      *xmin = x2; 
      return nrc_f2; 
   }
}
#undef C
#undef R
#undef SHFT2
#undef SHFT3
