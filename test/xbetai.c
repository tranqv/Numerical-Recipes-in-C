
#include "nrc_types.h"

/* Driver for routine nrc_betai */

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
   sReal a, b, x, val; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Incomplete Beta Function", 24 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%5s %10s %12s %14s %13s \n", 
      "a", "b", "x", "actual", "nrc_betai ( x )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf %lf", &a, &b, &x, &val ); 
      printf ( "%6.2f %12.6f %12.6f %12.6f %12.6f\n", 
         a, b, x, val, nrc_betai ( a, b, x ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
