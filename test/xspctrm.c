
#include "nrc_types.h"

/* Driver for routine nrc_spctrm */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define M 16
#define TRUE 1
#define FALSE 0

int main ( void )
{
   int j, k, ovrlap; 
   sReal *p, *q; 
   FILE *fp; 

   p = nrc_vector ( 1, M ); 
   q = nrc_vector ( 1, M ); 
   if ( ( fp = fopen ( "spctrl.dat", "r" ) ) == NULL )
      nrc_error ( "Data file spctrl.dat not found\n" ); 
   k = 8; 
   ovrlap = TRUE; 
   nrc_spctrm ( fp, p, M, k, ovrlap ); 
   rewind ( fp ); 
   k = 16; 
   ovrlap = FALSE; 
   nrc_spctrm ( fp, q, M, k, ovrlap ); 
   fclose ( fp ); 
   printf ( "\nSpectrum of data in file spctrl.dat\n" ); 
   printf ( "%13s %s %5s %s\n", " ", "overlapped ", " ", "non - overlapped" ); 
   for ( j = 1; j <= M; j ++ )
      printf ( "%3d %5s %13f %5s %13f\n", j, " ", p[j], " ", q[j] ); 
   nrc_free_vector ( q, 1, M ); 
   nrc_free_vector ( p, 1, M ); 
   return 0; 
}
#undef NRANSI
