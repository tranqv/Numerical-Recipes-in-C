
#include "nrc_types.h"

#include <math.h>
#define ACC 40.0
#define BIGNO 1.0e10
#define BIGNI 1.0e-10

sReal nrc_bessj ( int n, sReal x )
{
   sReal nrc_bessj0 ( sReal x ); 
   sReal nrc_bessj1 ( sReal x ); 
   void nrc_error ( char error_text[] ); 
   int j, jsum, m; 
   sReal ax, bj, bjm, bjp, sum, tox, ans; 

   if ( n < 2 ) nrc_error ( "Index n less than 2 in nrc_bessj" ); 
   ax = fabs ( x ); 
   if ( ax == 0.0 )
      return 0.0; 
   else if ( ax > ( sReal ) n ) {
      tox = 2.0/ax; 
      bjm = nrc_bessj0 ( ax ); 
      bj = nrc_bessj1 ( ax ); 
      for ( j = 1; j < n; j ++ ) {
         bjp = j*tox*bj - bjm; 
         bjm = bj; 
         bj = bjp; 
      }
      ans = bj; 
   } else {
      tox = 2.0/ax; 
      m = 2*( ( n +( int ) sqrt ( ACC*n ) )/2 ); 
      jsum = 0; 
      bjp = ans = sum = 0.0; 
      bj = 1.0; 
      for ( j = m; j > 0; j -- ) {
         bjm = j*tox*bj - bjp; 
         bjp = bj; 
         bj = bjm; 
         if ( fabs ( bj ) > BIGNO ) {
            bj *= BIGNI; 
            bjp *= BIGNI; 
            ans *= BIGNI; 
            sum *= BIGNI; 
         }
         if ( jsum ) sum += bj; 
         jsum =!jsum; 
         if ( j == n ) ans = bjp; 
      }
      sum = 2.0*sum - bj; 
      ans /= sum; 
   }
   return x < 0.0 && ( n & 1 ) ? - ans : ans; 
}
#undef ACC
#undef BIGNO
#undef BIGNI
