
#include "nrc_types.h"

/* Driver for routine nrc_hpsel */

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
   unsigned long i, k; 
   sReal *a, *heap, check; 
   FILE *fp; 

   a = nrc_vector ( 1, NP ); 
   heap = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   for ( ; ; ) {
      printf ( "Input k\n" ); 
      if ( scanf ( "%lu", &k ) == EOF ) break; 

      if ( k < 0 ) return 1 ; 

      nrc_hpsel ( k, NP, a, heap ); 
      check = nrc_select ( NP + 1 - k, NP, a ); 
      printf ( "heap[1], check = %6.2f %6.2f\n", heap[1], check ); 
      printf ( "heap of numbers of size %lu\n", k ); 
      for ( i = 1; i <= k; i ++ ) printf ( "%lu %6.2f\n", i, heap[i] ); 
   }
   nrc_free_vector ( heap, 1, NP ); 
   nrc_free_vector ( a, 1, NP ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
