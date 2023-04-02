
#include "nrc_types.h"

/* Driver for routine nrc_kendl1 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDAT 200

int main ( void )
{
   int i, j; 
   long idum; 
   sReal prob, tau, z, *data1, *data2; 
   static char *txt[5]={"RAN0", "RAN1", "RAN2", "RAN3", "RAN4"}; 

   data1 = nrc_vector ( 1, NDAT ); 
   data2 = nrc_vector ( 1, NDAT ); 
   /* Look for correlations in RAN0, RAN1, RAN2, RAN3 and RAN4 */
   printf ( "\nPair correlations of RAN0 ... RAN4\n\n" ); 
   printf ( "%9s %17s %16s %18s\n", 
      "Program", "Kendall tau", "Std. Dev.", "Probability" ); 
   for ( i = 1; i <= 5; i ++ ) {
      idum =( - 1357 ); 
      for ( j = 1; j <= NDAT; j ++ ) {
         if ( i == 1 ) {
            data1[j]= nrc_ran0 ( &idum ); 
            data2[j]= nrc_ran0 ( &idum ); 
         } else if ( i == 2 ) {
            data1[j]= nrc_ran1 ( &idum ); 
            data2[j]= nrc_ran1 ( &idum ); 
         } else if ( i == 3 ) {
            data1[j]= nrc_ran2 ( &idum ); 
            data2[j]= nrc_ran2 ( &idum ); 
         } else if ( i == 4 ) {
            data1[j]= nrc_ran3 ( &idum ); 
            data2[j]= nrc_ran3 ( &idum ); 
         } else if ( i == 5 ) {
            data1[j]= nrc_ran4 ( &idum ); 
            data2[j]= nrc_ran4 ( &idum ); 
         }
      }
      nrc_kendl1 ( data1, data2, NDAT, &tau, &z, &prob ); 
      printf ( "%8s %17.6f %17.6f %17.6f\n", txt[i - 1], tau, z, prob ); 
   }
   nrc_free_vector ( data2, 1, NDAT ); 
   nrc_free_vector ( data1, 1, NDAT ); 
   return 0; 
}
#undef NRANSI
