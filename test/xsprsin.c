
#include "nrc_types.h"

/* Driver for routine nrc_sprsin */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5
#define NMAX (2*NP*NP+1)

int main ( void )
{
   unsigned long i, j, msize, *ija; 
   sReal **a, **aa, *sa; 
   static sReal ainit[NP][NP]={
      3.0, 0.0, 1.0, 0.0, 0.0, 
      0.0, 4.0, 0.0, 0.0, 0.0, 
      0.0, 7.0, 5.0, 9.0, 0.0, 
      0.0, 0.0, 0.0, 0.0, 2.0, 
      0.0, 0.0, 0.0, 6.0, 5.0}; 

   ija = nrc_lvector ( 1, NMAX ); 
   sa = nrc_vector ( 1, NMAX ); 
   aa = nrc_matrix ( 1, NP, 1, NP ); 
   a = nrc_convert_matrix ( &ainit[0][0], 1, NP, 1, NP ); 
   nrc_sprsin ( a, NP, 0.5, NMAX, sa, ija ); 
   msize = ija[ija[1]- 1]- 1; 
   sa[NP + 1]= 0.0; 
   printf ( "index\tija\t\tsa\n" ); 
   for ( i = 1; i <= msize; i ++ ) printf ( "%lu\t%lu\t%12.6f\n", i, ija[i], sa[i] ); 
   for ( i = 1; i <= NP; i ++ ) for ( j = 1; j <= NP; j ++ ) aa[i][j]= 0.0; 
   for ( i = 1; i <= NP; i ++ ) {
      aa[i][i]= sa[i]; 
      for ( j = ija[i]; j <= ija[i + 1]- 1; j ++ ) aa[i][ija[j]]= sa[j]; 
   }
   printf ( "Original Matrix\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%5.2f\t", a[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "Reconstructed Matrix\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%5.2f\t", aa[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_convert_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_matrix ( aa, 1, NP, 1, NP ); 
   nrc_free_vector ( sa, 1, NMAX ); 
   nrc_free_lvector ( ija, 1, NMAX ); 
   return 0; 
}
#undef NRANSI
