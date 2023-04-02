
#include "nrc_types.h"

/* Driver for routine nrc_rank */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 100
#define MAXSTR 80

int main ( void )
{
   char txt[MAXSTR]; 
   unsigned long i, j, k, l, *indx, *irank; 
   sReal *a, b[11]; 
   FILE *fp; 

   indx = nrc_lvector ( 1, NP ); 
   irank = nrc_lvector ( 1, NP ); 
   a = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   nrc_indexx ( NP, a, indx ); 
   nrc_rank ( NP, indx, irank ); 
   printf ( "original array is:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   printf ( "table of ranks is:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7d", irank[10*i + j] ); 
      printf ( "\n" ); 
   }
   printf ( "press return to continue...\n" ); 
   ( void ) getchar ( ); 
   printf ( "array sorted according to nrc_rank table:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) {
         k = 10*i + j; 
         for ( l = 1; l <= NP; l ++ )
            if ( irank[l] == k ) b[j]= a[l]; 
      }
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", b[j] ); 
      printf ( "\n" ); 
   }
   nrc_free_vector ( a, 1, NP ); 
   nrc_free_lvector ( irank, 1, NP ); 
   nrc_free_lvector ( indx, 1, NP ); 
   return 0; 
}
#undef NRANSI
