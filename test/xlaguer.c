
#include "nrc_types.h"

/* Driver for routine nrc_laguer */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_complex.h"

#define M 4     /* degree of polynomial */
#define MP1 (M+1)   /* no. of polynomial coefficients */
#define NTRY 21
#define NTRY1 NTRY+1
#define EPS 1.e-6

int main ( void )
{
   sComp y[NTRY1], x; 
   static sComp a[MP1]={{0.0, 2.0}, 
            {0.0, 0.0}, 
            {- 1.0, - 2.0}, 
            {0.0, 0.0}, 
            {1.0, 0.0} }; 
   int i, iflag, its, j, n = 0; 

   printf ( "\nRoots of polynomial x^4 -( 1 + 2i )*x^2 + 2i\n" ); 
   printf ( "\n%15s %15s %7s\n", "Real", "nrc_cmplx", "#iter" ); 
   for ( i = 1; i <= NTRY; i ++ ) {
      x = nrc_cmplx ( ( i - 11.0 )/10.0, ( i - 11.0 )/10.0 ); 
      nrc_laguer ( a, M, &x, &its ); 
      if ( n == 0 ) {
         n = 1; 
         y[1]= x; 
         printf ( "%5d %12.6f %12.6f %5d\n", n, x.r, x.i, its ); 
      } else {
         iflag = 0; 
         for ( j = 1; j <= n; j ++ )
            if ( nrc_cabs ( nrc_csub ( x, y[j] ) ) <= EPS*nrc_cabs ( x ) ) iflag = 1; 
         if ( iflag == 0 ) {
            y[++ n]= x; 
            printf ( "%5d %12.6f %12.6f %5d\n", n, x.r, x.i, its ); 
         }
      }
   }
   return 0; 
}
#undef NRANSI
