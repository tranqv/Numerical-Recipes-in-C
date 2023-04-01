
#include "nrc_types.h"

/* Driver for routine nrc_avevar */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NPTS 1000
#define EPS 0.1

int main ( void )
{
   int i, j; 
   long idum =( - 5 ); 
   sReal ave, shift, vrnce, *data; 

   data = nrc_vector ( 1, NPTS ); 
   /* generate gaussian distributed data */
   printf ( "\n%9s %11s %12s\n", "shift", "average", "variance" ); 
   for ( i = 1; i <= 11; i ++ ) {
      shift =( i - 1 )*EPS; 
      for ( j = 1; j <= NPTS; j ++ )
         data[j]= shift + i*nrc_gasdev ( &idum ); 
      nrc_avevar ( data, NPTS, &ave, &vrnce ); 
      printf ( "%8.2f %11.2f %12.2f\n", shift, ave, vrnce ); 
   }
   nrc_free_vector ( data, 1, NPTS ); 
   return 0; 
}
#undef NRANSI
