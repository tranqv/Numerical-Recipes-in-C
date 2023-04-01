
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

sReal nrc_elle ( sReal phi, sReal ak )
{
   sReal nrc_rd ( sReal x, sReal y, sReal z ); 
   sReal nrc_rf ( sReal x, sReal y, sReal z ); 
   sReal cc, q, s; 

   s = sin ( phi ); 
   cc = SQR ( cos ( phi ) ); 
   q =( 1.0 - s*ak )*( 1.0 + s*ak ); 
   return s*( nrc_rf ( cc, q, 1.0 )-( SQR ( s*ak ) )*nrc_rd ( cc, q, 1.0 )/3.0 ); 
}
#undef NRANSI
