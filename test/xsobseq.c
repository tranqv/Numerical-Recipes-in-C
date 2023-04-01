
#include "nrc_types.h"

/* Driver for routine nrc_sobseq */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

int main ( void )
{
   int i, n1 =( - 1 ), n2 = 3; 
   sReal *x; 

   x = nrc_vector ( 1, n2 ); 
   nrc_sobseq ( &n1, x ); 
   for ( i = 1; i <= 32; i ++ ) {
      nrc_sobseq ( &n2, x ); 
      printf ( " %10.5f %10.5f %10.5f %5d\n", x[1], x[2], x[3], i ); 
   }
   nrc_free_vector ( x, 1, n2 ); 
   return 0; 
}
#undef NRANSI
