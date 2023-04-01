
#include "nrc_types.h"

/* Driver for routine nrc_memcof */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 1000
#define M 10

int main ( void )
{
   int i; 
   sReal pm, *cof, *data; 
   FILE *fp; 

   cof = nrc_vector ( 1, M ); 
   data = nrc_vector ( 1, N ); 
   if ( ( fp = fopen ( "spctrl.dat", "r" ) ) == NULL )
      nrc_error ( "Data file spctrl.dat not found\n" ); 
   for ( i = 1; i <= N; i ++ ) fscanf ( fp, "%lf", &data[i] ); 
   fclose ( fp ); 
   nrc_memcof ( data, N, M, &pm, cof ); 
   printf ( "Coefficients for spectral estimation of spctrl.dat\n\n" ); 
   for ( i = 1; i <= M; i ++ ) printf ( "a[%2d] = %12.6f \n", i, cof[i] ); 
   printf ( "\na0 =%12.6f\n", pm ); 
   nrc_free_vector ( data, 1, N ); 
   nrc_free_vector ( cof, 1, M ); 
   return 0; 
}
#undef NRANSI
