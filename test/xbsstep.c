
#include "nrc_types.h"

/* Driver for routine nrc_bsstep */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 4

sReal dxsav, *xp, **yp; /* defining declarations */
int kmax, kount; 

int nrhs; /* counts function evaluations */

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   nrhs ++; 
   dydx[1] = - y[2]; 
   dydx[2]= y[1]-( 1.0/x )*y[2]; 
   dydx[3]= y[2]-( 2.0/x )*y[3]; 
   dydx[4]= y[3]-( 3.0/x )*y[4]; 
}

int main ( void )
{
   int i, nbad, nok; 
   sReal eps = 1.0e-4, h1 = 0.1, hmin = 0.0, x1 = 1.0, x2 = 10.0, *ystart; 

   ystart = nrc_vector ( 1, N ); 
   xp = nrc_vector ( 1, 200 ); 
   yp = nrc_matrix ( 1, 10, 1, 200 ); 
   ystart[1]= nrc_bessj0 ( x1 ); 
   ystart[2]= nrc_bessj1 ( x1 ); 
   ystart[3]= nrc_bessj ( 2, x1 ); 
   ystart[4]= nrc_bessj ( 3, x1 ); 
   nrhs = 0; 
   kmax = 100; 
   dxsav =( x2 - x1 )/20.0; 
   nrc_odeint ( ystart, N, x1, x2, eps, h1, hmin, &nok, &nbad, nrc_derivs, nrc_bsstep ); 
   printf ( "\n%s %13s %3d\n", "successful steps:", " ", nok ); 
   printf ( "%s %20s %3d\n", "bad steps:", " ", nbad ); 
   printf ( "%s %9s %3d\n", "function evaluations:", " ", nrhs ); 
   printf ( "\n%s %3d\n", "stored intermediate values:    ", kount ); 
   printf ( "\n%8s %18s %15s\n", "x", "integral", "nrc_bessj ( 3, x )" ); 
   for ( i = 1; i <= kount; i ++ )
      printf ( "%10.4f %16.6f %14.6f\n", 
         xp[i], yp[4][i], nrc_bessj ( 3, xp[i] ) ); 
   nrc_free_matrix ( yp, 1, 10, 1, 200 ); 
   nrc_free_vector ( xp, 1, 200 ); 
   nrc_free_vector ( ystart, 1, N ); 
   return 0; 
}
#undef NRANSI
