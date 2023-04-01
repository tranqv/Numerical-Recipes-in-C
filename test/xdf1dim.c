
#include "nrc_types.h"

/* Driver for routine nrc_df1dim */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDIM 3

int ncom;    /* defining declarations */
sReal *pcom, *xicom; 
void ( *nrdfun )( sReal [],  sReal [] ); 

void dfunc ( sReal x[],  sReal df[] )
{
   int i; 

   for ( i = 1; i <= 3; i ++ ) df[i]=( x[i]- 1.0 )*( x[i]- 1.0 ); 
}

int main ( void )
{
   ncom = NDIM; 
   pcom = nrc_vector ( 1, ncom ); 
   xicom = nrc_vector ( 1, ncom ); 
   nrdfun = dfunc; 
   printf ( "\nEnter nrc_vector direction along which to\n" ); 
   printf ( "plot the function. Minimum is in the\n" ); 
   printf ( "direction 1.0 1.0 1.0 - enter x y z:\n\n" ); 
   pcom[1]= pcom[2]= pcom[3]= 0.0; 
   scanf ( "%f %f %f", &xicom[1], &xicom[2], &xicom[3] ); 
   nrc_scrsho ( nrc_df1dim ); 
   nrc_free_vector ( xicom, 1, ncom ); 
   nrc_free_vector ( pcom, 1, ncom ); 
   return 0; 
}
#undef NRANSI
