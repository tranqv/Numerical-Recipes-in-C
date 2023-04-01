
#include "nrc_types.h"

/* Driver for routine nrc_golden */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define TOL 1.0e-6
#define EQL 1.0e-3

sReal func ( sReal x )
{
   return nrc_bessj0 ( x ); 
}

int main ( void )
{
   int i, iflag, j, nmin = 0; 
   sReal ax, bx, cx, fa, fb, fc, xmin, gold, amin[21]; 

   printf ( "Minima of the function nrc_bessj0\n" ); 
   printf ( "%10s %8s %17s %12s\n", "min. #", "x", "nrc_bessj0 ( x )", "nrc_bessj1 ( x )" ); 
   for ( i = 1; i <= 100; i ++ ) {
      ax = i; 
      bx = i + 1.0; 
      nrc_mnbrak ( &ax, &bx, &cx, &fa, &fb, &fc, func ); 
      gold = nrc_golden ( ax, bx, cx, func, TOL, &xmin ); 
      if ( nmin == 0 ) {
         amin[1]= xmin; 
         nmin = 1; 
         printf ( "%7d %15.6f %12.6f %12.6f\n", 
            nmin, xmin, nrc_bessj0 ( xmin ), nrc_bessj1 ( xmin ) ); 
      } else {
         iflag = 0; 
         for ( j = 1; j <= nmin; j ++ )
            if ( fabs ( xmin - amin[j] ) <= EQL*xmin ) iflag = 1; 
         if ( iflag == 0 ) {
            amin[++ nmin]= xmin; 
            printf ( "%7d %15.6f %12.6f %12.6f\n", 
               nmin, xmin, nrc_bessj0 ( xmin ), nrc_bessj1 ( xmin ) ); 
         }
      }
   }
   return 0; 
}
#undef NRANSI
