
#include "nrc_types.h"

/* Driver for routine nrc_ran4 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

int main ( void )
{
   int i; 
   static long idum[5]={0, - 1, 99, - 99, 99}; 
   static char *ansvax[5]={"", "0.275898", "0.208204", "0.034307", "0.838676"}; 
   static char *ansiee[5]={"", "0.219120", "0.849246", "0.375290", "0.457334"}; 
   sReal random[5]; 

   for ( i = 1; i <= 4; i ++ ) random[i]= nrc_ran4 ( &idum[i] ); 
   printf ( "nrc_ran4 gets values: " ); 
   for ( i = 1; i <= 4; i ++ ) printf ( "%15.6f", random[i] ); 
   printf ( "\n    IEEE answers: " ); 
   for ( i = 1; i <= 4; i ++ ) printf ( "%15s", ansiee[i] ); 
   printf ( "\n     VAX answers: " ); 
   for ( i = 1; i <= 4; i ++ ) printf ( "%15s", ansvax[i] ); 
   printf ( "\n" ); 
   return 0; 
}
#undef NRANSI
