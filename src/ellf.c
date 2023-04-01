
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

sReal nrc_ellf ( sReal phi, sReal ak )
{
   sReal nrc_rf ( sReal x, sReal y, sReal z ); 
   sReal s; 

   s = sin ( phi ); 
   return s*nrc_rf ( SQR ( cos ( phi ) ), ( 1.0 - s*ak )*( 1.0 + s*ak ), 1.0 ); 
}
#undef NRANSI
