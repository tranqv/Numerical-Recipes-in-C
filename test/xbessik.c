
#include "nrc_types.h"

/* Driver for routine nrc_bessik */

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
   sReal ri, rk, rip, rkp, x, xnu, xri, xrk, xrip, xrkp; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Modified Bessel Functions", 25 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   printf ( "%5s %7s\n%14s %16s %17s %16s\n%14s %16s %17s %16s\n", 
      "xnu", "x", "ri", "rk", "rip", "rkp", "xri", "xrk", "xrip", "xrkp" ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf %lf %lf %lf %lf", &xnu, &x, &ri, &rk, &rip, &rkp ); 
      nrc_bessik ( x, xnu, &xri, &xrk, &xrip, &xrkp ); 
      printf ( "%5.2f %5.2f\n\t%16.6e %16.6e %16.6e %16.6e\n", xnu, x, ri, rk, rip, rkp ); 
      printf ( "\t%16.6e %16.6e %16.6e %16.6e\n", xri, xrk, xrip, xrkp ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
