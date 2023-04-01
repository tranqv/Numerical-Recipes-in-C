
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_polint ( sReal xa[], sReal ya[], int n, sReal x, sReal *y, sReal *dy )
{
   int i, m, ns = 1; 
   sReal den, dif, dift, ho, hp, w; 
   sReal *c, *d; 

   dif = fabs ( x - xa[1] ); 
   c = nrc_vector ( 1, n ); 
   d = nrc_vector ( 1, n ); 
   for ( i = 1; i <= n; i ++ ) {
      if ( ( dift = fabs ( x - xa[i] ) ) < dif ) {
         ns = i; 
         dif = dift; 
      }
      c[i]= ya[i]; 
      d[i]= ya[i]; 
   }
   *y = ya[ns --]; 
   for ( m = 1; m < n; m ++ ) {
      for ( i = 1; i <= n - m; i ++ ) {
         ho = xa[i]- x; 
         hp = xa[i + m]- x; 
         w = c[i + 1]- d[i]; 
         if ( ( den = ho - hp ) == 0.0 ) nrc_error ( "Error in routine nrc_polint" ); 
         den = w/den; 
         d[i]= hp*den; 
         c[i]= ho*den; 
      }
      *y += ( *dy =( 2*ns < ( n - m ) ? c[ns + 1] : d[ns --] ) ); 
   }
   nrc_free_vector ( d, 1, n ); 
   nrc_free_vector ( c, 1, n ); 
}
#undef NRANSI
