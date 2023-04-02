
#include "nrc_types.h"

/* Driver for routine nrc_select */

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
   sReal *a, *b, q, s; 
   FILE *fp; 

   a = nrc_vector ( 1, NP ); 
   b = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   for ( ; ; ) {
      printf ( "Input k\n" ); 
      if ( scanf ( "%lu", &k ) == EOF ) break; 
      for ( i = 1; i <= NP; i ++ ) b[i]= a[i]; 
      s = nrc_selip ( k, NP, a ); 
      q = nrc_select ( k, NP, b ); 
      printf ( "Element in nrc_sort position %lu is %6.2f\n", k, q ); 
      printf ( "Cross - check from SELIP routine %6.2f\n", s ); 
   }
   nrc_free_vector ( b, 1, NP ); 
   nrc_free_vector ( a, 1, NP ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
