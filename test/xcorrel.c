
#include "nrc_types.h"

/* Driver for routine nrc_correl */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 64
#define N2 (2*N)

int main ( void )
{
   unsigned long i, j; 
   sReal cmp, *data1, *data2, *ans; 

   data1 = nrc_vector ( 1, N ); 
   data2 = nrc_vector ( 1, N ); 
   ans = nrc_vector ( 1, N2 ); 
   for ( i = 1; i <= N; i ++ ) {
      if ( ( i > N/2 - N/8 ) && ( i < N/2 + N/8 ) )
         data1[i]= 1.0; 
      else
         data1[i]= 0.0; 
      data2[i]= data1[i]; 
   }
   nrc_correl ( data1, data2, N, ans ); 
   /* Calculate directly */
   printf ( "%3s %14s %18s\n", "n", "CORREL", "direct calc." ); 
   for ( i = 0; i <= 16; i ++ ) {
      cmp = 0.0; 
      for ( j = 1; j <= N; j ++ )
         cmp += data1[( ( i + j - 1 ) % N )+ 1]*data2[j]; 
      printf ( "%3ld %15.6f %15.6f\n", i, ans[i + 1], cmp ); 
   }
   nrc_free_vector ( ans, 1, N2 ); 
   nrc_free_vector ( data2, 1, N ); 
   nrc_free_vector ( data1, 1, N ); 
   return 0; 
}
#undef NRANSI
