
#include "nrc_types.h"

void nrc_fleg ( sReal x, sReal pl[], int nl )
{
   int j; 
   sReal twox, nrc_f2, nrc_f1, d; 

   pl[1]= 1.0; 
   pl[2]= x; 
   if ( nl > 2 ) {
      twox = 2.0*x; 
      nrc_f2 = x; 
      d = 1.0; 
      for ( j = 3; j <= nl; j ++ ) {
         nrc_f1 = d ++; 
         nrc_f2 += twox; 
         pl[j]=( nrc_f2*pl[j - 1]- nrc_f1*pl[j - 2] )/d; 
      }
   }
}
