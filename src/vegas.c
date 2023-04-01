
#include "nrc_types.h"

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define ALPH 1.5
#define NDMX 50
#define MXDIM 10
#define TINY   1.0e-30

extern long idum; 

void nrc_vegas ( sReal regn[], int ndim, sReal ( *fxn )( sReal [], sReal ), int init, 
   unsigned long ncall, int itmx, int nprn, sReal *tgral, sReal *sd, 
   sReal *chi2a )
{
   sReal nrc_ran2 ( long *idum ); 
   void nrc_rebin ( sReal nrc_rc, int nd, sReal r[], sReal xin[], sReal xi[] ); 
   static int i, it, j, k, mds, nd, ndo, ng, npg, ia[MXDIM + 1], kg[MXDIM + 1]; 
   static sReal calls, dv2g, dxg, f, nrc_f2, f2b, fb, nrc_rc, ti, tsi, wgt, xjac, xn, xnd, xo; 
   static sReal d[NDMX + 1][MXDIM + 1], di[NDMX + 1][MXDIM + 1], dt[MXDIM + 1], 
      dx[MXDIM + 1], r[NDMX + 1], x[MXDIM + 1], xi[MXDIM + 1][NDMX + 1], xin[NDMX + 1]; 
   static dReal schi, si, swgt; 

   if ( init <= 0 ) {
      mds = ndo = 1; 
      for ( j = 1; j <= ndim; j ++ ) xi[j][1]= 1.0; 
   }
   if ( init <= 1 ) si = swgt = schi = 0.0; 
   if ( init <= 2 ) {
      nd = NDMX; 
      ng = 1; 
      if ( mds ) {
         ng =( int ) pow ( ncall/2.0 + 0.25, 1.0/ndim ); 
         mds = 1; 
         if ( ( 2*ng - NDMX ) >= 0 ) {
            mds = - 1; 
            npg = ng/NDMX + 1; 
            nd = ng/npg; 
            ng = npg*nd; 
         }
      }
      for ( k = 1, i = 1; i <= ndim; i ++ ) k *= ng; 
      npg = IMAX ( ncall/k, 2 ); 
      calls =( sReal ) npg * ( sReal ) k; 
      dxg = 1.0/ng; 
      for ( dv2g = 1, i = 1; i <= ndim; i ++ ) dv2g *= dxg; 
      dv2g = SQR ( calls*dv2g )/npg/npg/( npg - 1.0 ); 
      xnd = nd; 
      dxg *= xnd; 
      xjac = 1.0/calls; 
      for ( j = 1; j <= ndim; j ++ ) {
         dx[j]= regn[j + ndim]- regn[j]; 
         xjac *= dx[j]; 
      }
      if ( nd != ndo ) {
         for ( i = 1; i <= IMAX ( nd, ndo ); i ++ ) r[i]= 1.0; 
         for ( j = 1; j <= ndim; j ++ ) nrc_rebin ( ndo/xnd, nd, r, xin, xi[j] ); 
         ndo = nd; 
      }
      if ( nprn >= 0 ) {
         printf ( "%s:  ndim = %3d ncall = %8.0f\n", 
            " Input parameters for nrc_vegas", ndim, calls ); 
         printf ( "%28s it =%5d itmx =%5d\n", " ", it, itmx ); 
         printf ( "%28s nprn =%3d ALPH =%5.2f\n", " ", nprn, ALPH ); 
         printf ( "%28s mds =%3d nd =%4d\n", " ", mds, nd ); 
         for ( j = 1; j <= ndim; j ++ ) {
            printf ( "%30s xl[%2d]= %11.4g xu[%2d]= %11.4g\n", 
               " ", j, regn[j], j, regn[j + ndim] ); 
         }
      }
   }
   for ( it = 1; it <= itmx; it ++ ) {
      ti = tsi = 0.0; 
      for ( j = 1; j <= ndim; j ++ ) {
         kg[j]= 1; 
         for ( i = 1; i <= nd; i ++ ) d[i][j]= di[i][j]= 0.0; 
      }
      for ( ; ; ) {
         fb = f2b = 0.0; 
         for ( k = 1; k <= npg; k ++ ) {
            wgt = xjac; 
            for ( j = 1; j <= ndim; j ++ ) {
               xn =( kg[j]- nrc_ran2 ( &idum ) )*dxg + 1.0; 
               ia[j]= IMAX ( IMIN ( ( int )( xn ), NDMX ), 1 ); 
               if ( ia[j] > 1 ) {
                  xo = xi[j][ia[j]]- xi[j][ia[j]- 1]; 
                  nrc_rc = xi[j][ia[j]- 1]+( xn - ia[j] )*xo; 
               } else {
                  xo = xi[j][ia[j]]; 
                  nrc_rc =( xn - ia[j] )*xo; 
               }
               x[j]= regn[j]+ nrc_rc*dx[j]; 
               wgt *= xo*xnd; 
            }
            f = wgt*( *fxn )( x, wgt ); 
            nrc_f2 = f*f; 
            fb += f; 
            f2b += nrc_f2; 
            for ( j = 1; j <= ndim; j ++ ) {
               di[ia[j]][j] += f; 
               if ( mds >= 0 ) d[ia[j]][j] += nrc_f2; 
            }
         }
         f2b = sqrt ( f2b*npg ); 
         f2b =( f2b - fb )*( f2b + fb ); 
         if ( f2b <= 0.0 ) f2b = TINY; 
         ti += fb; 
         tsi += f2b; 
         if ( mds < 0 ) {
            for ( j = 1; j <= ndim; j ++ ) d[ia[j]][j] += f2b; 
         }
         for ( k = ndim; k >= 1; k -- ) {
            kg[k] %= ng; 
            if ( ++ kg[k] != 1 ) break; 
         }
         if ( k < 1 ) break; 
      }
      tsi *= dv2g; 
      wgt = 1.0/tsi; 
      si += wgt*ti; 
      schi += wgt*ti*ti; 
      swgt += wgt; 
      *tgral = si/swgt; 
      *chi2a =( schi - si*( *tgral ) )/( it - 0.9999 ); 
      if ( *chi2a < 0.0 ) *chi2a = 0.0; 
      *sd = sqrt ( 1.0/swgt ); 
      tsi = sqrt ( tsi ); 
      if ( nprn >= 0 ) {
         printf ( "%s %3d : integral = %14.7g +/-  %9.2g\n", 
            " iteration no.", it, ti, tsi ); 
         printf ( "%s integral =%14.7g +/-%9.2g chi**2/IT n = %9.2g\n", 
            " all iterations:  ", *tgral, *sd, *chi2a ); 
         if ( nprn ) {
            for ( j = 1; j <= ndim; j ++ ) {
               printf ( " DATA FOR axis %2d\n", j ); 
               printf ( "%6s%13s%11s%13s%11s%13s\n", 
                  "X", "delta i", "X", "delta i", "X", "delta i" ); 
               for ( i = 1 + nprn/2; i <= nd; i += nprn + 2 ) {
                  printf ( "%8.5f%12.4g%12.5f%12.4g%12.5f%12.4g\n", 
                     xi[j][i], di[i][j], xi[j][i + 1], 
                     di[i + 1][j], xi[j][i + 2], di[i + 2][j] ); 
               }
            }
         }
      }
      for ( j = 1; j <= ndim; j ++ ) {
         xo = d[1][j]; 
         xn = d[2][j]; 
         d[1][j]=( xo + xn )/2.0; 
         dt[j]= d[1][j]; 
         for ( i = 2; i < nd; i ++ ) {
            nrc_rc = xo + xn; 
            xo = xn; 
            xn = d[i + 1][j]; 
            d[i][j] = ( nrc_rc + xn )/3.0; 
            dt[j] += d[i][j]; 
         }
         d[nd][j]=( xo + xn )/2.0; 
         dt[j] += d[nd][j]; 
      }
      for ( j = 1; j <= ndim; j ++ ) {
         nrc_rc = 0.0; 
         for ( i = 1; i <= nd; i ++ ) {
            if ( d[i][j] < TINY ) d[i][j]= TINY; 
            r[i]= pow ( ( 1.0 - d[i][j]/dt[j] )/
               ( log ( dt[j] )- log ( d[i][j] ) ), ALPH ); 
            nrc_rc += r[i]; 
         }
         nrc_rebin ( nrc_rc/xnd, nd, r, xin, xi[j] ); 
      }
   }
}
#undef ALPH
#undef NDMX
#undef MXDIM
#undef TINY
#undef NRANSI
