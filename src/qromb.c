
#include "nrc_types.h"

#include <math.h>
#define EPS    1.0e-10
#define JMAX 20
#define JMAXP (JMAX+1)
#define K 5

sReal nrc_qromb ( sReal ( *func )( sReal ), sReal a, sReal b )
{
   void nrc_polint ( sReal xa[], sReal ya[], int n, sReal x, sReal *y, sReal *dy ); 
   sReal nrc_trapzd ( sReal ( *func )( sReal ), sReal a, sReal b, int n ); 
   void nrc_error ( char error_text[] ); 
   sReal ss, dss; 
   sReal s[JMAXP], h[JMAXP + 1]; 
   int j; 

   h[1]= 1.0; 
   for ( j = 1; j <= JMAX; j ++ ) {
      s[j]= nrc_trapzd ( func, a, b, j ); 
      if ( j >= K ) {
         nrc_polint ( &h[j - K], &s[j - K], K, 0.0, &ss, &dss ); 
         if ( fabs ( dss ) <= EPS*fabs ( ss ) ) return ss; 
      }
      h[j + 1]= 0.25*h[j]; 
   }
   nrc_error ( "Too many steps in routine nrc_qromb" ); 
   return 0.0; 
}
#undef EPS
#undef JMAX
#undef JMAXP
#undef K
