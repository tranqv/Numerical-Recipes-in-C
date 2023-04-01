
#include "nrc_types.h"

void nrc_qrsolv ( sReal **a, int n, sReal c[], sReal d[], sReal b[] )
{
   void nrc_rsolv ( sReal **a, int n, sReal d[], sReal b[] ); 
   int i, j; 
   sReal sum, tau; 

   for ( j = 1; j < n; j ++ ) {
      for ( sum = 0.0, i = j; i <= n; i ++ ) sum += a[i][j]*b[i]; 
      tau = sum/c[j]; 
      for ( i = j; i <= n; i ++ ) b[i] -= tau*a[i][j]; 
   }
   nrc_rsolv ( a, n, d, b ); 
}
