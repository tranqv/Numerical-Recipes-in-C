
#include "nrc_types.h"

#include <math.h>
#include "nrc_complex.h"
#define NRANSI
#include "nrc_util.h"
#define EPSS 1.0e-7
#define MR 8
#define MT 10
#define MAXIT (MT*MR)

void nrc_laguer ( sComp a[], int m, sComp *x, int *its )
{
   int iter, j; 
   sReal abx, abp, abm, err; 
   sComp dx, x1, b, d, f, g, h, sq, gp, gm, g2; 
   static sReal frac[MR + 1] = {0.0, 0.5, 0.25, 0.75, 0.13, 0.38, 0.62, 0.88, 1.0}; 

   for ( iter = 1; iter <= MAXIT; iter ++ ) {
      *its = iter; 
      b = a[m]; 
      err = nrc_cabs ( b ); 
      d = f = nrc_cmplx ( 0.0, 0.0 ); 
      abx = nrc_cabs ( *x ); 
      for ( j = m - 1; j >= 0; j -- ) {
         f = nrc_cadd ( nrc_cmul ( *x, f ), d ); 
         d = nrc_cadd ( nrc_cmul ( *x, d ), b ); 
         b = nrc_cadd ( nrc_cmul ( *x, b ), a[j] ); 
         err = nrc_cabs ( b )+ abx*err; 
      }
      err *= EPSS; 
      if ( nrc_cabs ( b ) <= err ) return; 
      g = nrc_cdiv ( d, b ); 
      g2 = nrc_cmul ( g, g ); 
      h = nrc_csub ( g2, nrc_rcmul ( 2.0, nrc_cdiv ( f, b ) ) ); 
      sq = nrc_csqrt ( nrc_rcmul ( ( sReal ) ( m - 1 ), nrc_csub ( nrc_rcmul ( ( sReal ) m, h ), g2 ) ) ); 
      gp = nrc_cadd ( g, sq ); 
      gm = nrc_csub ( g, sq ); 
      abp = nrc_cabs ( gp ); 
      abm = nrc_cabs ( gm ); 
      if ( abp < abm ) gp = gm; 
      dx =( ( FMAX ( abp, abm ) > 0.0 ? nrc_cdiv ( nrc_cmplx ( ( sReal ) m, 0.0 ), gp )
         : nrc_rcmul ( 1 + abx, nrc_cmplx ( cos ( ( sReal ) iter ), sin ( ( sReal ) iter ) ) ) ) ); 
      x1 = nrc_csub ( *x, dx ); 
      if ( x -> r == x1.r && x -> i == x1.i ) return; 
      if ( iter % MT ) *x = x1; 
      else *x = nrc_csub ( *x, nrc_rcmul ( frac[iter/MT], dx ) ); 
   }
   nrc_error ( "too many iterations in nrc_laguer" ); 
   return; 
}
#undef EPSS
#undef MR
#undef MT
#undef MAXIT
#undef NRANSI
