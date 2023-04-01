
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

extern sReal **d, *x; 

void nrc_rzextr ( int iest, sReal xest, sReal yest[], sReal yz[], sReal dy[], int nv )
{
   int k, j; 
   sReal yy, v, ddy, c, b1, b, *fx; 

   fx = nrc_vector ( 1, iest ); 
   x[iest]= xest; 
   if ( iest == 1 )
      for ( j = 1; j <= nv; j ++ ) {
         yz[j]= yest[j]; 
         d[j][1]= yest[j]; 
         dy[j]= yest[j]; 
      }
   else {
      for ( k = 1; k < iest; k ++ )
         fx[k + 1]= x[iest - k]/xest; 
      for ( j = 1; j <= nv; j ++ ) {
         v = d[j][1]; 
         d[j][1]= yy = c = yest[j]; 
         for ( k = 2; k <= iest; k ++ ) {
            b1 = fx[k]*v; 
            b = b1 - c; 
            if ( b ) {
               b =( c - v )/b; 
               ddy = c*b; 
               c = b1*b; 
            } else
               ddy = v; 
            if ( k != iest ) v = d[j][k]; 
            d[j][k]= ddy; 
            yy += ddy; 
         }
         dy[j]= ddy; 
         yz[j]= yy; 
      }
   }
   nrc_free_vector ( fx, 1, iest ); 
}
#undef NRANSI
