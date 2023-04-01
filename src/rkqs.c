
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define SAFETY    0.9
#define PGROW     -0.2
#define PSHRNK    -0.25
#define ERRCON    1.89e-4

void nrc_rkqs ( sReal y[], sReal dydx[], int n, sReal *x, sReal htry, sReal eps, 
   sReal yscal[], sReal *hdid, sReal *hnext, 
   void ( *nrc_derivs )( sReal, sReal [], sReal [] ) )
{
   void nrc_rkck ( sReal y[], sReal dydx[], int n, sReal x, sReal h, 
      sReal yout[], sReal yerr[], void ( *nrc_derivs )( sReal, sReal [], sReal [] ) ); 
   int i; 
   sReal errmax, h, htemp, xnew, *yerr, *ytemp; 

   yerr = nrc_vector ( 1, n ); 
   ytemp = nrc_vector ( 1, n ); 
   h = htry; 
   for ( ; ; ) {
      nrc_rkck ( y, dydx, n, *x, h, ytemp, yerr, nrc_derivs ); 
      errmax = 0.0; 
      for ( i = 1; i <= n; i ++ ) errmax = FMAX ( errmax, fabs ( yerr[i]/yscal[i] ) ); 
      errmax /= eps; 
      if ( errmax <= 1.0 ) break; 
      htemp = SAFETY*h*pow ( errmax, PSHRNK ); 
      h =( h >= 0.0 ? FMAX ( htemp, 0.1*h ) : FMIN ( htemp, 0.1*h ) ); 
      xnew =( *x )+ h; 
      if ( xnew == *x ) nrc_error ( "stepsize underflow in nrc_rkqs" ); 
   }
   if ( errmax > ERRCON ) *hnext = SAFETY*h*pow ( errmax, PGROW ); 
   else *hnext = 5.0*h; 
   *x += ( *hdid = h ); 
   for ( i = 1; i <= n; i ++ ) y[i]= ytemp[i]; 
   nrc_free_vector ( ytemp, 1, n ); 
   nrc_free_vector ( yerr, 1, n ); 
}
#undef SAFETY
#undef PGROW
#undef PSHRNK
#undef ERRCON
#undef NRANSI
