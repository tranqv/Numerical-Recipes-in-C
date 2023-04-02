
#include "nrc_types.h"

/* Driver for routine nrc_sprspm */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5
#define NMAX (2*NP*NP+1)

int main ( void )
{
   unsigned long i, j, k, *ija, *ijb, *ijbt, *ijc; 
   sReal *sa, *sb, *sbt, *sc, **a, **b, **c, **ab; 
   static sReal ainit[NP][NP]={
      1.0, 0.5, 0.0, 0.0, 0.0, 
      0.5, 2.0, 0.5, 0.0, 0.0, 
      0.0, 0.5, 3.0, 0.5, 0.0, 
      0.0, 0.0, 0.5, 4.0, 0.5, 
      0.0, 0.0, 0.0, 0.5, 5.0}; 
   static sReal binit[NP][NP]={
      1.0, 1.0, 0.0, 0.0, 0.0, 
      1.0, 2.0, 1.0, 0.0, 0.0, 
      0.0, 1.0, 3.0, 1.0, 0.0, 
      0.0, 0.0, 1.0, 4.0, 1.0, 
      0.0, 0.0, 0.0, 1.0, 5.0}; 

   ija = nrc_lvector ( 1, NMAX ); 
   ijb = nrc_lvector ( 1, NMAX ); 
   ijbt = nrc_lvector ( 1, NMAX ); 
   ijc = nrc_lvector ( 1, NMAX ); 
   sa = nrc_vector ( 1, NMAX ); 
   sb = nrc_vector ( 1, NMAX ); 
   sbt = nrc_vector ( 1, NMAX ); 
   sc = nrc_vector ( 1, NMAX ); 
   c = nrc_matrix ( 1, NP, 1, NP ); 
   ab = nrc_matrix ( 1, NP, 1, NP ); 
   a = nrc_convert_matrix ( &ainit[0][0], 1, NP, 1, NP ); 
   b = nrc_convert_matrix ( &binit[0][0], 1, NP, 1, NP ); 
   nrc_sprsin ( a, NP, 0.5, NMAX, sa, ija ); 
   nrc_sprsin ( b, NP, 0.5, NMAX, sb, ijb ); 
   nrc_sprstp ( sb, ijb, sbt, ijbt ); 
   /* specify tridiagonal output, using fact that a is tridiagonal */
   for ( i = 1; i <= ija[ija[1]- 1]- 1; i ++ ) ijc[i]= ija[i]; 
   nrc_sprspm ( sa, ija, sbt, ijbt, sc, ijc ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) {
         ab[i][j]= 0.0; 
         for ( k = 1; k <= NP; k ++ ) {
            ab[i][j]= ab[i][j]+ a[i][k]*b[k][j]; 
         }
      }
   }
   printf ( "Reference nrc_matrix:\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%5.2f\t", ab[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "nrc_sprspm nrc_matrix ( should show only tridiagonals ):\n" ); 
   for ( i = 1; i <= NP; i ++ ) for ( j = 1; j <= NP; j ++ ) c[i][j]= 0.0; 
   for ( i = 1; i <= NP; i ++ ) {
      c[i][i]= sc[i]; 
      for ( j = ijc[i]; j <= ijc[i + 1]- 1; j ++ ) c[i][ijc[j]]= sc[j]; 
   }
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%5.2f\t", c[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_convert_matrix ( b, 1, NP, 1, NP ); 
   nrc_free_convert_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_matrix ( ab, 1, NP, 1, NP ); 
   nrc_free_matrix ( c, 1, NP, 1, NP ); 
   nrc_free_vector ( sc, 1, NMAX ); 
   nrc_free_vector ( sbt, 1, NMAX ); 
   nrc_free_vector ( sb, 1, NMAX ); 
   nrc_free_vector ( sa, 1, NMAX ); 
   nrc_free_lvector ( ijc, 1, NMAX ); 
   nrc_free_lvector ( ijbt, 1, NMAX ); 
   nrc_free_lvector ( ijb, 1, NMAX ); 
   nrc_free_lvector ( ija, 1, NMAX ); 
   return 0; 
}
#undef NRANSI
