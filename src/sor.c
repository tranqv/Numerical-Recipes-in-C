
#include "nrc_types.h"

#include <math.h>
#define MAXITS 1000
#define EPS    1.0e-13

void nrc_sor ( dReal **a, dReal **b, dReal **c, dReal **d, dReal **e, 
   dReal **f, dReal **u, int jmax, dReal rjac )
{
   void nrc_error ( char error_text[] ); 
   int ipass, j, jsw, l, lsw, n; 
   dReal anorm, anormf = 0.0, omega = 1.0, nrc_resid; 

   for ( j = 2; j < jmax; j ++ )
      for ( l = 2; l < jmax; l ++ )
         anormf += fabs ( f[j][l] ); 
   for ( n = 1; n <= MAXITS; n ++ ) {
      anorm = 0.0; 
      jsw = 1; 
      for ( ipass = 1; ipass <= 2; ipass ++ ) {
         lsw = jsw; 
         for ( j = 2; j < jmax; j ++ ) {
            for ( l = lsw + 1; l < jmax; l += 2 ) {
               nrc_resid = a[j][l]*u[j + 1][l]
                  + b[j][l]*u[j - 1][l]
                  + c[j][l]*u[j][l + 1]
                  + d[j][l]*u[j][l - 1]
                  + e[j][l]*u[j][l]
                  - f[j][l]; 
               anorm += fabs ( nrc_resid ); 
               u[j][l] -= omega*nrc_resid/e[j][l]; 
            }
            lsw = 3 - lsw; 
         }
         jsw = 3 - jsw; 
         omega =( n == 1 && ipass == 1 ? 1.0/( 1.0 - 0.5*rjac*rjac ) :
            1.0/( 1.0 - 0.25*rjac*rjac*omega ) ); 
      }
      if ( anorm < EPS*anormf ) return; 
   }
   nrc_error ( "MAXITS exceeded" ); 
}
#undef MAXITS
#undef EPS
