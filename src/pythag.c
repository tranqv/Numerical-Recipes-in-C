
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

sReal nrc_pythag ( sReal a, sReal b )
{
   sReal absa, absb; 
   absa = fabs ( a ); 
   absb = fabs ( b ); 
   if ( absa > absb ) return absa*sqrt ( 1.0 + SQR ( absb/absa ) ); 
   else return ( absb == 0.0 ? 0.0 : absb*sqrt ( 1.0 + SQR ( absa/absb ) ) ); 
}
#undef NRANSI
