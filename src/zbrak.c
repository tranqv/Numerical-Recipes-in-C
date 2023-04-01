
#include "nrc_types.h"

void nrc_zbrak ( sReal ( *fx )( sReal ), sReal x1, sReal x2, int n, sReal xb1[], 
   sReal xb2[], int *nb )
{
   int nbb, i; 
   sReal x, fp, fc, dx; 

   nbb = 0; 
   dx =( x2 - x1 )/n; 
   fp =( *fx )( x = x1 ); 
   for ( i = 1; i <= n; i ++ ) {
      fc =( *fx )( x += dx ); 
      if ( fc*fp <= 0.0 ) {
         xb1[++ nbb]= x - dx; 
         xb2[nbb]= x; 
         if ( *nb == nbb ) return; 

      }
      fp = fc; 
   }
   *nb = nbb; 
}
