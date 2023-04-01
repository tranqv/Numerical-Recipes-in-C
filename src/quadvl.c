
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_quadvl ( sReal x, sReal y, sReal *fa, sReal *fb, sReal *fc, sReal *fd )
{
   sReal qa, qb, qc, qd; 

   qa = FMIN ( 2.0, FMAX ( 0.0, 1.0 - x ) ); 
   qb = FMIN ( 2.0, FMAX ( 0.0, 1.0 - y ) ); 
   qc = FMIN ( 2.0, FMAX ( 0.0, x + 1.0 ) ); 
   qd = FMIN ( 2.0, FMAX ( 0.0, y + 1.0 ) ); 
   *fa = 0.25*qa*qb; 
   *fb = 0.25*qb*qc; 
   *fc = 0.25*qc*qd; 
   *fd = 0.25*qd*qa; 
}
#undef NRANSI
