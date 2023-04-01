
#include "nrc_types.h"

void nrc_jacobn ( sReal x, sReal y[], sReal dfdx[], sReal **dfdy, int n )
{
   int i; 

   for ( i = 1; i <= n; i ++ ) dfdx[i]= 0.0; 
   dfdy[1][1] = - 0.013 - 1000.0*y[3]; 
   dfdy[1][2]= 0.0; 
   dfdy[1][3] = - 1000.0*y[1]; 
   dfdy[2][1]= 0.0; 
   dfdy[2][2] = - 2500.0*y[3]; 
   dfdy[2][3] = - 2500.0*y[2]; 
   dfdy[3][1] = - 0.013 - 1000.0*y[3]; 
   dfdy[3][2] = - 2500.0*y[3]; 
   dfdy[3][3] = - 1000.0*y[1]- 2500.0*y[2]; 
}

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   dydx[1] = - 0.013*y[1]- 1000.0*y[1]*y[3]; 
   dydx[2] = - 2500.0*y[2]*y[3]; 
   dydx[3] = - 0.013*y[1]- 1000.0*y[1]*y[3]- 2500.0*y[2]*y[3]; 
}
