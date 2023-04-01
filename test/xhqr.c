
#include "nrc_types.h"

/* Driver for routine nrc_hqr */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 5

int main ( void )
{
   int i, j; 
   static sReal c[NP][NP]=
      {1.0, 2.0, 0.0, 0.0, 0.0, 
      - 2.0, 3.0, 0.0, 0.0, 0.0, 
      3.0, 4.0, 50.0, 0.0, 0.0, 
      - 4.0, 5.0, - 60.0, 7.0, 0.0, 
      - 5.0, 6.0, - 70.0, 8.0, - 9.0}; 
   sReal *wr, *wi, **a; 

   wr = nrc_vector ( 1, NP ); 
   wi = nrc_vector ( 1, NP ); 
   a = nrc_convert_matrix ( &c[0][0], 1, NP, 1, NP ); 
   printf ( "nrc_matrix:\n" ); 
   for ( i = 1; i <= NP; i ++ ) {
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.2f", a[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_balanc ( a, NP ); 
   nrc_elmhes ( a, NP ); 
   nrc_hqr ( a, NP, wr, wi ); 
   printf ( "eigenvalues:\n" ); 
   printf ( "%11s %16s \n", "real", "imag." ); 
   for ( i = 1; i <= NP; i ++ ) printf ( "%15f %14f\n", wr[i], wi[i] ); 
   nrc_free_convert_matrix ( a, 1, NP, 1, NP ); 
   nrc_free_vector ( wi, 1, NP ); 
   nrc_free_vector ( wr, 1, NP ); 
   return 0; 
}
#undef NRANSI
