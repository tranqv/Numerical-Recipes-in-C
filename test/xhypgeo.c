
#include "nrc_types.h"

/* Driver for routine nrc_hypgeo */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"
#include "nrc_complex.h"

sComp Clog ( sComp a )
{
   sComp b; 

   b.r = log ( nrc_cabs ( a ) ); 
   b.i = atan2 ( a.i, a.r ); 
   return b; 
}

int main ( void )
{
   sComp a, b, c, z, zi, q1, q2, q3, q4; 
   sReal x, y; 

   a = nrc_cmplx ( 0.5, 0.0 ); 
   b = nrc_cmplx ( 1.0, 0.0 ); 
   c = nrc_cmplx ( 1.5, 0.0 ); 
   for ( ; ; ) {
      printf ( "INPUT X, Y OF COMPLEX ARGUMENT:\n" ); 
      if ( scanf ( "%lf %lf", &x, &y ) == EOF ) break; 
      z = nrc_cmplx ( x, y ); 
      q1 = nrc_hypgeo ( a, b, c, nrc_cmul ( z, z ) ); 
      q2 = nrc_rcmul ( 0.5, nrc_cdiv ( Clog ( nrc_cdiv ( nrc_cadd ( b, z ), nrc_csub ( b, z ) ) ), z ) ); 
      q3 = nrc_hypgeo ( a, b, c, nrc_rcmul ( - 1.0, nrc_cmul ( z, z ) ) ); 
      zi = nrc_cmplx ( - y, x ); 
      q4 = nrc_rcmul ( 0.5, nrc_cdiv ( Clog ( nrc_cdiv ( nrc_cadd ( b, zi ), nrc_csub ( b, zi ) ) ), zi ) ); 
      printf ( "2F1 ( 0.5, 1.0, 1.5; z^2 ) =%12.6f %12.6f\n", q1.r, q1.i ); 
      printf ( "check using log form: %12.6f %12.6f\n", q2.r, q2.i ); 
      printf ( "2F1 ( 0.5, 1.0, 1.5; - z^2 )=%12.6f %12.6f\n", q3.r, q3.i ); 
      printf ( "check using log form: %12.6f %12.6f\n", q4.r, q4.i ); 
   }
   return 0; 
}
#undef NRANSI
