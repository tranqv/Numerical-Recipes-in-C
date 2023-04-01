
#include "nrc_types.h"

void nrc_addint ( dReal **uf, dReal **uc, dReal **res, int nf )
{
   void nrc_interp ( dReal **uf, dReal **uc, int nf ); 
   int i, j; 

   nrc_interp ( res, uc, nf ); 
   for ( j = 1; j <= nf; j ++ )
      for ( i = 1; i <= nf; i ++ )
         uf[i][j] += res[i][j]; 
}
