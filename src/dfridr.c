
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define CON 1.4
#define CON2 (CON*CON)
#define BIG     NR_CONST_HUGE
#define NTAB 10
#define SAFE 2.0

sReal nrc_dfridr ( sReal ( *func )( sReal ), sReal x, sReal h, sReal *err )
{
   int i, j; 
   sReal errt, fac, hh, **a, ans; 

   if ( h == 0.0 ) nrc_error ( "h must be nonzero in nrc_dfridr." ); 
   a = nrc_matrix ( 1, NTAB, 1, NTAB ); 
   hh = h; 
   a[1][1]=( ( *func )( x + hh )-( *func )( x - hh ) )/( 2.0*hh ); 
   *err = BIG; 
   for ( i = 2; i <= NTAB; i ++ ) {
      hh /= CON; 
      a[1][i]=( ( *func )( x + hh )-( *func )( x - hh ) )/( 2.0*hh ); 
      fac = CON2; 
      for ( j = 2; j <= i; j ++ ) {
         a[j][i]=( a[j - 1][i]*fac - a[j - 1][i - 1] )/( fac - 1.0 ); 
         fac = CON2*fac; 
         errt = FMAX ( fabs ( a[j][i]- a[j - 1][i] ), fabs ( a[j][i]- a[j - 1][i - 1] ) ); 
         if ( errt <= *err ) {
            *err = errt; 
            ans = a[j][i]; 
         }
      }
      if ( fabs ( a[i][i]- a[i - 1][i - 1] ) >= SAFE*( *err ) ) break; 
   }
   nrc_free_matrix ( a, 1, NTAB, 1, NTAB ); 
   return ans; 
}
#undef CON
#undef CON2
#undef BIG
#undef NTAB
#undef SAFE
#undef NRANSI
