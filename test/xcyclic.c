
#include "nrc_types.h"

/* Driver for routine nrc_cyclic */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 20

int main ( void )
{
   sReal alpha, nrc_beta, d, *a, *b, *c, *r, *x, **aa; 
   int i, j, *indx; 
   long idum =( - 23 ); 

   indx = nrc_ivector ( 1, N ); 
   a = nrc_vector ( 1, N ); 
   b = nrc_vector ( 1, N ); 
   c = nrc_vector ( 1, N ); 
   r = nrc_vector ( 1, N ); 
   x = nrc_vector ( 1, N ); 
   aa = nrc_matrix ( 1, N, 1, N ); 
   for ( i = 1; i <= N; i ++ )
      for ( j = 1; j <= N; j ++ ) aa[i][j]= 0.0; 
   for ( i = 1; i <= N; i ++ ) {
      b[i]= nrc_ran2 ( &idum ); 
      aa[i][i]= b[i]; 
      r[i]= nrc_ran2 ( &idum ); 
   }
   for ( i = 1; i < N; i ++ ) {
      a[i + 1]= nrc_ran2 ( &idum ); 
      aa[i + 1][i]= a[i + 1]; 
      c[i]= nrc_ran2 ( &idum ); 
      aa[i][i + 1]= c[i]; 
   }
   alpha = nrc_ran2 ( &idum ); 
   aa[N][1]= alpha; 
   nrc_beta = nrc_ran2 ( &idum ); 
   aa[1][N]= nrc_beta; 
   nrc_cyclic ( a, b, c, alpha, nrc_beta, r, x, N ); 
   nrc_ludcmp ( aa, N, indx, &d ); 
   nrc_lubksb ( aa, N, indx, r ); 
   for ( i = 1; i <= N; i ++ ) printf ( "%4d %12.6e\n", i, ( x[i]- r[i] )/( x[i]+ r[i] ) ); 
   nrc_free_matrix ( aa, 1, N, 1, N ); 
   nrc_free_vector ( x, 1, N ); 
   nrc_free_vector ( r, 1, N ); 
   nrc_free_vector ( c, 1, N ); 
   nrc_free_vector ( b, 1, N ); 
   nrc_free_vector ( a, 1, N ); 
   nrc_free_ivector ( indx, 1, N ); 
   return 0; 
}
#undef NRANSI
