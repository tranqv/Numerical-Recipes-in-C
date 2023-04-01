
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define ITMAX 20
#define TINY   1.0e-14

void nrc_qroot ( sReal p[], int n, sReal *b, sReal *c, sReal eps )
{
   void nrc_poldiv ( sReal u[], int n, sReal v[], int nv, sReal q[], sReal r[] ); 
   int iter; 
   sReal sc, sb, s, nrc_rc, rb, r, dv, delc, delb; 
   sReal *q, *qq, *rem; 
   sReal d[3]; 

   q = nrc_vector ( 0, n ); 
   qq = nrc_vector ( 0, n ); 
   rem = nrc_vector ( 0, n ); 
   d[2]= 1.0; 
   for ( iter = 1; iter <= ITMAX; iter ++ ) {
      d[1]=( *b ); 
      d[0]=( *c ); 
      nrc_poldiv ( p, n, d, 2, q, rem ); 
      s = rem[0]; 
      r = rem[1]; 
      nrc_poldiv ( q, ( n - 1 ), d, 2, qq, rem ); 
      sb = -( *c )*( nrc_rc = - rem[1] ); 
      rb = -( *b )*nrc_rc +( sc = - rem[0] ); 
      dv = 1.0/( sb*nrc_rc - sc*rb ); 
      delb =( r*sc - s*nrc_rc )*dv; 
      delc =( - r*sb + s*rb )*dv; 
      *b += ( delb =( r*sc - s*nrc_rc )*dv ); 
      *c += ( delc =( - r*sb + s*rb )*dv ); 
      if ( ( fabs ( delb ) <= eps*fabs ( *b ) || fabs ( *b ) < TINY )
         && ( fabs ( delc ) <= eps*fabs ( *c ) || fabs ( *c ) < TINY ) ) {
         nrc_free_vector ( rem, 0, n ); 
         nrc_free_vector ( qq, 0, n ); 
         nrc_free_vector ( q, 0, n ); 
         return; 
      }
   }
   nrc_error ( "Too many iterations in routine nrc_qroot" ); 
}
#undef ITMAX
#undef TINY
#undef NRANSI
