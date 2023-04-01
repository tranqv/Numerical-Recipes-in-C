
#include "nrc_types.h"

#include <math.h>

void nrc_choldc ( sReal **a, int n, sReal p[] )
{
   void nrc_error ( char error_text[] ); 
   int i, j, k; 
   sReal sum; 

   for ( i = 1; i <= n; i ++ ) {
      for ( j = i; j <= n; j ++ ) {
         for ( sum = a[i][j], k = i - 1; k >= 1; k -- ) sum -= a[i][k]*a[j][k]; 
         if ( i == j ) {
            if ( sum <= 0.0 )
               nrc_error ( "nrc_choldc failed" ); 
            p[i]= sqrt ( sum ); 
         } else a[j][i]= sum/p[i]; 
      }
   }
}
