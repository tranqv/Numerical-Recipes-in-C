
#include "nrc_types.h"

/* Driver for routine nrc_sprstp */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5
#define NMAX (2*NP*NP+1)

int main ( void )
{
   unsigned long i, j, *ija, *ijat; 
   sReal **a, **at, *sa, *sat; 
   static sReal ainit[NP][NP]={
      3.0, 0.0, 1.0, 0.0, 0.0, 
      0.0, 4.0, 0.0, 0.0, 0.0, 
      0.0, 7.0, 5.0, 9.0, 0.0, 
      0.0, 0.0, 0.0, 0.0, 2.0, 
      0.0, 0.0, 0.0, 6.0, 5.0}; 

   ija = nrc_lvector ( 1, NMAX ); 
   ijat = nrc_lvector ( 1, NMAX ); 
   sa = nrc_vector ( 1, NMAX ); 
   sat = nrc_vector ( 1, NMAX ); 
   at = nrc_matrix ( 1, NP, 1, NP ); 
   a = nrc_convert_matrix ( &ainit[0][0], 1, NP, 1, NP ); 
   nrc_sprsin ( a, NP, 0.5, NMAX, sa, ija ); 
   nrc_sprstp ( sa, ija, sat, ijat ); 
   for ( i = 1; i <= NP; i ++ ) for ( j = 1; j <= NP; j ++ ) at[i][j]= 0.0; 
   for ( i = 1; i <= NP; i ++ ) {
      at[i][i]= sat[i]; 
      for ( j = ijat[i]; j <= ijat[i + 1]- 1; j ++ ) at[i][ijat[j]]= sat[j]; 
   }
   printf ( "Original Matrix\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%5.2f\t", a[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "Transpose\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%5.2f\t", at[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_convert_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_matrix ( at, 1, NP, 1, NP ); 
   nrc_free_vector ( sat, 1, NMAX ); 
   nrc_free_vector ( sa, 1, NMAX ); 
   nrc_free_lvector ( ijat, 1, NMAX ); 
   nrc_free_lvector ( ija, 1, NMAX ); 
   return 0; 
}
#undef NRANSI
