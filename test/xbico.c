
#include "nrc_types.h"

/* Driver for routine nrc_bico */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80

int main ( void )
{
   char txt[MAXSTR]; 
   int i, k, n, nval; 
   sReal binco; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Binomial Coefficients", 21 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%6s %6s %12s %12s \n", "n", "k", "actual", "nrc_bico ( n, k )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%d %d %lf ", &n, &k, &binco ); 
      printf ( "%6d %6d %12.0f %12.0f \n", n, k, binco, nrc_bico ( n, k ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
