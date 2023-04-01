
#include "nrc_types.h"

/* Driver for routine nrc_julday */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80

int main ( void )
{
   int i, id, im, iy, n; 
   char txt[MAXSTR]; 
   static char *name[]={"", "january", "february", "march", 
      "april", "may", "june", "july", "august", "september", 
      "october", "november", "december"}; 
   FILE *fp; 

   if ( ( fp = fopen ( "dates1.dat", "r" ) ) == NULL )
      nrc_error ( "Data file dates1.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   fscanf ( fp, "%d %*s ", &n ); 
   printf ( "\n%5s %8s %6s %12s %9s\n", "month", "day", "year", 
      "julian day", "event" ); 
   for ( i = 1; i <= n; i ++ ) {
      fscanf ( fp, "%d %d %d ", &im, &id, &iy ); 
      fgets ( txt, MAXSTR, fp ); 
      printf ( "%- 10s %3d %6d %10ld %5s %s", name[im], id, iy, 
         nrc_julday ( im, id, iy ), " ", txt ); 
   }
   fclose ( fp ); 
   printf ( "\nYour choices: ( negative to end )\n" ); 
   printf ( "month day year ( e.g. 1 13 1905 )\n" ); 
   for ( i = 1; i <= 20; i ++ ) {
      printf ( "\nmm dd yyyy ?\n" ); 
      scanf ( "%d %d %d", &im, &id, &iy ); 
      if ( im < 0 ) return 0; 
      printf ( "julian day: %ld \n", nrc_julday ( im, id, iy ) ); 
   }
   return 0; 
}
#undef NRANSI
