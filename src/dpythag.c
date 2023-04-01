
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

dReal nrc_dpythag ( dReal a, dReal b )
{
   dReal absa, absb; 
   absa = fabs ( a ); 
   absb = fabs ( b ); 
   if ( absa > absb ) return absa*sqrt ( 1.0 + DSQR ( absb/absa ) ); 
   else return ( absb == 0.0 ? 0.0 : absb*sqrt ( 1.0 + DSQR ( absa/absb ) ) ); 
}
#undef NRANSI
