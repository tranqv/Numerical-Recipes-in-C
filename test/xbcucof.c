
#include "nrc_types.h"

/* Driver for routine nrc_bcucof */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

int main ( void )
{
   int i, j; 
   sReal d1, d2, ee, x1x2; 
   sReal y[5], y1[5], y2[5], y12[5], **c; 
   static sReal x1[]={0.0, 0.0, 2.0, 2.0, 0.0}; 
   static sReal x2[]={0.0, 0.0, 0.0, 2.0, 2.0}; 

   c = nrc_matrix ( 1, 4, 1, 4 ); 
   d1 = x1[2]- x1[1]; 
   d2 = x2[4]- x2[1]; 
   for ( i = 1; i <= 4; i ++ ) {
      x1x2 = x1[i]*x2[i]; 
      ee = exp ( - x1x2 ); 
      y[i]= x1x2*ee; 
      y1[i]= x2[i]*( 1.0 - x1x2 )*ee; 
      y2[i]= x1[i]*( 1.0 - x1x2 )*ee; 
      y12[i]=( 1.0 - 3.0*x1x2 + x1x2*x1x2 )*ee; 
   }
   nrc_bcucof ( y, y1, y2, y12, d1, d2, c ); 
   printf ( "\nCoefficients for bicubic interpolation:\n\n" ); 
   for ( i = 1; i <= 4; i ++ ) {
      for ( j = 1; j <= 4; j ++ ) printf ( "%12.6f", c[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_matrix ( c, 1, 4, 1, 4 ); 
   return 0; 
}
#undef NRANSI
