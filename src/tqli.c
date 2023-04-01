
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_tqli ( sReal d[], sReal e[], int n, sReal **z )
{
   sReal nrc_pythag ( sReal a, sReal b ); 
   int m, l, iter, i, k; 
   sReal s, r, p, g, f, dd, c, b; 

   for ( i = 2; i <= n; i ++ ) e[i - 1]= e[i]; 
   e[n]= 0.0; 
   for ( l = 1; l <= n; l ++ ) {
      iter = 0; 
      do {
         for ( m = l; m <= n - 1; m ++ ) {
            dd = fabs ( d[m] )+ fabs ( d[m + 1] ); 
            if ( ( sReal )( fabs ( e[m] )+ dd ) == dd ) break; 
         }
         if ( m != l ) {
            if ( iter ++ == 30 ) nrc_error ( "Too many iterations in nrc_tqli" ); 
            g =( d[l + 1]- d[l] )/( 2.0*e[l] ); 
            r = nrc_pythag ( g, 1.0 ); 
            g = d[m]- d[l]+ e[l]/( g + SIGN ( r, g ) ); 
            s = c = 1.0; 
            p = 0.0; 
            for ( i = m - 1; i >= l; i -- ) {
               f = s*e[i]; 
               b = c*e[i]; 
               e[i + 1]=( r = nrc_pythag ( f, g ) ); 
               if ( r == 0.0 ) {
                  d[i + 1] -= p; 
                  e[m]= 0.0; 
                  break; 
               }
               s = f/r; 
               c = g/r; 
               g = d[i + 1]- p; 
               r =( d[i]- g )*s + 2.0*c*b; 
               d[i + 1]= g +( p = s*r ); 
               g = c*r - b; 
               for ( k = 1; k <= n; k ++ ) {
                  f = z[k][i + 1]; 
                  z[k][i + 1]= s*z[k][i]+ c*f; 
                  z[k][i]= c*z[k][i]- s*f; 
               }
            }
            if ( r == 0.0 && i >= l ) continue; 
            d[l] -= p; 
            e[l]= g; 
            e[m]= 0.0; 
         }
      } while ( m != l ); 
   }
}
#undef NRANSI
