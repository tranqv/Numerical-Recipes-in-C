
#include "nrc_types.h"

/* Driver for routine nrc_factln */

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
   int i, n, nval; 
   sReal val; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "N - factorial", 11 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\nlog of n_factorial\n" ); 
   printf ( "\n%6s %19s %21s\n", "n", "actual", "nrc_factln ( n )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%d %lf", &n, &val ); 
      printf ( "%6d %20.7f %20.7f\n", n, log ( val ), nrc_factln ( n ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
