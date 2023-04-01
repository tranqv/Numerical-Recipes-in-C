
#include "nrc_types.h"

/* Driver for routine nrc_qroot */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 6 /* degree of polynomial */
#define EPS 1.0e-6
#define NTRY 10
#define TINY 1.0e-5

int main ( void )
{
   int i, j, nflag, nroot = 0; 
   static sReal p[N + 1]={10.0, - 18.0, 25.0, - 24.0, 16.0, - 6.0, 1.0}; 
   sReal *b, *c; 

   b = nrc_vector ( 1, NTRY ); 
   c = nrc_vector ( 1, NTRY ); 
   printf ( "\nP ( x )= x^6 - 6x^5 + 16x^4 - 24x^3 + 25x^2 - 18x + 10\n" ); 
   printf ( "Quadratic factors x^2 + bx + c\n\n" ); 
   printf ( "%6s %10s %12s \n\n", "factor", "b", "c" ); 
   for ( i = 1; i <= NTRY; i ++ ) {
      c[i]= 0.5*i; 
      b[i] = - 0.5*i; 
      nrc_qroot ( p, N, &b[i], &c[i], EPS ); 
      if ( nroot == 0 ) {
         printf ( "%4d %15.6f %12.6f\n", nroot, b[i], c[i] ); 
         nroot = 1; 
      } else {
         nflag = 0; 
         for ( j = 1; j <= nroot; j ++ )
            if ( ( fabs ( b[i]- b[j] ) < TINY )
               && ( fabs ( c[i]- c[j] ) < TINY ) )
               nflag = 1; 
         if ( nflag == 0 ) {
            printf ( "%4d %15.6f %12.6f\n", nroot, b[i], c[i] ); 
            ++ nroot; 
         }
      }
   }
   nrc_free_vector ( c, 1, NTRY ); 
   nrc_free_vector ( b, 1, NTRY ); 
   return 0; 
}
#undef NRANSI
