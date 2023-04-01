
#include "nrc_types.h"

#include <math.h>
#define PI 3.141592653589793238462643383279502884197
#define THIRD (1.0/3.0)
#define TWOTHR (2.0*THIRD)
#define ONOVRT 0.5773502691896257645091487805019574556476

void nrc_airy ( sReal x, sReal *ai, sReal *bi, sReal *aip, sReal *bip )
{
   void nrc_bessik ( sReal x, sReal xnu, sReal *ri, sReal *rk, sReal *rip, 
      sReal *rkp ); 
   void nrc_bessjy ( sReal x, sReal xnu, sReal *nrc_rj, sReal *ry, sReal *rjp, 
      sReal *ryp ); 
   sReal absx, ri, rip, nrc_rj, rjp, rk, rkp, rootx, ry, ryp, z; 

   absx = fabs ( x ); 
   rootx = sqrt ( absx ); 
   z = TWOTHR*absx*rootx; 
   if ( x > 0.0 ) {
      nrc_bessik ( z, THIRD, &ri, &rk, &rip, &rkp ); 
      *ai = rootx*ONOVRT*rk/PI; 
      *bi = rootx*( rk/PI + 2.0*ONOVRT*ri ); 
      nrc_bessik ( z, TWOTHR, &ri, &rk, &rip, &rkp ); 
      *aip = - x*ONOVRT*rk/PI; 
      *bip = x*( rk/PI + 2.0*ONOVRT*ri ); 
   } else if ( x < 0.0 ) {
      nrc_bessjy ( z, THIRD, &nrc_rj, &ry, &rjp, &ryp ); 
      *ai = 0.5*rootx*( nrc_rj - ONOVRT*ry ); 
      *bi = - 0.5*rootx*( ry + ONOVRT*nrc_rj ); 
      nrc_bessjy ( z, TWOTHR, &nrc_rj, &ry, &rjp, &ryp ); 
      *aip = 0.5*absx*( ONOVRT*ry + nrc_rj ); 
      *bip = 0.5*absx*( ONOVRT*nrc_rj - ry ); 
   } else {
      *ai = 0.355028053887817; 
      *bi =( *ai )/ONOVRT; 
      *aip = - 0.258819403792807; 
      *bip = -( *aip )/ONOVRT; 
   }
}
#undef PI
#undef THIRD
#undef TWOTHR
#undef ONOVRT
