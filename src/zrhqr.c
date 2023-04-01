
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define MAXM 50

void nrc_zrhqr ( sReal a[], int m, sReal rtr[], sReal rti[] )
{
   void nrc_balanc ( sReal **a, int n ); 
   void nrc_hqr ( sReal **a, int n, sReal wr[], sReal wi[] ); 
   int j, k; 
   sReal **hess, xr, xi; 

   hess = nrc_matrix ( 1, MAXM, 1, MAXM ); 
   if ( m > MAXM || a[m] == 0.0 ) nrc_error ( "bad args in nrc_zrhqr" ); 
   for ( k = 1; k <= m; k ++ ) {
      hess[1][k] = - a[m - k]/a[m]; 
      for ( j = 2; j <= m; j ++ ) hess[j][k]= 0.0; 
      if ( k != m ) hess[k + 1][k]= 1.0; 
   }
   nrc_balanc ( hess, m ); 
   nrc_hqr ( hess, m, rtr, rti ); 
   for ( j = 2; j <= m; j ++ ) {
      xr = rtr[j]; 
      xi = rti[j]; 
      for ( k = j - 1; k >= 1; k -- ) {
         if ( rtr[k] <= xr ) break; 
         rtr[k + 1]= rtr[k]; 
         rti[k + 1]= rti[k]; 
      }
      rtr[k + 1]= xr; 
      rti[k + 1]= xi; 
   }
   nrc_free_matrix ( hess, 1, MAXM, 1, MAXM ); 
}
#undef MAXM
#undef NRANSI
