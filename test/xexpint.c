
#include "nrc_types.h"

/* Driver for routine nrc_expint */

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
   int i, nval, n; 
   sReal val, x; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Exponential Integral En", 23 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%4s %7s %15s %21s \n", "n", "x", "actual", "nrc_expint ( n, x )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%d %lf %lf", &n, &x, &val ); 
      printf ( "%4d %8.2f %18.6e %18.6e\n", n, x, val, nrc_expint ( n, x ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
