
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

extern sReal **d, *x; 

void nrc_pzextr ( int iest, sReal xest, sReal yest[], sReal yz[], sReal dy[], int nv )
{
   int k1, j; 
   sReal q, nrc_f2, nrc_f1, delta, *c; 

   c = nrc_vector ( 1, nv ); 
   x[iest]= xest; 
   for ( j = 1; j <= nv; j ++ ) dy[j]= yz[j]= yest[j]; 
   if ( iest == 1 ) {
      for ( j = 1; j <= nv; j ++ ) d[j][1]= yest[j]; 
   } else {
      for ( j = 1; j <= nv; j ++ ) c[j]= yest[j]; 
      for ( k1 = 1; k1 < iest; k1 ++ ) {
         delta = 1.0/( x[iest - k1]- xest ); 
         nrc_f1 = xest*delta; 
         nrc_f2 = x[iest - k1]*delta; 
         for ( j = 1; j <= nv; j ++ ) {
            q = d[j][k1]; 
            d[j][k1]= dy[j]; 
            delta = c[j]- q; 
            dy[j]= nrc_f1*delta; 
            c[j]= nrc_f2*delta; 
            yz[j] += dy[j]; 
         }
      }
      for ( j = 1; j <= nv; j ++ ) d[j][iest]= dy[j]; 
   }
   nrc_free_vector ( c, 1, nv ); 
}
#undef NRANSI
