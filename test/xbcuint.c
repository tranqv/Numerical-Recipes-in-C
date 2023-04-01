
#include "nrc_types.h"

/* Driver for routine nrc_bcuint */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

int main ( void )
{
   int i; 
   sReal ansy, ansy1, ansy2, ey, ey1, ey2; 
   sReal x1, x1l, x1u, x1x2, x2, x2l, x2u, xxyy; 
   sReal y[5], y1[5], y12[5], y2[5]; 
   static sReal xx[]={0.0, 0.0, 2.0, 2.0, 0.0}; 
   static sReal yy[]={0.0, 0.0, 0.0, 2.0, 2.0}; 

   x1l = xx[1]; 
   x1u = xx[2]; 
   x2l = yy[1]; 
   x2u = yy[4]; 
   for ( i = 1; i <= 4; i ++ ) {
      xxyy = xx[i]*yy[i]; 
      y[i]= xxyy*xxyy; 
      y1[i]= 2.0*yy[i]*xxyy; 
      y2[i]= 2.0*xx[i]*xxyy; 
      y12[i]= 4.0*xxyy; 
   }
   printf ( "\n%6s %8s %7s %11s %6s %10s %6s %10s \n\n", 
      "x1", "x2", "y", "expect", "y1", "expect", "y2", "expect" ); 
   for ( i = 1; i <= 10; i ++ ) {
      x2 =( x1 = 0.2*i ); 
      nrc_bcuint ( y, y1, y2, y12, x1l, x1u, x2l, x2u, x1, x2, &ansy, &ansy1, &ansy2 ); 
      x1x2 = x1*x2; 
      ey = x1x2*x1x2; 
      ey1 = 2.0*x2*x1x2; 
      ey2 = 2.0*x1*x1x2; 
      printf ( "%8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n", 
         x1, x2, ansy, ey, ansy1, ey1, ansy2, ey2 ); 
   }
   return 0; 
}
#undef NRANSI
