
#include "nrc_types.h"

#include <math.h>
#define MAXIT 100
#define EPS 3.0e-7
#define FPMIN   NR_CONST_FPMIN

sReal nrc_betacf ( sReal a, sReal b, sReal x )
{
   void nrc_error ( char error_text[] ); 
   int m, m2; 
   sReal aa, c, d, del, h, qab, qam, qap; 

   qab = a + b; 
   qap = a + 1.0; 
   qam = a - 1.0; 
   c = 1.0; 
   d = 1.0 - qab*x/qap; 
   if ( fabs ( d ) < FPMIN ) d = FPMIN; 
   d = 1.0/d; 
   h = d; 
   for ( m = 1; m <= MAXIT; m ++ ) {
      m2 = 2*m; 
      aa = m*( b - m )*x/( ( qam + m2 )*( a + m2 ) ); 
      d = 1.0 + aa*d; 
      if ( fabs ( d ) < FPMIN ) d = FPMIN; 
      c = 1.0 + aa/c; 
      if ( fabs ( c ) < FPMIN ) c = FPMIN; 
      d = 1.0/d; 
      h *= d*c; 
      aa = -( a + m )*( qab + m )*x/( ( a + m2 )*( qap + m2 ) ); 
      d = 1.0 + aa*d; 
      if ( fabs ( d ) < FPMIN ) d = FPMIN; 
      c = 1.0 + aa/c; 
      if ( fabs ( c ) < FPMIN ) c = FPMIN; 
      d = 1.0/d; 
      del = d*c; 
      h *= del; 
      if ( fabs ( del - 1.0 ) < EPS ) break; 
   }
   if ( m > MAXIT ) nrc_error ( "a or b too big, or MAXIT too small in nrc_betacf" ); 
   return h; 
}
#undef MAXIT
#undef EPS
#undef FPMIN
