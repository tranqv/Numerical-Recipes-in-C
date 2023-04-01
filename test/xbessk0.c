
#include "nrc_types.h"

/* Driver for routine nrc_bessk0 */

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
   sReal val, x, y, d; 
   FILE *fp; 

   if ( ( fp = fopen ( "fncval.dat", "r" ) ) == NULL )
      nrc_error ( "Data file fncval.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   while ( strncmp ( txt, "Modified Bessel Function K0", 27 ) ) {
      fgets ( txt, MAXSTR, fp ); 
      if ( feof ( fp ) ) nrc_error ( "Data not found in fncval.dat\n" ); 
   }
   fscanf ( fp, "%d %*s", &nval ); 
   printf ( "\n%s\n", txt ); 

   printf ( "%6s %18s %18s %18s\n", "x", "actual", "nrc_bessk0 ( x )", "Re. Error" ); 

   for ( i = 1; i <= nval; i ++ ) {
      fscanf ( fp, "%lf %lf", &x, &val ); 

      y = nrc_bessk0 ( x ) ; 
      d = fabs ( val - y )/fabs ( val + 1.0e-14 ) ; 

      printf ( "%6.2f %18.7e %18.7e %18.7e\n", x, val, y, d ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
