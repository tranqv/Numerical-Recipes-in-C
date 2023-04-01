
#include "nrc_types.h"

/* Driver for routine nrc_expdev */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define NPTS 10000
#define EE 2.718281828

int main ( void )
{
   long idum =( 1 ); 
   int i, j, total = 0, x[21]; 
   sReal expect, xx, y, trig[21]; 

   for ( i = 0; i <= 20; i ++ ) {
      trig[i]= i/20.0; 
      x[i]= 0; 
   }
   for ( i = 1; i <= NPTS; i ++ ) {
      y = nrc_expdev ( &idum ); 
      for ( j = 1; j <= 20; j ++ )
         if ( ( y < trig[j] ) && ( y > trig[j - 1] ) ) ++ x[j]; 
   }
   for ( i = 1; i <= 20; i ++ ) total += x[i]; 
   printf ( "\nexponential distribution with %7d points\n", NPTS ); 
   printf ( "    interval      observed     expected\n\n" ); 
   for ( i = 1; i <= 20; i ++ ) {
      xx =( sReal ) x[i]/total; 
      expect = exp ( -( trig[i - 1]+ trig[i] )/2.0 ); 
      expect *= ( 0.05*EE/( EE-1 ) ); 
      printf ( "%6.2f %6.2f %12.6f %12.6f \n", 
         trig[i - 1], trig[i], xx, expect ); 
   }
   return 0; 
}
#undef NRANSI
