
#include "nrc_types.h"

/* Driver for routine nrc_rkqs */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 4

void nrc_derivs ( sReal x, sReal y[], sReal dydx[] )
{
   dydx[1] = - y[2]; 
   dydx[2]= y[1]-( 1.0/x )*y[2]; 
   dydx[3]= y[2]-( 2.0/x )*y[3]; 
   dydx[4]= y[3]-( 3.0/x )*y[4]; 
}

int main ( void )
{
   int i, j; 
   sReal eps, hdid, hnext, htry, x = 1.0, *y, *dydx, *dysav, *ysav, *yscal; 

   y = nrc_vector ( 1, N ); 
   dydx = nrc_vector ( 1, N ); 
   dysav = nrc_vector ( 1, N ); 
   ysav = nrc_vector ( 1, N ); 
   yscal = nrc_vector ( 1, N ); 
   ysav[1]= nrc_bessj0 ( x ); 
   ysav[2]= nrc_bessj1 ( x ); 
   ysav[3]= nrc_bessj ( 2, x ); 
   ysav[4]= nrc_bessj ( 3, x ); 
   nrc_derivs ( x, ysav, dysav ); 
   for ( i = 1; i <= N; i ++ ) yscal[i]= 1.0; 
   htry = 0.6; 
   printf ( "%10s %11s %12s %13s\n", "eps", "htry", "hdid", "hnext" ); 
   for ( i = 1; i <= 15; i ++ ) {
      eps = exp ( ( dReal ) - i ); 
      x = 1.0; 
      for ( j = 1; j <= N; j ++ ) {
         y[j]= ysav[j]; 
         dydx[j]= dysav[j]; 
      }
      nrc_rkqs ( y, dydx, N, &x, htry, eps, yscal, &hdid, &hnext, nrc_derivs ); 
      printf ( "%13f %8.2f %14.6f %12.6f \n", eps, htry, hdid, hnext ); 
   }
   nrc_free_vector ( yscal, 1, N ); 
   nrc_free_vector ( ysav, 1, N ); 
   nrc_free_vector ( dysav, 1, N ); 
   nrc_free_vector ( dydx, 1, N ); 
   nrc_free_vector ( y, 1, N ); 
   return 0; 
}
#undef NRANSI
