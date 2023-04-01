
#include "nrc_types.h"

/* Driver for routine nrc_rc */

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
   sReal val, x, y; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Elliptic Integral Degenerate RC", 31 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%7s %8s %16s %18s\n", "x", "y", "actual", "nrc_rc ( x, y )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf", &x, &y, &val ); 
      printf ( "%8.2f %8.2f %18.6e %18.6e\n", x, y, val, nrc_rc ( x, y ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
