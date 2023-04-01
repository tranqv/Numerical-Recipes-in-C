
#include "nrc_types.h"

/* Driver for routine nrc_bandec */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

int main ( void )
{
   sReal d, **a, **al, *b, *x; 
   unsigned long i, j, *indx; 
   long idum =( - 1 ); 

   a = nrc_matrix ( 1, 7, 1, 4 ); 
   x = nrc_vector ( 1, 7 ); 
   b = nrc_vector ( 1, 7 ); 
   al = nrc_matrix ( 1, 7, 1, 2 ); 
   indx = nrc_lvector ( 1, 7 ); 
   for ( i = 1; i <= 7; i ++ ) {
      x[i]= nrc_ran1 ( &idum ); 
      for ( j = 1; j <= 4; j ++ ) {
         a[i][j]= nrc_ran1 ( &idum ); 
      }
   }
   nrc_banmul ( a, 7, 2, 1, x, b ); 
   for ( i = 1; i <= 7; i ++ ) printf ( "%ld %12.6f %12.6f\n", i, b[i], x[i] ); 
   nrc_bandec ( a, 7, 2, 1, al, indx, &d ); 
   nrc_banbks ( a, 7, 2, 1, al, indx, b ); 
   for ( i = 1; i <= 7; i ++ ) printf ( "%ld %12.6f %12.6f\n", i, b[i], x[i] ); 
   nrc_free_lvector ( indx, 1, 7 ); 
   nrc_free_matrix ( al, 1, 7, 1, 2 ); 
   nrc_free_vector ( b, 1, 7 ); 
   nrc_free_vector ( x, 1, 7 ); 
   nrc_free_matrix ( a, 1, 7, 1, 4 ); 
   return 0; 
}
#undef NRANSI
