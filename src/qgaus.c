
#include "nrc_types.h"

sReal nrc_qgaus ( sReal ( *func )( sReal ), sReal a, sReal b )
{
   int j; 
   sReal xr, xm, dx, s; 
   static sReal x[]={0.0, 0.1488743389, 0.4333953941, 
      0.6794095682, 0.8650633666, 0.9739065285}; 
   static sReal w[]={0.0, 0.2955242247, 0.2692667193, 
      0.2190863625, 0.1494513491, 0.0666713443}; 

   xm = 0.5*( b + a ); 
   xr = 0.5*( b - a ); 
   s = 0; 
   for ( j = 1; j <= 5; j ++ ) {
      dx = xr*x[j]; 
      s += w[j]*( ( *func )( xm + dx )+( *func )( xm - dx ) ); 
   }
   return s *= xr; 
}
