
#include "nrc_types.h"

/* Driver for routine nrc_polin2 */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 5
#define PI 3.1415926

int main ( void )
{
   int i, j; 
   sReal dy, f, x1, x2, y, *x1a, *x2a, **ya; 

   x1a = nrc_vector ( 1, N ); 
   x2a = nrc_vector ( 1, N ); 
   ya = nrc_matrix ( 1, N, 1, N ); 
   for ( i = 1; i <= N; i ++ ) {
      x1a[i]= i*PI/N; 
      for ( j = 1; j <= N; j ++ ) {
         x2a[j]= 1.0*j/N; 
         ya[i][j]= sin ( x1a[i] )*exp ( x2a[j] ); 
      }
   }
   /* test 2 - dimensional interpolation */
   printf ( "\nTwo dimensional interpolation of sin ( x1 ) exp ( x2 )\n" ); 
   printf ( "%9s %12s %13s %16s %11s\n", 
      "x1", "x2", "f ( x )", "interpolated", "error" ); 
   for ( i = 1; i <= 4; i ++ ) {
      x1 =( - 0.1 + i/5.0 )*PI; 
      for ( j = 1; j <= 4; j ++ ) {
         x2 = - 0.1 + j/5.0; 
         f = sin ( x1 )*exp ( x2 ); 
         nrc_polin2 ( x1a, x2a, ya, N, N, x1, x2, &y, &dy ); 
         printf ( "%12.6f %12.6f %12.6f %12.6f %15.6f\n", 
            x1, x2, f, y, dy ); 
      }
      printf ( "***********************************\n" ); 
   }
   nrc_free_matrix ( ya, 1, N, 1, N ); 
   nrc_free_vector ( x2a, 1, N ); 
   nrc_free_vector ( x1a, 1, N ); 
   return 0; 
}
#undef NRANSI
