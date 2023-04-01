
#include "nrc_types.h"

/* Driver for routine nrc_gammln */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80

int main ( void )
{
   char txt[MAXSTR]; 
   int i, nval; 
   sReal actual, calc, x; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Gamma Function", 14 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%10s %21s %21s\n", "x", "actual", "nrc_gammln ( x )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf", &x, &actual ); 
      if ( x > 0.0 ) {
         calc =( x < 1.0 ? nrc_gammln ( x + 1.0 )- log ( x ) : nrc_gammln ( x ) ); 
         printf ( "%12.2f %20.6f %20.6f\n", x, 
            log ( actual ), calc ); 
      }
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
