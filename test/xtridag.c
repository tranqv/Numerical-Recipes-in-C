
#include "nrc_types.h"

/* Driver for routine nrc_tridag */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 20
#define MAXSTR 80

int main ( void )
{
   unsigned long k, n; 
   sReal *diag, *superd, *subd, *rhs, *u; 
   char dummy[MAXSTR]; 
   FILE *fp; 

   diag = nrc_vector ( 1, NP ); 
   superd = nrc_vector ( 1, NP ); 
   subd = nrc_vector ( 1, NP ); 
   rhs = nrc_vector ( 1, NP ); 
   u = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "matrx2.dat", "r" ) ) == NULL )
      nrc_error ( "Data file matrx2.dat not found\n" ); 
   while ( !feof ( fp ) ) {
      fgets ( dummy, MAXSTR, fp ); 
      fgets ( dummy, MAXSTR, fp ); 
      fscanf ( fp, "%ld ", &n ); 
      fgets ( dummy, MAXSTR, fp ); 
      for ( k = 1; k <= n; k ++ ) fscanf ( fp, "%lf ", &diag[k] ); 
      fgets ( dummy, MAXSTR, fp ); 
      for ( k = 1; k < n; k ++ ) fscanf ( fp, "%lf ", &superd[k] ); 
      fgets ( dummy, MAXSTR, fp ); 
      for ( k = 2; k <= n; k ++ ) fscanf ( fp, "%lf ", &subd[k] ); 
      fgets ( dummy, MAXSTR, fp ); 
      for ( k = 1; k <= n; k ++ ) fscanf ( fp, "%lf ", &rhs[k] ); 
      /* carry out solution */
      nrc_tridag ( subd, diag, superd, rhs, u, n ); 
      printf ( "\nThe solution nrc_vector is:\n" ); 
      for ( k = 1; k <= n; k ++ ) printf ( "%12.6f", u[k] ); 
      printf ( "\n" ); 
      /* test solution */
      printf ( "\n ( nrc_matrix )*( sol'n nrc_vector ) should be:\n" ); 
      for ( k = 1; k <= n; k ++ ) printf ( "%12.6f", rhs[k] ); 
      printf ( "\n" ); 
      printf ( "actual result is:\n" ); 
      for ( k = 1; k <= n; k ++ ) {
         if ( k == 1 )
            rhs[k]= diag[1]*u[1]+ superd[1]*u[2]; 
         else if ( k == n )
            rhs[k]= subd[n]*u[n - 1]+ diag[n]*u[n]; 
         else
            rhs[k]= subd[k]*u[k - 1]+ diag[k]*u[k]
               + superd[k]*u[k + 1]; 
      }
      for ( k = 1; k <= n; k ++ ) printf ( "%12.6f", rhs[k] ); 
      printf ( "\n" ); 
      printf ( "***********************************\n" ); 
      printf ( "press return for next problem:\n" ); 
      ( void ) getchar ( ); 
   }
   fclose ( fp ); 
   nrc_free_vector ( u, 1, NP ); 
   nrc_free_vector ( rhs, 1, NP ); 
   nrc_free_vector ( subd, 1, NP ); 
   nrc_free_vector ( superd, 1, NP ); 
   nrc_free_vector ( diag, 1, NP ); 
   return 0; 
}
#undef NRANSI
