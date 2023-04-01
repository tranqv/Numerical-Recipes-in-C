
#include "nrc_types.h"

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define EPS 1.0e-14

void nrc_linbcg ( unsigned long n, dReal b[], dReal x[], int itol, dReal tol, 
   int itmax, int *iter, dReal *err )
{
   void nrc_asolve ( unsigned long n, dReal b[], dReal x[], int itrnsp ); 
   void nrc_atimes ( unsigned long n, dReal x[], dReal r[], int itrnsp ); 
   dReal nrc_snrm ( unsigned long n, dReal sx[], int itol ); 
   unsigned long j; 
   dReal ak, akden, bk, bkden, bknum, bnrm, dxnrm, xnrm, zm1nrm, znrm; 
   dReal *p, *pp, *r, *rr, *z, *zz; 

   p = nrc_dvector ( 1, n ); 
   pp = nrc_dvector ( 1, n ); 
   r = nrc_dvector ( 1, n ); 
   rr = nrc_dvector ( 1, n ); 
   z = nrc_dvector ( 1, n ); 
   zz = nrc_dvector ( 1, n ); 

   *iter = 0; 
   nrc_atimes ( n, x, r, 0 ); 
   for ( j = 1; j <= n; j ++ ) {
      r[j]= b[j]- r[j]; 
      rr[j]= r[j]; 
   }
   if ( itol == 1 ) {
      bnrm = nrc_snrm ( n, b, itol ); 
      nrc_asolve ( n, r, z, 0 ); 
   }
   else if ( itol == 2 ) {
      nrc_asolve ( n, b, z, 0 ); 
      bnrm = nrc_snrm ( n, z, itol ); 
      nrc_asolve ( n, r, z, 0 ); 
   }
   else if ( itol == 3 || itol == 4 ) {
      nrc_asolve ( n, b, z, 0 ); 
      bnrm = nrc_snrm ( n, z, itol ); 
      nrc_asolve ( n, r, z, 0 ); 
      znrm = nrc_snrm ( n, z, itol ); 
   } else nrc_error ( "illegal itol in nrc_linbcg" ); 
   while ( *iter <= itmax ) {
      ++( *iter ); 
      nrc_asolve ( n, rr, zz, 1 ); 
      for ( bknum = 0.0, j = 1; j <= n; j ++ ) bknum += z[j]*rr[j]; 
      if ( *iter == 1 ) {
         for ( j = 1; j <= n; j ++ ) {
            p[j]= z[j]; 
            pp[j]= zz[j]; 
         }
      }
      else {
         bk = bknum/bkden; 
         for ( j = 1; j <= n; j ++ ) {
            p[j]= bk*p[j]+ z[j]; 
            pp[j]= bk*pp[j]+ zz[j]; 
         }
      }
      bkden = bknum; 
      nrc_atimes ( n, p, z, 0 ); 
      for ( akden = 0.0, j = 1; j <= n; j ++ ) akden += z[j]*pp[j]; 
      ak = bknum/akden; 
      nrc_atimes ( n, pp, zz, 1 ); 
      for ( j = 1; j <= n; j ++ ) {
         x[j] += ak*p[j]; 
         r[j] -= ak*z[j]; 
         rr[j] -= ak*zz[j]; 
      }
      nrc_asolve ( n, r, z, 0 ); 
      if ( itol == 1 )
         *err = nrc_snrm ( n, r, itol )/bnrm; 
       else if ( itol == 2 )
         *err = nrc_snrm ( n, z, itol )/bnrm; 
      else if ( itol == 3 || itol == 4 ) {
         zm1nrm = znrm; 
         znrm = nrc_snrm ( n, z, itol ); 
         if ( fabs ( zm1nrm - znrm ) > EPS*znrm ) {
            dxnrm = fabs ( ak )*nrc_snrm ( n, p, itol ); 
            *err = znrm/fabs ( zm1nrm - znrm )*dxnrm; 
         } else {
            *err = znrm/bnrm; 
            continue; 
         }
         xnrm = nrc_snrm ( n, x, itol ); 
         if ( *err <= 0.5*xnrm ) *err /= xnrm; 
         else {
            *err = znrm/bnrm; 
            continue; 
         }
      }
      printf ( "iter =%4d err =%12.6f\n", *iter, *err ); 
   if ( *err <= tol ) break; 
   }

   nrc_free_dvector ( p, 1, n ); 
   nrc_free_dvector ( pp, 1, n ); 
   nrc_free_dvector ( r, 1, n ); 
   nrc_free_dvector ( rr, 1, n ); 
   nrc_free_dvector ( z, 1, n ); 
   nrc_free_dvector ( zz, 1, n ); 
}
#undef EPS
#undef NRANSI
