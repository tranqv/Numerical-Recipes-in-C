
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

sReal nrc_ellpi ( sReal phi, sReal en, sReal ak )
{
   sReal nrc_rf ( sReal x, sReal y, sReal z ); 
   sReal nrc_rj ( sReal x, sReal y, sReal z, sReal p ); 
   sReal cc, enss, q, s; 

   s = sin ( phi ); 
   enss = en*s*s; 
   cc = SQR ( cos ( phi ) ); 
   q =( 1.0 - s*ak )*( 1.0 + s*ak ); 
   return s*( nrc_rf ( cc, q, 1.0 )- enss*nrc_rj ( cc, q, 1.0, 1.0 + enss )/3.0 ); 
}
#undef NRANSI
