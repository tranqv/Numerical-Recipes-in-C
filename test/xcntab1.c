
#include "nrc_types.h"

/* Driver for routine nrc_cntab1 */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDAT 9
#define NMON 12
#define MAXSTR 80

int main ( void )
{
   int i, j, **nmbr; 
   sReal ccc, chisq, cramrv, df, prob; 
   char dummy[MAXSTR], fate[NDAT + 1][16], mon[NMON + 1][6], txt[16]; 
   FILE *fp; 

   nmbr = nrc_imatrix ( 1, NDAT, 1, NMON ); 
   if ( ( fp = fopen ( "table1.dat", "r" ) ) == NULL )
      nrc_error ( "Data file table1.dat not found\n" ); 
   fgets ( dummy, MAXSTR, fp ); 
   fgets ( dummy, MAXSTR, fp ); 
   fscanf ( fp, "%16c", txt ); 
   txt[15]='\0'; 
   for ( i = 1; i <= 12; i ++ ) fscanf ( fp, " %s", mon[i] ); 
   fgets ( dummy, MAXSTR, fp ); 
   fgets ( dummy, MAXSTR, fp ); 
   for ( i = 1; i <= NDAT; i ++ ) {
      fscanf ( fp, "%16[^0123456789]", fate[i] ); 
      fate[i][15]='\0'; 
      for ( j = 1; j <= 12; j ++ )
         fscanf ( fp, "%d ", &nmbr[i][j] ); 
   }
   fclose ( fp ); 
   printf ( "\n%s", txt ); 
   for ( i = 1; i <= 12; i ++ ) printf ( "%5s", mon[i] ); 
   printf ( "\n\n" ); 
   for ( i = 1; i <= NDAT; i ++ ) {
      printf ( "%s", fate[i] ); 
      for ( j = 1; j <= 12; j ++ ) printf ( "%5d", nmbr[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_cntab1 ( nmbr, NDAT, NMON, &chisq, &df, &prob, &cramrv, &ccc ); 
   printf ( "\n%15s chi - squared %20.2f\n", " ", chisq ); 
   printf ( "%15s degrees of freedom%20.2f\n", " ", df ); 
   printf ( "%15s probability %20.4f\n", " ", prob ); 
   printf ( "%15s cramer - v %20.4f\n", " ", cramrv ); 
   printf ( "%15s contingency coeff.%20.4f\n", " ", ccc ); 
   nrc_free_imatrix ( nmbr, 1, NDAT, 1, NMON ); 
   return 0; 
}
#undef NRANSI
