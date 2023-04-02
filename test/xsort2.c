
#include "nrc_types.h"

/* Driver for routine nrc_sort2 */

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
   sReal *a, *b; 
   FILE *fp; 

   a = nrc_vector ( 1, NP ); 
   b = nrc_vector ( 1, NP ); 
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( txt, MAXSTR, fp ); 
   for ( i = 1; i <= NP; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   /* generate b - array */
   for ( i = 1; i <= NP; i ++ ) b[i]= i; 
   /* nrc_sort a and mix b */
   nrc_sort2 ( NP, a, b ); 
   printf ( "\nAfter sorting a and mixing b, array a is:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   printf ( "\n... and array b is:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", b[10*i + j] ); 
      printf ( "\n" ); 
   }
   printf ( "press return to continue...\n" ); 
   ( void ) getchar ( ); 
   /* nrc_sort b and mix a */
   nrc_sort2 ( NP, b, a ); 
   printf ( "\nAfter sorting b and mixing a, array a is:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", a[10*i + j] ); 
      printf ( "\n" ); 
   }
   printf ( "\n... and array b is:\n" ); 
   for ( i = 0; i <= 9; i ++ ) {
      for ( j = 1; j <= 10; j ++ ) printf ( "%7.2f", b[10*i + j] ); 
      printf ( "\n" ); 
   }
   nrc_free_vector ( b, 1, NP ); 
   nrc_free_vector ( a, 1, NP ); 
   return 0; 
}
#undef NRANSI
