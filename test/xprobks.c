
#include "nrc_types.h"

/* Driver for routine nrc_probks */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define NPTS 20
#define EPS 0.1
#define ISCAL 40

int main ( void )
{
   int i, j, jmax; 
   char txt[ISCAL + 1]; 
   sReal alam, aval; 

   printf ( "probability function for kolmogorov - smirnov statistic\n\n" ); 
   printf ( "%7s %10s %13s\n", "lambda", "value:", "graph:" ); 
   for ( i = 1; i <= NPTS; i ++ ) {
      alam = i*EPS; 
      aval = nrc_probks ( alam ); 
      jmax =( int ) ( 0.5 +( ISCAL - 1 )*aval ); 
      for ( j = 0; j < ISCAL; j ++ ) {
         if ( j < jmax )
            txt[j]='*'; 
         else
            txt[j]=' '; 
      }
      txt[ISCAL]='\0'; 
      printf ( "%8.6f %10.6f %s\n", alam, aval, txt ); 
   }
   return 0; 
}
#undef NRANSI
