
#include "nrc_types.h"

#include <math.h>

void nrc_ttest ( sReal data1[], unsigned long n1, sReal data2[], unsigned long n2, 
   sReal *t, sReal *prob )
{
   void nrc_avevar ( sReal data[], unsigned long n, sReal *ave, sReal *var ); 
   sReal nrc_betai ( sReal a, sReal b, sReal x ); 
   sReal var1, var2, svar, df, ave1, ave2; 

   nrc_avevar ( data1, n1, &ave1, &var1 ); 
   nrc_avevar ( data2, n2, &ave2, &var2 ); 
   df = n1 + n2 - 2; 
   svar =( ( n1 - 1 )*var1 +( n2 - 1 )*var2 )/df; 
   *t =( ave1 - ave2 )/sqrt ( svar*( 1.0/n1 + 1.0/n2 ) ); 
   *prob = nrc_betai ( 0.5*df, 0.5, df/( df +( *t )*( *t ) ) ); 
}
