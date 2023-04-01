
#include "nrc_types.h"

/* Driver for routine nrc_fgauss */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPT 3
#define NLIN 2
#define NA 3*NLIN

int main ( void )
{
   int i, j; 
   sReal e1, e2, f, x, y; 
   static sReal a[NA + 1]={0.0, 3.0, 0.2, 0.5, 1.0, 0.7, 0.3}; 
   sReal dyda[NA + 1], df[NA + 1]; 

   printf ( "\n%6s %8s %8s %7s %7s %7s %7s %7s\n", 
      "x", "y", "dyda1", "dyda2", "dyda3", "dyda4", "dyda5", "dyda6" ); 
   for ( i = 1; i <= NPT; i ++ ) {
      x = 0.3*i; 
      nrc_fgauss ( x, a, &y, dyda, NA ); 
      e1 = exp ( - SQR ( ( x - a[2] )/a[3] ) ); 
      e2 = exp ( - SQR ( ( x - a[5] )/a[6] ) ); 
      f = a[1]*e1 + a[4]*e2; 
      df[1]= e1; 
      df[4]= e2; 
      df[2]= a[1]*e1*2.0*( x - a[2] )/( a[3]*a[3] ); 
      df[5]= a[4]*e2*2.0*( x - a[5] )/( a[6]*a[6] ); 
      df[3]= a[1]*e1*2.0*SQR ( x - a[2] )/( a[3]*a[3]*a[3] ); 
      df[6]= a[4]*e2*2.0*SQR ( x - a[5] )/( a[6]*a[6]*a[6] ); 
      printf ( "from FGAUSS\n" ); 
      printf ( "%8.4f %8.4f", x, y ); 
      for ( j = 1; j <= 6; j ++ ) printf ( "%8.4f", dyda[j] ); 
      printf ( "\nindependent calc.\n" ); 
      printf ( "%8.4f %8.4f", x, f ); 
      for ( j = 1; j <= 6; j ++ ) printf ( "%8.4f", df[j] ); 
      printf ( "\n\n" ); 
   }
   return 0; 
}
#undef NRANSI
