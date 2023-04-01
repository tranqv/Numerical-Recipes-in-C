
#include "nrc_types.h"

extern long idum; 

void nrc_ranpt ( sReal pt[], sReal regn[], int n )
{
   sReal nrc_ran1 ( long *idum ); 
   int j; 

   for ( j = 1; j <= n; j ++ )
      pt[j]= regn[j]+( regn[n + j]- regn[j] )*nrc_ran1 ( &idum ); 
}
