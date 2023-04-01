
#include "nrc_types.h"

/* Driver for routine nrc_erff */

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
   int i, nval; 
   sReal val, x; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Error Function", 14 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%4s %12s %12s\n", "x", "actual", "erf ( x )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf", &x, &val ); 
      printf ( "%6.2f %12.7f %12.7f\n", x, val, nrc_erff ( x ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
