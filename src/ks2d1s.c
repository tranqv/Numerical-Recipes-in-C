
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_ks2d1s ( sReal x1[], sReal y1[], unsigned long n1, 
   void ( *nrc_quadvl )( sReal, sReal, sReal *, sReal *, sReal *, sReal * ), 
   sReal *d1, sReal *prob )
{
   void nrc_pearsn ( sReal x[], sReal y[], unsigned long n, sReal *r, sReal *prob, 
      sReal *z ); 
   sReal nrc_probks ( sReal alam ); 
   void nrc_quadct ( sReal x, sReal y, sReal xx[], sReal yy[], unsigned long nn, 
      sReal *fa, sReal *fb, sReal *fc, sReal *fd ); 
   unsigned long j; 
   sReal dum, dumm, fa, fb, fc, fd, ga, gb, gc, gd, r1, rr, sqen; 

   *d1 = 0.0; 
   for ( j = 1; j <= n1; j ++ ) {
      nrc_quadct ( x1[j], y1[j], x1, y1, n1, &fa, &fb, &fc, &fd ); 
      ( *nrc_quadvl )( x1[j], y1[j], &ga, &gb, &gc, &gd ); 
      *d1 = FMAX ( *d1, fabs ( fa - ga ) ); 
      *d1 = FMAX ( *d1, fabs ( fb - gb ) ); 
      *d1 = FMAX ( *d1, fabs ( fc - gc ) ); 
      *d1 = FMAX ( *d1, fabs ( fd - gd ) ); 
   }
   nrc_pearsn ( x1, y1, n1, &r1, &dum, &dumm ); 
   sqen = sqrt ( ( dReal ) n1 ); 
   rr = sqrt ( 1.0 - r1*r1 ); 
   *prob = nrc_probks ( *d1*sqen/( 1.0 + rr*( 0.25 - 0.75/sqen ) ) ); 
}
#undef NRANSI
