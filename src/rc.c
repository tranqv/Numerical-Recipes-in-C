
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define ERRTOL    0.0012
#define TINY      1.69e-38
#define SQRTNY    1.3e-19
#define BIG       3.0e37
#define TNBG (TINY*BIG)
#define COMP1 (2.236/SQRTNY)
#define COMP2 (TNBG*TNBG/25.0)
#define THIRD (1.0/3.0)
#define C1 0.3
#define C2 (1.0/7.0)
#define C3 0.375
#define C4 (9.0/22.0)

sReal nrc_rc ( sReal x, sReal y )
{
   sReal alamb, ave, s, w, xt, yt; 
   if ( x < 0.0 || y == 0.0 || ( x + fabs ( y ) ) < TINY || ( x + fabs ( y ) ) > BIG ||
      ( y <- COMP1 && x > 0.0 && x < COMP2 ) )
         nrc_error ( "invalid arguments in nrc_rc" ); 
   if ( y > 0.0 ) {
      xt = x; 
      yt = y; 
      w = 1.0; 
   } else {
      xt = x - y; 
      yt = - y; 
      w = sqrt ( x )/sqrt ( xt ); 
   }
   do {
      alamb = 2.0*sqrt ( xt )*sqrt ( yt )+ yt; 
      xt = 0.25*( xt + alamb ); 
      yt = 0.25*( yt + alamb ); 
      ave = THIRD*( xt + yt + yt ); 
      s =( yt - ave )/ave; 
   } while ( fabs ( s ) > ERRTOL ); 
   return w*( 1.0 + s*s*( C1 + s*( C2 + s*( C3 + s*C4 ) ) ) )/sqrt ( ave ); 
}
#undef ERRTOL
#undef TINY
#undef SQRTNY
#undef BIG
#undef TNBG
#undef COMP1
#undef COMP2
#undef THIRD
#undef C1
#undef C2
#undef C3
#undef C4
#undef NRANSI
