
#include "nrc_types.h"

#include <math.h>
#define ACC 40.0
#define BIGNO 1.0e10
#define BIGNI 1.0e-10

sReal nrc_bessi ( int n, sReal x )
{
   sReal nrc_bessi0 ( sReal x ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal bi, bim, bip, tox, ans; 

   if ( n < 2 ) nrc_error ( "Index n less than 2 in nrc_bessi" ); 
   if ( x == 0.0 )
      return 0.0; 
   else {
      tox = 2.0/fabs ( x ); 
      bip = ans = 0.0; 
      bi = 1.0; 
      for ( j = 2*( n +( int ) sqrt ( ACC*n ) ); j > 0; j -- ) {
         bim = bip + j*tox*bi; 
         bip = bi; 
         bi = bim; 
         if ( fabs ( bi ) > BIGNO ) {
            ans *= BIGNI; 
            bi *= BIGNI; 
            bip *= BIGNI; 
         }
         if ( j == n ) ans = bip; 
      }
      ans *= nrc_bessi0 ( x )/bi; 
      return x < 0.0 && ( n & 1 ) ? - ans : ans; 
   }
}
#undef ACC
#undef BIGNO
#undef BIGNI
