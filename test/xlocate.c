
#include "nrc_types.h"

/* Driver for routine nrc_locate */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 100

int main ( void )
{
   unsigned long i, j; 
   sReal x, *xx; 

   xx = nrc_vector ( 1, N ); 
   /* create array to be searched */
   for ( i = 1; i <= N; i ++ )
      xx[i]= exp ( i/20.0 )- 74.0; 
   printf ( "\nresult of:  j = 0 indicates x too small\n" ); 
   printf ( "%11s j = 100 indicates x too large", " " ); 
   printf ( "\n%10s %6s %11s %12s \n", "nrc_locate ", "j", "xx ( j )", "xx ( j + 1 )" ); 
   /* perform test */
   for ( i = 1; i <= 19; i ++ ) {
      x = - 100.0 + 200.0*i/20.0; 
      nrc_locate ( xx, N, x, &j ); 
      if ( ( j < N ) && ( j > 0 ) )
         printf ( "%10.4f %6lu %12.6f %12.6f\n", 
            x, j, xx[j], xx[j + 1] ); 
      else if ( j == N )
         printf ( "%10.4f %6lu %12.6f %s\n", 
            x, j, xx[j], "   upper lim" ); 
      else
         printf ( "%10.4f %6lu %s %12.6f \n", 
            x, j, "   lower lim", xx[j + 1] ); 
   }
   nrc_free_vector ( xx, 1, N ); 
   return 0; 
}
#undef NRANSI
