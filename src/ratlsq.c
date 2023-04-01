
#include "nrc_types.h"

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define NPFAC 8
#define MAXIT 5
#define PIO2 (3.141592653589793238462643383279502884197/2.0)
#define BIG    1.0e30

void nrc_ratlsq ( dReal ( *fn )( dReal ), dReal a, dReal b, int mm, int kk, 
   dReal cof[], dReal *dev )
{
   dReal nrc_ratval ( dReal x, dReal cof[], int mm, int kk ); 
   void nrc_dsvbksb ( dReal **u, dReal w[], dReal **v, int m, int n, dReal b[], 
      dReal x[] ); 
   void nrc_dsvdcmp ( dReal **a, int m, int n, dReal w[], dReal **v ); 
   int i, it, j, ncof, npt; 
   dReal devmax, e, hth, power, sum, *bb, *coff, *ee, *fs, **u, **v, *w, *wt, *xs; 

   ncof = mm + kk + 1; 
   npt = NPFAC*ncof; 
   bb = nrc_dvector ( 1, npt ); 
   coff = nrc_dvector ( 0, ncof - 1 ); 
   ee = nrc_dvector ( 1, npt ); 
   fs = nrc_dvector ( 1, npt ); 
   u = nrc_dmatrix ( 1, npt, 1, ncof ); 
   v = nrc_dmatrix ( 1, ncof, 1, ncof ); 
   w = nrc_dvector ( 1, ncof ); 
   wt = nrc_dvector ( 1, npt ); 
   xs = nrc_dvector ( 1, npt ); 
   *dev = BIG; 
   for ( i = 1; i <= npt; i ++ ) {
      if ( i < npt/2 ) {
         hth = PIO2*( i - 1 )/( npt - 1.0 ); 
         xs[i]= a +( b - a )*DSQR ( sin ( hth ) ); 
      } else {
         hth = PIO2*( npt - i )/( npt - 1.0 ); 
         xs[i]= b -( b - a )*DSQR ( sin ( hth ) ); 
      }
      fs[i]=( *fn )( xs[i] ); 
      wt[i]= 1.0; 
      ee[i]= 1.0; 
   }
   e = 0.0; 
   for ( it = 1; it <= MAXIT; it ++ ) {
      for ( i = 1; i <= npt; i ++ ) {
         power = wt[i]; 
         bb[i]= power*( fs[i]+ SIGN ( e, ee[i] ) ); 
         for ( j = 1; j <= mm + 1; j ++ ) {
            u[i][j]= power; 
            power *= xs[i]; 
         }
         power = - bb[i]; 
         for ( j = mm + 2; j <= ncof; j ++ ) {
            power *= xs[i]; 
            u[i][j]= power; 
         }
      }
      nrc_dsvdcmp ( u, npt, ncof, w, v ); 
      nrc_dsvbksb ( u, w, v, npt, ncof, bb, coff - 1 ); 
      devmax = sum = 0.0; 
      for ( j = 1; j <= npt; j ++ ) {
         ee[j]= nrc_ratval ( xs[j], coff, mm, kk )- fs[j]; 
         wt[j]= fabs ( ee[j] ); 
         sum += wt[j]; 
         if ( wt[j] > devmax ) devmax = wt[j]; 
      }
      e = sum/npt; 
      if ( devmax <= *dev ) {
         for ( j = 0; j < ncof; j ++ ) cof[j]= coff[j]; 
         *dev = devmax; 
      }
      printf ( " nrc_ratlsq iteration = %2d max error = %10.3e\n", it, devmax ); 
   }
   nrc_free_dvector ( xs, 1, npt ); 
   nrc_free_dvector ( wt, 1, npt ); 
   nrc_free_dvector ( w, 1, ncof ); 
   nrc_free_dmatrix ( v, 1, ncof, 1, ncof ); 
   nrc_free_dmatrix ( u, 1, npt, 1, ncof ); 
   nrc_free_dvector ( fs, 1, npt ); 
   nrc_free_dvector ( ee, 1, npt ); 
   nrc_free_dvector ( coff, 0, ncof - 1 ); 
   nrc_free_dvector ( bb, 1, npt ); 
}
#undef NPFAC
#undef MAXIT
#undef PIO2
#undef BIG
#undef NRANSI
