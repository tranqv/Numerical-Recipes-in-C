
#include "nrc_types.h"

#include <math.h>
#define EPS    3.0e-9
#define JMAX 14
#define JMAXP (JMAX+1)
#define K 5

sReal nrc_qromo ( sReal ( *func )( sReal ), sReal a, sReal b, 
   sReal ( *choose )( sReal ( * )( sReal ), sReal, sReal, int ) )
{
   void nrc_polint ( sReal xa[], sReal ya[], int n, sReal x, sReal *y, sReal *dy ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal ss, dss, h[JMAXP + 1], s[JMAXP]; 

   h[1]= 1.0; 
   for ( j = 1; j <= JMAX; j ++ ) {
      s[j]=( *choose )( func, a, b, j ); 
      if ( j >= K ) {
         nrc_polint ( &h[j - K], &s[j - K], K, 0.0, &ss, &dss ); 
         if ( fabs ( dss ) <= EPS*fabs ( ss ) ) return ss; 
      }
      h[j + 1]= h[j]/9.0; 
   }
   nrc_error ( "Too many steps in routing nrc_qromo" ); 
   return 0.0; 
}
#undef EPS
#undef JMAX
#undef JMAXP
#undef K
