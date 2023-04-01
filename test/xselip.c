
#include "nrc_types.h"

/* Driver for routine nrc_selip */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MAXSTR 80
#define NP 100

int main ( void )
{
   char txt[MAXSTR]; 
   unsigned long i, j, k; 
   sReal *a, *b, q; 
   FILE *fp; 

   a = nrc_vector ( 1, NP ); 
   b = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   printf ( "\noriginal array:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   for ( i = 1; i <= NP; i ++ ) b[i]= nrc_selip ( i, 100, a ); 
   printf ( "\nsorted array:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", b[10*i + j] ); 
      printf ( "\n" ); 
   }
   for ( ; ;  ) {
      printf ( "Input k\n" ); 
      if ( scanf ( "%lu", &k ) == EOF ) break; 
      q = nrc_selip ( k, NP, a ); 
      printf ( "Element in nrc_sort position %lu is %6.2f\n", k, q ); 
   }
   nrc_free_vector ( b, 1, NP ); 
   nrc_free_vector ( a, 1, NP ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
