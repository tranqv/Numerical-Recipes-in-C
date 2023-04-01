
#include "nrc_types.h"

/* Driver for routine nrc_piksrt */

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
   int i, j; 
   sReal *a; 
   FILE *fp; 

   a = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   printf ( "original array:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   nrc_piksrt ( NP, a ); 
   printf ( "sorted array:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   nrc_free_vector ( a, 1, NP ); 
   return 0; 
}
#undef NRANSI
