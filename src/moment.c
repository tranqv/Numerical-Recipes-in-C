
#include "nrc_types.h"

#include <math.h>

void nrc_moment ( sReal data[], int n, sReal *ave, sReal *adev, sReal *sdev, 
   sReal *var, sReal *skew, sReal *curt )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal ep = 0.0, s, p; 

   if ( n <= 1 ) nrc_error ( "n must be at least 2 in nrc_moment" ); 
   s = 0.0; 
   for ( j = 1; j <= n; j ++ ) s += data[j]; 
   *ave = s/n; 
   *adev =( *var )=( *skew )=( *curt )= 0.0; 
   for ( j = 1; j <= n; j ++ ) {
      *adev += fabs ( s = data[j]-( *ave ) ); 
      ep += s; 
      *var += ( p = s*s ); 
      *skew += ( p *= s ); 
      *curt += ( p *= s ); 
   }
   *adev /= n; 
   *var =( *var - ep*ep/n )/( n - 1 ); 
   *sdev = sqrt ( *var ); 
   if ( *var ) {
      *skew /= ( n*( *var )*( *sdev ) ); 
      *curt =( *curt )/( n*( *var )*( *var ) )- 3.0; 
   } else nrc_error ( "No skew/kurtosis when variance = 0 ( in nrc_moment )" ); 
}
