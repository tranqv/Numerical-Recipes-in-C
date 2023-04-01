
#include "nrc_types.h"

/* Driver for routine nrc_hunt */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 100

int main ( void )
{
   unsigned long i, j, ji; 
   sReal x, *xx; 

   xx = nrc_vector ( 1, N ); 
   /* create array to be searched */
   for ( i = 1; i <= N; i ++ )
      xx[i]= exp ( i/20.0 )- 74.0; 
   printf ( "\n  result of:   j = 0 indicates x too small\n" ); 
   printf ( "%14s j = 100 indicates x too large", " " ); 
   printf ( "\n%12s %8s %4s %11s %13s \n", 
      "nrc_locate:", "guess", "j", "xx ( j )", "xx ( j + 1 )" ); 
   /* do test */
   for ( i = 1; i <= 19; i ++ ) {
      x = - 100.0 + 10.0*i; 
      /* trial parameter */
      j =( ji = 5*i ); 
      /* begin search */
      nrc_hunt ( xx, N, x, &j ); 
      if ( ( j < N ) && ( j > 0 ) )
         printf ( "%12.5f %6lu %6lu %12.6f %12.6f \n", 
            x, ji, j, xx[j], xx[j + 1] ); 
      else if ( j == N )
         printf ( "%12.5f %6lu %6lu %12.6f %s \n", 
            x, ji, j, xx[j], "   upper lim" ); 
      else
         printf ( "%12.5f %6lu %6lu %s %12.6f \n", 
            x, ji, j, "   lower lim", xx[j + 1] ); 
   }
   nrc_free_vector ( xx, 1, N ); 
   return 0; 
}
#undef NRANSI
