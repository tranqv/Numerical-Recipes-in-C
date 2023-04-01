
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_tutest ( sReal data1[], unsigned long n1, sReal data2[], unsigned long n2, 
   sReal *t, sReal *prob )
{
   void nrc_avevar ( sReal data[], unsigned long n, sReal *ave, sReal *var ); 
   sReal nrc_betai ( sReal a, sReal b, sReal x ); 
   sReal var1, var2, df, ave1, ave2; 

   nrc_avevar ( data1, n1, &ave1, &var1 ); 
   nrc_avevar ( data2, n2, &ave2, &var2 ); 
   *t =( ave1 - ave2 )/sqrt ( var1/n1 + var2/n2 ); 
   df = SQR ( var1/n1 + var2/n2 )/( SQR ( var1/n1 )/( n1 - 1 )+ SQR ( var2/n2 )/( n2 - 1 ) ); 
   *prob = nrc_betai ( 0.5*df, 0.5, df/( df + SQR ( *t ) ) ); 
}
#undef NRANSI
