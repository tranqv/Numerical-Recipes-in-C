
#include "nrc_types.h"

/* Driver for routine nrc_gammp */

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
   sReal a, val, x; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Incomplete Gamma Function", 25 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%4s %11s %14s %14s \n", "a", "x", "actual", "nrc_gammp ( a, x )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf", &a, &x, &val ); 
      printf ( "%6.2f %12.6f %12.6f %12.6f \n", a, x, val, nrc_gammp ( a, x ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
