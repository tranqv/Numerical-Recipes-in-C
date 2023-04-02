
#include "nrc_types.h"

/* Driver for routine nrc_cntab2 */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NI 9
#define NMON 12
#define MAXSTR 80

int main ( void )
{
   sReal h, hx, hxgy, hy, hygx, uxgy, uxy, uygx; 
   int i, j, **nmbr; 
   char dummy[MAXSTR], fate[NI + 1][16], mon[NMON + 1][6], txt[16]; 
   FILE *fp; 

   nmbr = nrc_imatrix ( 1, NI, 1, NMON ); 
   if ( ( fp = fopen ( "table1.dat", "r" ) ) == NULL )
      nrc_error ( "Data file table1.dat not found\n" ); 
   fgets ( dummy, MAXSTR, fp ); 
   fgets ( dummy, MAXSTR, fp ); 
   fscanf ( fp, "%16c", txt ); 
   txt[15]='\0'; 
   for ( i = 1; i <= 12; i ++ ) fscanf ( fp, " %s", mon[i] ); 
   fgets ( dummy, MAXSTR, fp ); 
   fgets ( dummy, MAXSTR, fp ); 
   for ( i = 1; i <= NI; i ++ ) {
      fscanf ( fp, "%16[^0123456789]", fate[i] ); 
      fate[i][15]='\0'; 
      for ( j = 1; j <= 12; j ++ )
         fscanf ( fp, "%d ", &nmbr[i][j] ); 
   }
   fclose ( fp ); 
   printf ( "\n%s", txt ); 
   for ( i = 1; i <= 12; i ++ ) printf ( "%5s", mon[i] ); 
   printf ( "\n\n" ); 
   for ( i = 1; i <= NI; i ++ ) {
      printf ( "%s", fate[i] ); 
      for ( j = 1; j <= 12; j ++ ) printf ( "%5d", nmbr[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_cntab2 ( nmbr, NI, NMON, &h, &hx, &hy, &hygx, &hxgy, &uygx, &uxgy, &uxy ); 
   printf ( "\n entropy of table %10.4f\n", h ); 
   printf ( "       entropy of x - distribution %10.4f\n", hx ); 
   printf ( "       entropy of y - distribution %10.4f\n", hy ); 
   printf ( "       entropy of y given x %10.4f\n", hygx ); 
   printf ( "       entropy of x given y %10.4f\n", hxgy ); 
   printf ( "       dependency of y on x %10.4f\n", uygx ); 
   printf ( "       dependency of x on y %10.4f\n", uxgy ); 
   printf ( "       symmetrical dependency %10.4f\n", uxy ); 
   nrc_free_imatrix ( nmbr, 1, NI, 1, NMON ); 
   return 0; 
}
#undef NRANSI
