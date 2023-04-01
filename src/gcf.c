
#include "nrc_types.h"

#include <math.h>
#define ITMAX 100
#define EPS 3.0e-7
#define FPMIN   NR_CONST_FPMIN

void nrc_gcf ( sReal *gammcf, sReal a, sReal x, sReal *gln )
{
   sReal nrc_gammln ( sReal xx ); 
   void nrc_error ( char error_text[] ); 
   int i; 
   sReal an, b, c, d, del, h; 

   *gln = nrc_gammln ( a ); 
   b = x + 1.0 - a; 
   c = 1.0/FPMIN; 
   d = 1.0/b; 
   h = d; 
   for ( i = 1; i <= ITMAX; i ++ ) {
      an = - i*( i - a ); 
      b += 2.0; 
      d = an*d + b; 
      if ( fabs ( d ) < FPMIN ) d = FPMIN; 
      c = b + an/c; 
      if ( fabs ( c ) < FPMIN ) c = FPMIN; 
      d = 1.0/d; 
      del = d*c; 
      h *= del; 
      if ( fabs ( del - 1.0 ) < EPS ) break; 
   }
   if ( i > ITMAX ) nrc_error ( "a too large, ITMAX too small in nrc_gcf" ); 
   *gammcf = exp ( - x + a*log ( x )-( *gln ) )*h; 
}
#undef ITMAX
#undef EPS
#undef FPMIN
