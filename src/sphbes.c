
#include "nrc_types.h"

#include <math.h>
#define RTPIO2 1.25331413731550025120788264240552262650

void nrc_sphbes ( int n, sReal x, sReal *sj, sReal *sy, sReal *sjp, sReal *syp )
{
   void nrc_bessjy ( sReal x, sReal xnu, sReal *nrc_rj, sReal *ry, sReal *rjp, 
      sReal *ryp ); 
   void nrc_error ( char error_text[] ); 
   sReal factor, order, nrc_rj, rjp, ry, ryp; 

   if ( n < 0 || x <= 0.0 ) nrc_error ( "bad arguments in nrc_sphbes" ); 
   order = n + 0.5; 
   nrc_bessjy ( x, order, &nrc_rj, &ry, &rjp, &ryp ); 
   factor = RTPIO2/sqrt ( x ); 
   *sj = factor*nrc_rj; 
   *sy = factor*ry; 
   *sjp = factor*rjp -( *sj )/( 2.0*x ); 
   *syp = factor*ryp -( *sy )/( 2.0*x ); 
}
#undef RTPIO2
