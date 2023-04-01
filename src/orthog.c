
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_orthog ( int n, sReal anu[], sReal alpha[], sReal nrc_beta[], sReal a[], 
   sReal b[] )
{
   int k, l; 
   sReal **sig; 
   int looptmp; 

   sig = nrc_matrix ( 1, 2*n + 1, 1, 2*n + 1 ); 
   looptmp = 2*n; 
   for ( l = 3; l <= looptmp; l ++ ) sig[1][l]= 0.0; 
   looptmp ++; 
   for ( l = 2; l <= looptmp; l ++ ) sig[2][l]= anu[l - 1]; 
   a[1]= alpha[1]+ anu[2]/anu[1]; 
   b[1]= 0.0; 
   for ( k = 3; k <= n + 1; k ++ ) {
      looptmp = 2*n - k + 3; 
      for ( l = k; l <= looptmp; l ++ ) {
         sig[k][l]= sig[k - 1][l + 1]+( alpha[l - 1]- a[k - 2] )*sig[k - 1][l]-
            b[k - 2]*sig[k - 2][l]+ nrc_beta[l - 1]*sig[k - 1][l - 1]; 
      }
      a[k - 1]= alpha[k - 1]+ sig[k][k + 1]/sig[k][k]- sig[k - 1][k]/sig[k - 1][k - 1]; 
      b[k - 1]= sig[k][k]/sig[k - 1][k - 1]; 
   }
   nrc_free_matrix ( sig, 1, 2*n + 1, 1, 2*n + 1 ); 
}
#undef NRANSI
