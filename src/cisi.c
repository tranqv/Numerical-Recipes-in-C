
#include "nrc_types.h"

#include <math.h>
#include "nrc_complex.h"
#define EPS     NR_CONST_EPSI
#define EULER 0.577215664901532860606512090082402431042
#define MAXIT 100
#define PIBY2 1.5707963267948966192313216916397514420986
#define FPMIN   NR_CONST_FPMIN
#define TMIN 2.0
#define TRUE 1
#define ONE nrc_cmplx(1.0,0.0)

void nrc_cisi ( sReal x, sReal *ci, sReal *si )
{
   void nrc_error ( char error_text[] ); 
   int i, k, odd; 
   sReal a, err, fact, sign, sum, sumc, sums, t, term; 
   sComp h, b, c, d, del; 

   t = fabs ( x ); 
   if ( t == 0.0 ) {
      *si = 0.0; 
      *ci = - 1.0/FPMIN; 
      return; 
   }
   if ( t > TMIN ) {
      b = nrc_cmplx ( 1.0, t ); 
      c = nrc_cmplx ( 1.0/FPMIN, 0.0 ); 
      d = h = nrc_cdiv ( ONE, b ); 
      for ( i = 2; i <= MAXIT; i ++ ) {
         a = -( i - 1 )*( i - 1 ); 
         b = nrc_cadd ( b, nrc_cmplx ( 2.0, 0.0 ) ); 
         d = nrc_cdiv ( ONE, nrc_cadd ( nrc_rcmul ( a, d ), b ) ); 
         c = nrc_cadd ( b, nrc_cdiv ( nrc_cmplx ( a, 0.0 ), c ) ); 
         del = nrc_cmul ( c, d ); 
         h = nrc_cmul ( h, del ); 
         if ( fabs ( del.r - 1.0 )+ fabs ( del.i ) < EPS ) break; 
      }
      if ( i > MAXIT ) nrc_error ( "cf failed in nrc_cisi" ); 
      h = nrc_cmul ( nrc_cmplx ( cos ( t ), - sin ( t ) ), h ); 
      *ci = - h.r; 
      *si = PIBY2 + h.i; 
   } else {
      if ( t < sqrt ( FPMIN ) ) {
         sumc = 0.0; 
         sums = t; 
      } else {
         sum = sums = sumc = 0.0; 
         sign = fact = 1.0; 
         odd = TRUE; 
         for ( k = 1; k <= MAXIT; k ++ ) {
            fact *= t/k; 
            term = fact/k; 
            sum += sign*term; 
            err = term/fabs ( sum ); 
            if ( odd ) {
               sign = - sign; 
               sums = sum; 
               sum = sumc; 
            } else {
               sumc = sum; 
               sum = sums; 
            }
            if ( err < EPS ) break; 
            odd =!odd; 
         }
         if ( k > MAXIT ) nrc_error ( "maxits exceeded in nrc_cisi" ); 
      }
      *si = sums; 
      *ci = sumc + log ( t )+ EULER; 
   }
   if ( x < 0.0 ) *si = -( *si ); 
}
#undef EPS
#undef EULER
#undef MAXIT
#undef PIBY2
#undef FPMIN
#undef TMIN
#undef TRUE
#undef ONE
