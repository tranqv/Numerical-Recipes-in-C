
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

sReal **yy_dumb, *xx_dumb; 

void nrc_rkdumb ( sReal vstart[], int nvar, sReal x1, sReal x2, int nstep, 
   void ( *nrc_derivs )( sReal, sReal [], sReal [] ) )
{
   void nrc_rk4 ( sReal y[], sReal dydx[], int n, sReal x, sReal h, sReal yout[], 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ) ); 
   int i, k; 
   sReal x, h; 
   sReal *v, *vout, *dv; 

   v = nrc_vector ( 1, nvar ); 
   vout = nrc_vector ( 1, nvar ); 
   dv = nrc_vector ( 1, nvar ); 
   for ( i = 1; i <= nvar; i ++ ) {
      v[i]= vstart[i]; 
      yy_dumb[i][1]= v[i]; 
   }
   xx_dumb[1]= x1; 
   x = x1; 
   h =( x2 - x1 )/nstep; 
   for ( k = 1; k <= nstep; k ++ ) {
      ( *nrc_derivs )( x, v, dv ); 
      nrc_rk4 ( v, dv, nvar, x, h, vout, nrc_derivs ); 
      if ( ( sReal )( x + h ) == x ) nrc_error ( "Step size too small in routine nrc_rkdumb" ); 
      x += h; 
      xx_dumb[k + 1]= x; 
      for ( i = 1; i <= nvar; i ++ ) {
         v[i]= vout[i]; 
         yy_dumb[i][k + 1]= v[i]; 
      }
   }
   nrc_free_vector ( dv, 1, nvar ); 
   nrc_free_vector ( vout, 1, nvar ); 
   nrc_free_vector ( v, 1, nvar ); 
}
#undef NRANSI
