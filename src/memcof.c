
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_memcof ( sReal data[], int n, int m, sReal *xms, sReal d[] )
{
   int k, j, i; 
   sReal p = 0.0, *wk1, *wk2, *wkm; 

   wk1 = nrc_vector ( 1, n ); 
   wk2 = nrc_vector ( 1, n ); 
   wkm = nrc_vector ( 1, m ); 
   for ( j = 1; j <= n; j ++ ) p += SQR ( data[j] ); 
   *xms = p/n; 
   wk1[1]= data[1]; 
   wk2[n - 1]= data[n]; 
   for ( j = 2; j <= n - 1; j ++ ) {
      wk1[j]= data[j]; 
      wk2[j - 1]= data[j]; 
   }
   for ( k = 1; k <= m; k ++ ) {
      sReal num = 0.0, denom = 0.0; 
      for ( j = 1; j <=( n - k ); j ++ ) {
         num += wk1[j]*wk2[j]; 
         denom += SQR ( wk1[j] )+ SQR ( wk2[j] ); 
      }
      d[k]= 2.0*num/denom; 
      *xms *= ( 1.0 - SQR ( d[k] ) ); 
      for ( i = 1; i <=( k - 1 ); i ++ )
         d[i]= wkm[i]- d[k]*wkm[k - i]; 
      if ( k == m ) {
         nrc_free_vector ( wkm, 1, m ); 
         nrc_free_vector ( wk2, 1, n ); 
         nrc_free_vector ( wk1, 1, n ); 
         return; 
      }
      for ( i = 1; i <= k; i ++ ) wkm[i]= d[i]; 
      for ( j = 1; j <=( n - k - 1 ); j ++ ) {
         wk1[j] -= wkm[k]*wk2[j]; 
         wk2[j]= wk2[j + 1]- wkm[k]*wk1[j + 1]; 
      }
   }
   nrc_error ( "never get here in nrc_memcof." ); 
}
#undef NRANSI
