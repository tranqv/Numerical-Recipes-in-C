
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
   int i, n, nval; 
   sReal sj, sy, sjp, syp, x, xsj, xsy, xsjp, xsyp; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Spherical Bessel Functions", 26 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 
   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%d %lf %lf %lf %lf %lf", &n, &x, &sj, &sy, &sjp, &syp ); 
      printf ( "%5s %4s\n%14s %16s %17s %16s\n%14s %16s %17s %16s\n", 
         "n", "x", "sj", "sy", "sjp", "syp", "xsj", "xsy", "xsjp", "xsyp" ); 
      nrc_sphbes ( n, x, &xsj, &xsy, &xsjp, &xsyp ); 
      printf ( "%5d %5.2f\n\t%16.6e %16.6e %16.6e %16.6e\n", n, x, sj, sy, sjp, syp ); 
      printf ( "\t%16.6e %16.6e %16.6e %16.6e\n", xsj, xsy, xsjp, xsyp ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
