
#include "nrc_types.h"

void nrc_ftest ( sReal data1[], unsigned long n1, sReal data2[], unsigned long n2, 
   sReal *f, sReal *prob )
{
   void nrc_avevar ( sReal data[], unsigned long n, sReal *ave, sReal *var ); 
   sReal nrc_betai ( sReal a, sReal b, sReal x ); 
   sReal var1, var2, ave1, ave2, df1, df2; 

   nrc_avevar ( data1, n1, &ave1, &var1 ); 
   nrc_avevar ( data2, n2, &ave2, &var2 ); 
   if ( var1 > var2 ) {
      *f = var1/var2; 
      df1 = n1 - 1; 
      df2 = n2 - 1; 
   } else {
      *f = var2/var1; 
      df1 = n2 - 1; 
      df2 = n1 - 1; 
   }
   *prob = 2.0*nrc_betai ( 0.5*df2, 0.5*df1, df2/( df2 + df1*( *f ) ) ); 
   if ( *prob > 1.0 ) *prob = 2.0 -*prob; 
}
