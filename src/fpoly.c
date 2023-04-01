
#include "nrc_types.h"

void nrc_fpoly ( sReal x, sReal p[], int np )
{
   int j; 

   p[1]= 1.0; 
   for ( j = 2; j <= np; j ++ ) p[j]= p[j - 1]*x; 
}
