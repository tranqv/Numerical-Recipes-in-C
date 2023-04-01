
#include "nrc_types.h"

/* Driver for routine nrc_gcf */

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
   sReal a, val, x, gammcf, gln; 
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
   printf ( "%4s %11s %14s %13s %13s %8s\n", "a", "x", 
      "actual", "nrc_gcf ( a, x )", "nrc_gammln ( a )", "gln" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf", &a, &x, &val ); 
      if ( x >= ( a + 1.0 ) ) {
         nrc_gcf ( &gammcf, a, x, &gln ); 
         printf ( "%6.2f%13.6f%13.6f%13.6f%12.6f%13.6f\n", 
            a, x, ( 1.0 - val ), gammcf, nrc_gammln ( a ), gln ); 
      }
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
