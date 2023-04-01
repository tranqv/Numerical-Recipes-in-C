
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define ITMAX 200
#define EPS     NR_CONST_EPSI*1.0e-3
#define FREEALL nrc_free_vector(xi,1,n);nrc_free_vector(h,1,n);nrc_free_vector(g,1,n);

void nrc_frprmn ( sReal p[], int n, sReal ftol, int *iter, sReal *fret, 
   sReal ( *func )( sReal [] ), void ( *dfunc )( sReal [], sReal [] ) )
{
   void nrc_linmin ( sReal p[], sReal xi[], int n, sReal *fret, 
      sReal ( *func )( sReal [] ) ); 
   int j, its; 
   sReal gg, gam, fp, dgg; 
   sReal *g, *h, *xi; 

   g = nrc_vector ( 1, n ); 
   h = nrc_vector ( 1, n ); 
   xi = nrc_vector ( 1, n ); 
   fp =( *func )( p ); 
   ( *dfunc )( p, xi ); 
   for ( j = 1; j <= n; j ++ ) {
      g[j] = - xi[j]; 
      xi[j]= h[j]= g[j]; 
   }
   for ( its = 1; its <= ITMAX; its ++ ) {
      *iter = its; 
      nrc_linmin ( p, xi, n, fret, func ); 
      if ( 2.0*fabs ( *fret - fp ) <= ftol*( fabs ( *fret )+ fabs ( fp )+ EPS ) ) {
         FREEALL
         return; 
      }
      fp = *fret; 
      ( *dfunc )( p, xi ); 
      dgg = gg = 0.0; 
      for ( j = 1; j <= n; j ++ ) {
         gg += g[j]*g[j]; 
         dgg += ( xi[j]+ g[j] )*xi[j]; 
      }
      if ( gg == 0.0 ) {
         FREEALL
         return; 
      }
      gam = dgg/gg; 
      for ( j = 1; j <= n; j ++ ) {
         g[j] = - xi[j]; 
         xi[j]= h[j]= g[j]+ gam*h[j]; 
      }
   }
   nrc_error ( "Too many iterations in nrc_frprmn" ); 
}
#undef ITMAX
#undef EPS
#undef FREEALL
#undef NRANSI
