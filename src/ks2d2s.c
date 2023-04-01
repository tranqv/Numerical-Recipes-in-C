
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_ks2d2s ( sReal x1[], sReal y1[], unsigned long n1, sReal x2[], sReal y2[], 
   unsigned long n2, sReal *d, sReal *prob )
{
   void nrc_pearsn ( sReal x[], sReal y[], unsigned long n, sReal *r, sReal *prob, 
      sReal *z ); 
   sReal nrc_probks ( sReal alam ); 
   void nrc_quadct ( sReal x, sReal y, sReal xx[], sReal yy[], unsigned long nn, 
      sReal *fa, sReal *fb, sReal *fc, sReal *fd ); 
   unsigned long j; 
   sReal d1, d2, dum, dumm, fa, fb, fc, fd, ga, gb, gc, gd, r1, r2, rr, sqen; 

   d1 = 0.0; 
   for ( j = 1; j <= n1; j ++ ) {
      nrc_quadct ( x1[j], y1[j], x1, y1, n1, &fa, &fb, &fc, &fd ); 
      nrc_quadct ( x1[j], y1[j], x2, y2, n2, &ga, &gb, &gc, &gd ); 
      d1 = FMAX ( d1, fabs ( fa - ga ) ); 
      d1 = FMAX ( d1, fabs ( fb - gb ) ); 
      d1 = FMAX ( d1, fabs ( fc - gc ) ); 
      d1 = FMAX ( d1, fabs ( fd - gd ) ); 
   }
   d2 = 0.0; 
   for ( j = 1; j <= n2; j ++ ) {
      nrc_quadct ( x2[j], y2[j], x1, y1, n1, &fa, &fb, &fc, &fd ); 
      nrc_quadct ( x2[j], y2[j], x2, y2, n2, &ga, &gb, &gc, &gd ); 
      d2 = FMAX ( d2, fabs ( fa - ga ) ); 
      d2 = FMAX ( d2, fabs ( fb - gb ) ); 
      d2 = FMAX ( d2, fabs ( fc - gc ) ); 
      d2 = FMAX ( d2, fabs ( fd - gd ) ); 
   }
   *d = 0.5*( d1 + d2 ); 
   sqen = sqrt ( n1*n2/( dReal )( n1 + n2 ) ); 
   nrc_pearsn ( x1, y1, n1, &r1, &dum, &dumm ); 
   nrc_pearsn ( x2, y2, n2, &r2, &dum, &dumm ); 
   rr = sqrt ( 1.0 - 0.5*( r1*r1 + r2*r2 ) ); 
   *prob = nrc_probks ( *d*sqen/( 1.0 + rr*( 0.25 - 0.75/sqen ) ) ); 
}
#undef NRANSI
