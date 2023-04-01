
#include "nrc_types.h"

/* Driver for routine nrc_evlmem */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 1000
#define M 10
#define NFDT 16

int main ( void )
{
   int i; 
   sReal fdt, pm, *cof, *data; 
   FILE *fp; 

   cof = nrc_vector ( 1, M ); 
   data = nrc_vector ( 1, N ); 
   if ( ( fp = fopen ( "spctrl.dat", "r" ) ) == NULL )
      nrc_error ( "Data file spctrl.dat not found\n" ); 
   for ( i = 1; i <= N; i ++ ) fscanf ( fp, "%lf", &data[i] ); 
   fclose ( fp ); 
   nrc_memcof ( data, N, M, &pm, cof ); 
   printf ( "Power spectum estimate of data in spctrl.dat\n" ); 
   printf ( "     f*delta      power\n" ); 
   for ( fdt = 0.0; fdt <= 0.5; fdt += 0.5/NFDT )
      printf ( "%12.6f %12.6f\n", fdt, nrc_evlmem ( fdt, cof, M, pm ) ); 
   nrc_free_vector ( data, 1, N ); 
   nrc_free_vector ( cof, 1, M ); 
   return 0; 
}
#undef NRANSI
