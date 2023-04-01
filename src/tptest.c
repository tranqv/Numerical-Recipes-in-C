
#include "nrc_types.h"

#include <math.h>

void nrc_tptest ( sReal data1[], sReal data2[], unsigned long n, sReal *t, 
   sReal *prob )
{
   void nrc_avevar ( sReal data[], unsigned long n, sReal *ave, sReal *var ); 
   sReal nrc_betai ( sReal a, sReal b, sReal x ); 
   unsigned long j; 
   sReal var1, var2, ave1, ave2, sd, df, cov = 0.0; 

   nrc_avevar ( data1, n, &ave1, &var1 ); 
   nrc_avevar ( data2, n, &ave2, &var2 ); 
   for ( j = 1; j <= n; j ++ )
      cov += ( data1[j]- ave1 )*( data2[j]- ave2 ); 
   cov /= df = n - 1; 
   sd = sqrt ( ( var1 + var2 - 2.0*cov )/n ); 
   *t =( ave1 - ave2 )/sd; 
   *prob = nrc_betai ( 0.5*df, 0.5, df/( df +( *t )*( *t ) ) ); 
}
