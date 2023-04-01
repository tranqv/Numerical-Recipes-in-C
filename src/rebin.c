
#include "nrc_types.h"

void nrc_rebin ( sReal nrc_rc, int nd, sReal r[], sReal xin[], sReal xi[] )
{
   int i, k = 0; 
   sReal dr = 0.0, xn = 0.0, xo = 0.0; 

   for ( i = 1; i < nd; i ++ ) {
      while ( nrc_rc > dr )
         dr += r[++ k]; 
      if ( k > 1 ) xo = xi[k - 1]; 
      xn = xi[k]; 
      dr -= nrc_rc; 
      xin[i]= xn -( xn - xo )*dr/r[k]; 
   }
   for ( i = 1; i < nd; i ++ ) xi[i]= xin[i]; 
   xi[nd]= 1.0; 
}
