
#include "nrc_types.h"

#include <math.h>
#define TINY 1.0e-20

void nrc_pearsn ( sReal x[], sReal y[], unsigned long n, sReal *r, sReal *prob, 
   sReal *z )
{
   sReal nrc_betai ( sReal a, sReal b, sReal x ); 
   sReal nrc_erfcc ( sReal x ); 
   unsigned long j; 
   sReal yt, xt, t, df; 
   sReal syy = 0.0, sxy = 0.0, sxx = 0.0, ay = 0.0, ax = 0.0; 

   for ( j = 1; j <= n; j ++ ) {
      ax += x[j]; 
      ay += y[j]; 
   }
   ax /= n; 
   ay /= n; 
   for ( j = 1; j <= n; j ++ ) {
      xt = x[j]- ax; 
      yt = y[j]- ay; 
      sxx += xt*xt; 
      syy += yt*yt; 
      sxy += xt*yt; 
   }
   *r = sxy/( sqrt ( sxx*syy )+ TINY ); 
   *z = 0.5*log ( ( 1.0 +( *r )+ TINY )/( 1.0 -( *r )+ TINY ) ); 
   df = n - 2; 
   t =( *r )*sqrt ( df/( ( 1.0 -( *r )+ TINY )*( 1.0 +( *r )+ TINY ) ) ); 
   *prob = nrc_betai ( 0.5*df, 0.5, df/( df + t*t ) ); 
}
#undef TINY
