
#include "nrc_types.h"

/* Driver for routine nrc_indexx */

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
   unsigned long i, j, *indx; 
   sReal *a; 
   FILE *fp; 

   indx = nrc_lvector ( 1, NP ); 
   a = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   nrc_indexx ( NP, a, indx ); 
   printf ( "\noriginal array:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   printf ( "\nsorted array:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[indx[10*i + j]] ); 
      printf ( "\n" ); 
   }
   nrc_free_vector ( a, 1, NP ); 
   nrc_free_lvector ( indx, 1, NP ); 
   return 0; 
}
#undef NRANSI
