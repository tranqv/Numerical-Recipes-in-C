
#include "nrc_types.h"

#include <math.h>
#define EULER 0.577215664901532860606512090082402431042
#define MAXIT 100
#define FPMIN   NR_CONST_FPMIN
#define EPS     NR_CONST_EPSI

sReal nrc_ei ( sReal x )
{
   void nrc_error ( char error_text[] ); 
   int k; 
   sReal fact, prev, sum, term; 

   if ( x <= 0.0 ) nrc_error ( "Bad argument in nrc_ei" ); 
   if ( x < FPMIN ) return log ( x )+ EULER; 
   if ( x <= - log ( EPS ) ) {
      sum = 0.0; 
      fact = 1.0; 
      for ( k = 1; k <= MAXIT; k ++ ) {
         fact *= x/k; 
         term = fact/k; 
         sum += term; 
         if ( term < EPS*sum ) break; 
      }
      if ( k > MAXIT ) nrc_error ( "Series failed in nrc_ei" ); 
      return sum + log ( x )+ EULER; 
   } else {
      sum = 0.0; 
      term = 1.0; 
      for ( k = 1; k <= MAXIT; k ++ ) {
         prev = term; 
         term *= k/x; 
         if ( term < EPS ) break; 
         if ( term < prev ) sum += term; 
         else {
            sum -= prev; 
            break; 
         }
      }
      return exp ( x )*( 1.0 + sum )/x; 
   }
}
#undef EPS
#undef EULER
#undef MAXIT
#undef FPMIN
