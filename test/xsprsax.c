
#include "nrc_types.h"

/* Driver for routine nrc_sprsax */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5
#define NMAX (2*NP*NP+1)

int main ( void )
{
   unsigned long i, j, msize, *ija; 
   sReal **a, *sa, *ax, *b; 
   static sReal ainit[NP][NP]={
      3.0, 0.0, 1.0, 0.0, 0.0, 
      0.0, 4.0, 0.0, 0.0, 0.0, 
      0.0, 7.0, 5.0, 9.0, 0.0, 
      0.0, 0.0, 0.0, 0.0, 2.0, 
      0.0, 0.0, 0.0, 6.0, 5.0}; 
   static sReal x[NP + 1]={0.0, 1.0, 2.0, 3.0, 4.0, 5.0}; 

   ija = nrc_lvector ( 1, NMAX ); 
   ax = nrc_vector ( 1, NP ); 
   b = nrc_vector ( 1, NP ); 
   sa = nrc_vector ( 1, NMAX ); 
   a = nrc_convert_matrix ( &ainit[0][0], 1, NP, 1, NP ); 
   nrc_sprsin ( a, NP, 0.5, NMAX, sa, ija ); 
   msize = ija[1]- 2; 
   nrc_sprsax ( sa, ija, x, b, msize ); 
   for ( i = 1; i <= msize; i ++ )
      for ( ax[i]= 0.0, j = 1; j <= msize; j ++ ) ax[i] += a[i][j]*x[j]; 
   printf ( "\tReference\tsprsax result\n" ); 
   for ( i = 1; i <= msize; i ++ ) printf ( "\t%5.2f\t\t%5.2f\n", ax[i], b[i] ); 
   nrc_free_convert_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( sa, 1, NMAX ); 
   nrc_free_vector ( b, 1, NP ); 
   nrc_free_vector ( ax, 1, NP ); 
   nrc_free_lvector ( ija, 1, NMAX ); 
   return 0; 
}
#undef NRANSI
