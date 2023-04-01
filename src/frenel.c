
#include "nrc_types.h"

#include <math.h>
#include "nrc_complex.h"
#define EPS     NR_CONST_EPSI
#define MAXIT 100
#define FPMIN   NR_CONST_FPMIN
#define XMIN 1.5
#define PI 3.141592653589793238462643383279502884197
#define PIBY2 (PI/2.0)
#define TRUE 1
#define ONE nrc_cmplx(1.0,0.0)

void nrc_frenel ( sReal x, sReal *s, sReal *c )
{
   void nrc_error ( char error_text[] ); 
   int k, n, odd; 
   sReal a, ax, fact, pix2, sign, sum, sumc, sums, term, test; 
   sComp b, cc, d, h, del, cs; 

   ax = fabs ( x ); 
   if ( ax < sqrt ( FPMIN ) ) {
      *s = 0.0; 
      *c = ax; 
   } else if ( ax <= XMIN ) {
      sum = sums = 0.0; 
      sumc = ax; 
      sign = 1.0; 
      fact = PIBY2*ax*ax; 
      odd = TRUE; 
      term = ax; 
      n = 3; 
      for ( k = 1; k <= MAXIT; k ++ ) {
         term *= fact/k; 
         sum += sign*term/n; 
         test = fabs ( sum )*EPS; 
         if ( odd ) {
            sign = - sign; 
            sums = sum; 
            sum = sumc; 
         } else {
            sumc = sum; 
            sum = sums; 
         }
         if ( term < test ) break; 
         odd =!odd; 
         n += 2; 
      }
      if ( k > MAXIT ) nrc_error ( "series failed in nrc_frenel" ); 
      *s = sums; 
      *c = sumc; 
   } else {
      pix2 = PI*ax*ax; 
      b = nrc_cmplx ( 1.0, - pix2 ); 
      cc = nrc_cmplx ( 1.0/FPMIN, 0.0 ); 
      d = h = nrc_cdiv ( ONE, b ); 
      n = - 1; 
      for ( k = 2; k <= MAXIT; k ++ ) {
         n += 2; 
         a = - n*( n + 1 ); 
         b = nrc_cadd ( b, nrc_cmplx ( 4.0, 0.0 ) ); 
         d = nrc_cdiv ( ONE, nrc_cadd ( nrc_rcmul ( a, d ), b ) ); 
         cc = nrc_cadd ( b, nrc_cdiv ( nrc_cmplx ( a, 0.0 ), cc ) ); 
         del = nrc_cmul ( cc, d ); 
         h = nrc_cmul ( h, del ); 
         if ( fabs ( del.r - 1.0 )+ fabs ( del.i ) < EPS ) break; 
      }
      if ( k > MAXIT ) nrc_error ( "cf failed in nrc_frenel" ); 
      h = nrc_cmul ( nrc_cmplx ( ax, - ax ), h ); 
      cs = nrc_cmul ( nrc_cmplx ( 0.5, 0.5 ), 
         nrc_csub ( ONE, nrc_cmul ( nrc_cmplx ( cos ( 0.5*pix2 ), sin ( 0.5*pix2 ) ), h ) ) ); 
      *c = cs.r; 
      *s = cs.i; 
   }
   if ( x < 0.0 ) {
      *c = -( *c ); 
      *s = -( *s ); 
   }
}
#undef EPS
#undef MAXIT
#undef FPMIN
#undef XMIN
#undef PI
#undef PIBY2
#undef TRUE
#undef ONE
