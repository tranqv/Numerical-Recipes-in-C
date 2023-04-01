
#include "nrc_types.h"

/* Driver for routine nrc_mprove */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 5
#define NP N

int main ( void )
{
   int i, j, *indx; 
   long idum =( - 13 ); 
   sReal d, *x, **a, **aa; 
   static sReal ainit[NP][NP]=
      {1.0, 2.0, 3.0, 4.0, 5.0, 
      2.0, 3.0, 4.0, 5.0, 1.0, 
      1.0, 1.0, 1.0, 1.0, 1.0, 
      4.0, 5.0, 1.0, 2.0, 3.0, 
      5.0, 1.0, 2.0, 3.0, 4.0}; 
   static sReal b[N + 1]={0.0, 1.0, 1.0, 1.0, 1.0, 1.0}; 

   indx = nrc_ivector ( 1, N ); 
   x = nrc_vector ( 1, N ); 
   a = nrc_convert_matrix ( &ainit[0][0], 1, N, 1, N ); 
   aa = nrc_matrix ( 1, N, 1, N ); 
   for ( i = 1; i <= N; i ++ ) {
      x[i]= b[i]; 
      for ( j = 1; j <= N; j ++ )
         aa[i][j]= a[i][j]; 
   }
   nrc_ludcmp ( aa, N, indx, &d ); 
   nrc_lubksb ( aa, N, indx, x ); 
   printf ( "\nSolution nrc_vector for the equations:\n" ); 
   for ( i = 1; i <= N; i ++ ) printf ( "%12.6f", x[i] ); 
   printf ( "\n" ); 
   /* now phoney up x and let nrc_mprove fix it */
   for ( i = 1; i <= N; i ++ ) x[i] *= ( 1.0 + 0.2*nrc_ran3 ( &idum ) ); 
   printf ( "\nSolution nrc_vector with noise added:\n" ); 
   for ( i = 1; i <= N; i ++ ) printf ( "%12.6f", x[i] ); 
   printf ( "\n" ); 
   nrc_mprove ( a, aa, N, indx, b, x ); 
   printf ( "\nSolution nrc_vector recovered by nrc_mprove:\n" ); 
   for ( i = 1; i <= N; i ++ ) printf ( "%12.6f", x[i] ); 
   printf ( "\n" ); 
   nrc_free_matrix ( aa, 1, N, 1, N ); 
   nrc_free_convert_matrix ( a, 1, N, 1, N ); 
   nrc_free_vector ( x, 1, N ); 
   nrc_free_ivector ( indx, 1, N ); 
   return 0; 
}
#undef NRANSI
