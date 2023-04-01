
#include "nrc_types.h"

sReal nrc_fredin ( sReal x, int n, sReal a, sReal b, sReal t[], sReal f[], 
   sReal w[], sReal ( *g )( sReal ), sReal ( *ak )( sReal, sReal ) )
{
   int i; 
   sReal sum = 0.0; 

   for ( i = 1; i <= n; i ++ ) sum += ( *ak )( x, t[i] )*w[i]*f[i]; 
   return ( *g )( x )+ sum; 
}
