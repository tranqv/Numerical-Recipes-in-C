
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_stoerm ( sReal y[], sReal d2y[], int nv, sReal xs, sReal htot, int nstep, 
   sReal yout[], void ( *nrc_derivs )( sReal, sReal [], sReal [] ) )
{
   int i, n, neqns, nn; 
   sReal h, h2, halfh, x, *ytemp; 

   ytemp = nrc_vector ( 1, nv ); 
   h = htot/nstep; 
   halfh = 0.5*h; 
   neqns = nv/2; 
   for ( i = 1; i <= neqns; i ++ ) {
      n = neqns + i; 
      ytemp[i]= y[i]+( ytemp[n]= h*( y[n]+ halfh*d2y[i] ) ); 
   }
   x = xs + h; 
   ( *nrc_derivs )( x, ytemp, yout ); 
   h2 = h*h; 
   for ( nn = 2; nn <= nstep; nn ++ ) {
      for ( i = 1; i <= neqns; i ++ )
         ytemp[i] += ( ytemp[( n = neqns + i )] += h2*yout[i] ); 
      x += h; 
      ( *nrc_derivs )( x, ytemp, yout ); 
   }
   for ( i = 1; i <= neqns; i ++ ) {
      n = neqns + i; 
      yout[n]= ytemp[n]/h + halfh*yout[i]; 
      yout[i]= ytemp[i]; 
   }
   nrc_free_vector ( ytemp, 1, nv ); 
}
#undef NRANSI
