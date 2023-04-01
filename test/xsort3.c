
#include "nrc_types.h"

/* Driver for routine nrc_sort3 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NLEN 64

int main ( void )
{
   int i, j; 
   char dummy[NLEN], amsg[NLEN + 1], bmsg[NLEN + 1], cmsg[NLEN + 1]; 
   sReal *a, *b, *c; 
   FILE *fp; 

   a = nrc_vector ( 1, NLEN ); 
   b = nrc_vector ( 1, NLEN ); 
   c = nrc_vector ( 1, NLEN ); 
   ( void ) strcpy ( amsg, "I'd rather have a bottle in front of" ); 
   ( void ) strcat ( amsg, " me than a frontal lobotomy." ); 
   printf ( "\noriginal message:\n%s\n", amsg ); 
   /* read array of random numbers */
   if ( ( fp = fopen ( "tarray.dat", "r" ) ) == NULL )
      nrc_error ( "Data file tarray.dat not found\n" ); 
   fgets ( dummy, NLEN, fp ); 
   for ( i = 1; i <= NLEN; i ++ ) fscanf ( fp, "%lf", &a[i] ); 
   fclose ( fp ); 
   /* create array b and array c */
   for ( i = 1; i <= NLEN; i ++ ) {
      b[i]= i; 
      c[i]= NLEN + 1 - i; 
   }
   /* nrc_sort array a while mixing b and c */
   nrc_sort3 ( NLEN, a, b, c ); 
   /* scramble message according to array b */
   bmsg[NLEN]= amsg[NLEN];   /* null terminating character */
   for ( i = 1; i <= NLEN; i ++ ) {
      j = b[i]; 
      bmsg[i - 1]= amsg[j - 1]; 
   }
   printf ( "\nscrambled message:\n%s\n", bmsg ); 
   /* unscramble according to array c */
   cmsg[NLEN]= amsg[NLEN]; 
   for ( i = 1; i <= NLEN; i ++ ) {
      j = c[i]; 
      cmsg[j - 1]= bmsg[i - 1]; 
   }
   printf ( "\nmirrored message:\n%s\n", cmsg ); 
   nrc_free_vector ( c, 1, NLEN ); 
   nrc_free_vector ( b, 1, NLEN ); 
   nrc_free_vector ( a, 1, NLEN ); 
   return 0; 
}
#undef NRANSI
