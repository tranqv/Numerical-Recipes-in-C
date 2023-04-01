
#include "nrc_types.h"

/* Driver for routine nrc_pearsn */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define N 10

int main ( void )
{
   int i; 
   sReal prob, r, z; 
   static sReal dose[N + 1]=
      {0.0, 56.1, 64.1, 70.0, 66.6, 82.0, 91.3, 90.0, 99.7, 115.3, 110.0}; 
   static sReal spore[N + 1]=
      {0.0, 0.11, 0.40, 0.37, 0.48, 0.75, 0.66, 0.71, 1.20, 1.01, 0.95}; 

   printf ( "\nEffect of Gamma Rays on Man - in - the - Moon Marigolds\n" ); 
   printf ( "%16s %23s\n", "Count Rate ( cpm )", "Pollen Index" ); 
   for ( i = 1; i <= N; i ++ )
      printf ( "%10.2f %25.2f \n", dose[i], spore[i] ); 
   nrc_pearsn ( dose, spore, N, &r, &prob, &z ); 
   printf ( "\n%30s %16s\n", "PEARSN", "Expected" ); 
   printf ( "%s %8s %9f %15f\n", "Corr. Coeff.", " ", r, 0.9069586 ); 
   printf ( "%s %9s %9f %15f\n", "Probability", " ", prob, 0.2926505e-3 ); 
   printf ( "%s %10s %9f %15f\n", "Fisher's z", " ", z, 1.510110 ); 
   return 0; 
}
#undef NRANSI
