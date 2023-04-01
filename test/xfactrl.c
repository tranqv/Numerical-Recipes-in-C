
#include "nrc_types.h"

/* Driver for routine nrc_factrl */

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
   sReal actual; 
   int i, n, nval; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "N - factorial", 11 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%6s %18s %20s \n", "n", "actual", "nrc_factrl ( n )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%d %lf ", &n, &actual ); 
      if ( actual < 1.0e10 )
         printf ( "%6d %20.0f %20.0f\n", n, actual, nrc_factrl ( n ) ); 
      else
         printf ( "%6d %20e %20e \n", n, actual, nrc_factrl ( n ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
