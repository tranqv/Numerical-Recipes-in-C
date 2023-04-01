
#include "nrc_types.h"

/* Driver for routine nrc_rj */

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
   sReal p, val, x, y, z; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Elliptic Integral Third Kind RJ", 31 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%7s %8s %8s %8s %16s %20s\n", "x", "y", "z", "p", "actual", "nrc_rj ( x, y, z, p )" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf %lf %lf", &x, &y, &z, &p, &val ); 
      printf ( "%8.2f %8.2f %8.2f %8.2f %18.6e %18.6e\n", x, y, z, p, val, nrc_rj ( x, y, z, p ) ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
