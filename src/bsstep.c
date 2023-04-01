
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define KMAXX 8
#define IMAXX (KMAXX+1)
#define SAFE1 0.25
#define SAFE2 0.7
#define REDMAX 1.0e-5
#define REDMIN 0.7
#define TINY 1.0e-30
#define SCALMX 0.1

sReal **d, *x; 

void nrc_bsstep ( sReal y[], sReal dydx[], int nv, sReal *xx, sReal htry, sReal eps, 
   sReal yscal[], sReal *hdid, sReal *hnext, 
   void ( *nrc_derivs )( sReal, sReal [], sReal [] ) )
{
   void nrc_mmid ( sReal y[], sReal dydx[], int nvar, sReal xs, sReal htot, 
      int nstep, sReal yout[], void ( *nrc_derivs )( sReal, sReal[], sReal[] ) ); 
   void nrc_pzextr ( int iest, sReal xest, sReal yest[], sReal yz[], sReal dy[], 
      int nv ); 
   int i, iq, k, kk, km; 
   static int first = 1, kmax, kopt; 
   static sReal epsold = - 1.0, xnew; 
   sReal eps1, errmax, fact, h, nrc_red, scale, work, wrkmin, xest; 
   sReal *err, *yerr, *ysav, *yseq; 
   static sReal a[IMAXX + 1]; 
   static sReal alf[KMAXX + 1][KMAXX + 1]; 
   static int nseq[IMAXX + 1]={0, 2, 4, 6, 8, 10, 12, 14, 16, 18}; 
   int reduct, exitflag = 0; 

   d = nrc_matrix ( 1, nv, 1, KMAXX ); 
   err = nrc_vector ( 1, KMAXX ); 
   x = nrc_vector ( 1, KMAXX ); 
   yerr = nrc_vector ( 1, nv ); 
   ysav = nrc_vector ( 1, nv ); 
   yseq = nrc_vector ( 1, nv ); 
   if ( eps != epsold ) {
      *hnext = xnew = - 1.0e29; 
      eps1 = SAFE1*eps; 
      a[1]= nseq[1]+ 1; 
      for ( k = 1; k <= KMAXX; k ++ ) a[k + 1]= a[k]+ nseq[k + 1]; 
      for ( iq = 2; iq <= KMAXX; iq ++ ) {
         for ( k = 1; k < iq; k ++ )
            alf[k][iq]= pow ( eps1, ( a[k + 1]- a[iq + 1] )/
               ( ( a[iq + 1]- a[1]+ 1.0 )*( 2*k + 1 ) ) ); 
      }
      epsold = eps; 
      for ( kopt = 2; kopt < KMAXX; kopt ++ )
         if ( a[kopt + 1] > a[kopt]*alf[kopt - 1][kopt] ) break; 
      kmax = kopt; 
   }
   h = htry; 
   for ( i = 1; i <= nv; i ++ ) ysav[i]= y[i]; 
   if ( *xx != xnew || h != ( *hnext ) ) {
      first = 1; 
      kopt = kmax; 
   }
   reduct = 0; 
   for ( ; ; ) {
      for ( k = 1; k <= kmax; k ++ ) {
         xnew =( *xx )+ h; 
         if ( xnew == ( *xx ) ) nrc_error ( "step size underflow in nrc_bsstep" ); 
         nrc_mmid ( ysav, dydx, nv, *xx, h, nseq[k], yseq, nrc_derivs ); 
         xest = SQR ( h/nseq[k] ); 
         nrc_pzextr ( k, xest, yseq, y, yerr, nv ); 
         if ( k != 1 ) {
            errmax = TINY; 
            for ( i = 1; i <= nv; i ++ ) errmax = FMAX ( errmax, fabs ( yerr[i]/yscal[i] ) ); 
            errmax /= eps; 
            km = k - 1; 
            err[km]= pow ( errmax/SAFE1, 1.0/( 2*km + 1 ) ); 
         }
         if ( k != 1 && ( k >= kopt - 1 || first ) ) {
            if ( errmax < 1.0 ) {
               exitflag = 1; 
               break; 
            }
            if ( k == kmax || k == kopt + 1 ) {
               nrc_red = SAFE2/err[km]; 
               break; 
            }
            else if ( k == kopt && alf[kopt - 1][kopt] < err[km] ) {
                  nrc_red = 1.0/err[km]; 
                  break; 
               }
            else if ( kopt == kmax && alf[km][kmax - 1] < err[km] ) {
                  nrc_red = alf[km][kmax - 1]*SAFE2/err[km]; 
                  break; 
               }
            else if ( alf[km][kopt] < err[km] ) {
               nrc_red = alf[km][kopt - 1]/err[km]; 
               break; 
            }
         }
      }
      if ( exitflag ) break; 
      nrc_red = FMIN ( nrc_red, REDMIN ); 
      nrc_red = FMAX ( nrc_red, REDMAX ); 
      h *= nrc_red; 
      reduct = 1; 
   }
   *xx = xnew; 
   *hdid = h; 
   first = 0; 
   wrkmin = 1.0e35; 
   for ( kk = 1; kk <= km; kk ++ ) {
      fact = FMAX ( err[kk], SCALMX ); 
      work = fact*a[kk + 1]; 
      if ( work < wrkmin ) {
         scale = fact; 
         wrkmin = work; 
         kopt = kk + 1; 
      }
   }
   *hnext = h/scale; 
   if ( kopt >= k && kopt != kmax && !reduct ) {
      fact = FMAX ( scale/alf[kopt - 1][kopt], SCALMX ); 
      if ( a[kopt + 1]*fact <= wrkmin ) {
         *hnext = h/fact; 
         kopt ++; 
      }
   }
   nrc_free_vector ( yseq, 1, nv ); 
   nrc_free_vector ( ysav, 1, nv ); 
   nrc_free_vector ( yerr, 1, nv ); 
   nrc_free_vector ( x, 1, KMAXX ); 
   nrc_free_vector ( err, 1, KMAXX ); 
   nrc_free_matrix ( d, 1, nv, 1, KMAXX ); 
}
#undef KMAXX
#undef IMAXX
#undef SAFE1
#undef SAFE2
#undef REDMAX
#undef REDMIN
#undef TINY
#undef SCALMX
#undef NRANSI