
#include "nrc_types.h"

/* Driver for routine nrc_rkdumb */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NVAR 4
#define NSTEP 150

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   dydx[1] = - y[2]; 
   dydx[2]= y[1]-( 1.0/x )*y[2]; 
   dydx[3]= y[2]-( 2.0/x )*y[3]; 
   dydx[4]= y[3]-( 3.0/x )*y[4]; 
}

extern sReal **yy_dumb, *xx_dumb; /* referencing declaration */

int main ( void )
{
   int j; 
   sReal x1 = 1.0, x2 = 20.0, *vstart; 

   vstart = nrc_vector ( 1, NVAR ); 
   /* Note: The arrays xx_dumb and y must have indices up to NSTEP + 1 */
   xx_dumb = nrc_vector ( 1, NSTEP + 1 ); 
   yy_dumb = nrc_matrix ( 1, NVAR, 1, NSTEP + 1 ); 
   vstart[1]= nrc_bessj0 ( x1 ); 
   vstart[2]= nrc_bessj1 ( x1 ); 
   vstart[3]= nrc_bessj ( 2, x1 ); 
   vstart[4]= nrc_bessj ( 3, x1 ); 
   nrc_rkdumb ( vstart, NVAR, x1, x2, NSTEP, nrc_derivs ); 
   printf ( "%8s %17s %10s\n", "x", "integrated", "bessj3" ); 
   for ( j = 10; j <= NSTEP; j += 10 )
      printf ( "%10.4f %14.6f %12.6f\n", 
         xx_dumb[j], yy_dumb[4][j], nrc_bessj ( 3, xx_dumb[j] ) ); 
   nrc_free_matrix ( yy_dumb, 1, NVAR, 1, NSTEP + 1 ); 
   nrc_free_vector ( xx_dumb, 1, NSTEP + 1 ); 
   nrc_free_vector ( vstart, 1, NVAR ); 
   return 0; 
}
#undef NRANSI
