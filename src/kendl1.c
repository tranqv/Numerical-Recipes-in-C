
#include "nrc_types.h"

#include <math.h>

void nrc_kendl1 ( sReal data1[], sReal data2[], unsigned long n, sReal *tau, 
   sReal *z, sReal *prob )
{
   sReal nrc_erfcc ( sReal x ); 
   unsigned long n2 = 0, n1 = 0, k, j; 
   long is = 0; 
   sReal svar, aa, a2, a1; 

   for ( j = 1; j < n; j ++ ) {
      for ( k =( j + 1 ); k <= n; k ++ ) {
         a1 = data1[j]- data1[k]; 
         a2 = data2[j]- data2[k]; 
         aa = a1*a2; 
         if ( aa ) {
            ++ n1; 
            ++ n2; 
            aa > 0.0 ? ++ is : -- is; 
         } else {
            if ( a1 ) ++ n1; 
            if ( a2 ) ++ n2; 
         }
      }
   }
   *tau = is/( sqrt ( ( dReal ) n1 )*sqrt ( ( dReal ) n2 ) ); 
   svar =( 4.0*n + 10.0 )/( 9.0*n*( n - 1.0 ) ); 
   *z =( *tau )/sqrt ( svar ); 
   *prob = nrc_erfcc ( fabs ( *z )/1.4142136 ); 
}
