
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_rotate ( sReal **r, sReal **qt, int n, int i, sReal a, sReal b )
{
   int j; 
   sReal c, fact, s, w, y; 

   if ( a == 0.0 ) {
      c = 0.0; 
      s =( b >= 0.0 ? 1.0 : - 1.0 ); 
   } else if ( fabs ( a ) > fabs ( b ) ) {
      fact = b/a; 
      c = SIGN ( 1.0/sqrt ( 1.0 +( fact*fact ) ), a ); 
      s = fact*c; 
   } else {
      fact = a/b; 
      s = SIGN ( 1.0/sqrt ( 1.0 +( fact*fact ) ), b ); 
      c = fact*s; 
   }
   for ( j = i; j <= n; j ++ ) {
      y = r[i][j]; 
      w = r[i + 1][j]; 
      r[i][j]= c*y - s*w; 
      r[i + 1][j]= s*y + c*w; 
   }
   for ( j = 1; j <= n; j ++ ) {
      y = qt[i][j]; 
      w = qt[i + 1][j]; 
      qt[i][j]= c*y - s*w; 
      qt[i + 1][j]= s*y + c*w; 
   }
}
#undef NRANSI
