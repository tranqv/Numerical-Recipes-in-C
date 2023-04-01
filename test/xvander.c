
#include "nrc_types.h"

/* Driver for routine nrc_vander */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 5

int main ( void )
{
   int i, j; 
   dReal sum = 0.0, *w, *term; 
   static dReal x[]={0.0, 1.0, 1.5, 2.0, 2.5, 3.0}; 
   static dReal q[]={0.0, 1.0, 1.5, 2.0, 2.5, 3.0}; 

   w = nrc_dvector ( 1, N ); 
   term = nrc_dvector ( 1, N ); 
   nrc_vander ( x, w, q, N ); 
   printf ( "\nSolution nrc_vector:\n" ); 
   for ( i = 1; i <= N; i ++ )
      printf ( "%7s%1d%2s %12f \n", "w[", i, "]=", w[i] ); 
   printf ( "\nTest of solution nrc_vector:\n" ); 
   printf ( "%14s %11s\n", "mtrx*sol'n", "original" ); 
   for ( i = 1; i <= N; i ++ ) {
      term[i]= w[i]; 
      sum += w[i]; 
   }
   printf ( "%12.4f %12.4f\n", sum, q[1] ); 
   for ( i = 2; i <= N; i ++ ) {
      sum = 0.0; 
      for ( j = 1; j <= N; j ++ ) {
         term[j] *= x[j]; 
         sum += term[j]; 
      }
      printf ( "%12.4f %12.4f\n", sum, q[i] ); 
   }
   nrc_free_dvector ( term, 1, N ); 
   nrc_free_dvector ( w, 1, N ); 
   return 0; 
}
#undef NRANSI
