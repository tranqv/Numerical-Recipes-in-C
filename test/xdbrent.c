
#include "nrc_types.h"

/* Driver for routine nrc_dbrent */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"

#define TOL 1.0e-6
#define EQL 1.0e-4

sReal dfunc ( sReal x )
{
   return - nrc_bessj1 ( x ); 
}

sReal func ( sReal x )
{
   return nrc_bessj0 ( x ); 
}

int main ( void )
{
   int i, iflag, j, nmin = 0; 
   sReal ax, bx, cx, fa, fb, fc, xmin, dbr, amin[21]; 

   printf ( "\nMinima of the function nrc_bessj0\n" ); 
   printf ( "%10s %8s %16s %12s %11s\n", 
      "min. #", "x", "nrc_bessj0 ( x )", "nrc_bessj1 ( x )", "DBRENT" ); 
   for ( i = 1; i <= 100; i ++ ) {
      ax = i; 
      bx = i + 1.0; 
      nrc_mnbrak ( &ax, &bx, &cx, &fa, &fb, &fc, func ); 
      dbr = nrc_dbrent ( ax, bx, cx, func, dfunc, TOL, &xmin ); 
      if ( nmin == 0 ) {
         amin[1]= xmin; 
         nmin = 1; 
         printf ( "%7d %15.6f %12.6f %12.6f %12.6f\n", 
            nmin, xmin, func ( xmin ), dfunc ( xmin ), dbr ); 
      } else {
         iflag = 0; 
         for ( j = 1; j <= nmin; j ++ )
            if ( fabs ( xmin - amin[j] ) <= EQL*xmin ) iflag = 1; 
         if ( iflag == 0 ) {
            amin[++ nmin]= xmin; 
            printf ( "%7d %15.6f %12.6f %12.6f %12.6f\n", 
               nmin, xmin, func ( xmin ), dfunc ( xmin ), dbr ); 
         }
      }
   }
   return 0; 
}
#undef NRANSI
