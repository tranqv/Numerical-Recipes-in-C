
#include "nrc_types.h"

/* Driver for routine nrc_caldat */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80

int main ( void )
{
   int i, id, idd, im, imm, iy, iyy, n; 
   long j; 
   char dummy[MAXSTR]; 
   static char *name[]={"", "january", "february", "march", 
      "april", "may", "june", "july", "august", 
      "september", "october", "november", "december"}; 
   FILE *fp; 

   /* Check whether nrc_caldat properly undoes the operation of nrc_julday */
   if ( ( fp = fopen ( "dates1.dat", "r" ) ) == NULL )
      nrc_error ( "Data file dates1.dat not found\n" ); 
   fgets ( dummy, MAXSTR, fp ); 
   fscanf ( fp, "%d %*s ", &n ); 
   printf ( "\n %14s %43s\n", "original date:", "reconstructed date" ); 
   printf ( "%8s %5s %6s %15s %12s %5s %6s\n", "month", "day", "year", 
      "julian day", "month", "day", "year" ); 
   for ( i = 1; i <= n; i ++ ) {
      fscanf ( fp, "%d %d %d ", &im, &id, &iy ); 
      fgets ( dummy, MAXSTR, fp ); 
      j = nrc_julday ( im, id, iy ); 
      nrc_caldat ( j, &imm, &idd, &iyy ); 
      printf ( "%10s %3d %6d %13ld %16s %3d %6d\n", name[im], 
         id, iy, j, name[imm], idd, iyy ); 
   }
   fclose ( fp ); 
   return 0; 
}
#undef NRANSI
