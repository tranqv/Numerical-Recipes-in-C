
#include "nrc_types.h"

#include <math.h>

void nrc_simp1 ( sReal **a, int mm, int ll[], int nll, int iabf, int *kp, 
   sReal *bmax )
{
   int k; 
   sReal test; 

   if ( nll <= 0 )
      *bmax = 0.0; 
   else {
      *kp = ll[1]; 
      *bmax = a[mm + 1][*kp + 1]; 
      for ( k = 2; k <= nll; k ++ ) {
         if ( iabf == 0 )
            test = a[mm + 1][ll[k]+ 1]-( *bmax ); 
         else
            test = fabs ( a[mm + 1][ll[k]+ 1] )- fabs ( *bmax ); 
         if ( test > 0.0 ) {
            *bmax = a[mm + 1][ll[k]+ 1]; 
            *kp = ll[k]; 
         }
      }
   }
}
