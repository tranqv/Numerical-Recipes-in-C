
#include "nrc_types.h"

/* Driver for routine nrc_f1dim */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

sReal func ( sReal x[] )
{
   int i; 
   sReal f = 0.0; 

   for ( i = 1; i <= 3; i ++ ) f += ( x[i]- 1.0 )*( x[i]- 1.0 ); 
   return f; 
}

#define NDIM 3

int ncom;    /* defining declarations */
sReal *pcom, *xicom, ( *nrfunc )( sReal [] ); 

int main ( void )
{
   ncom = NDIM; 
   pcom = nrc_vector ( 1, ncom ); 
   xicom = nrc_vector ( 1, ncom ); 
   nrfunc = func; 
   pcom[1]= pcom[2]= pcom[3]= 0.0; 
   printf ( "\nEnter nrc_vector direction along which to\n" ); 
   printf ( "plot the function. Minimum is in the\n" ); 
   printf ( "direction 1.0 1.0 1.0 - enter x y z:\n" ); 
   scanf ( " %f %f %f", &xicom[1], &xicom[2], &xicom[3] ); 
   nrc_scrsho ( nrc_f1dim ); 
   nrc_free_vector ( xicom, 1, ncom ); 
   nrc_free_vector ( pcom, 1, ncom ); 
   return 0; 
}
#undef NRANSI
