
#include "nrc_types.h"

/* Driver for routine nrc_kendl2 */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NDAT 1000
#define IP 8
#define JP 8

int main ( void )
{
   int ifunc, i = IP, j = JP, k, l, m, n, twoton; 
   unsigned long iseed; 
   sReal prob, tau, z, **tab; 
   static char *txt[8]=
      {"000", "001", "010", "011", "100", "101", "110", "111"}; 

   /* Look for 'ones - after - zeros' in IRBIT1 and IRBIT2 sequences */
   tab = nrc_matrix ( 1, IP, 1, JP ); 
   printf ( "Are ones followed by zeros and vice - versa?\n" ); 
   for ( ifunc = 1; ifunc <= 2; ifunc ++ ) {
      iseed = 2468; 
      if ( ifunc == 1 )
         printf ( "test of nrc_irbit1:\n" ); 
      else
         printf ( "test of nrc_irbit2:\n" ); 
      for ( k = 1; k <= i; k ++ )
         for ( l = 1; l <= j; l ++ ) tab[k][l]= 0.0; 
      for ( m = 1; m <= NDAT; m ++ ) {
         k = 1; 
         twoton = 1; 
         for ( n = 0; n <= 2; n ++ ) {
            if ( ifunc == 1 )
               k += ( nrc_irbit1 ( &iseed )*twoton ); 
            else
               k += ( nrc_irbit2 ( &iseed )*twoton ); 
            twoton *= 2; 
         }
         l = 1; 
         twoton = 1; 
         for ( n = 0; n <= 2; n ++ ) {
            if ( ifunc == 1 )
               l += ( nrc_irbit1 ( &iseed )*twoton ); 
            else
               l += ( nrc_irbit2 ( &iseed )*twoton ); 
            twoton *= 2; 
         }
         ++ tab[k][l]; 
      }
      nrc_kendl2 ( tab, i, j, &tau, &z, &prob ); 
      printf ( "    " ); 
      for ( n = 0; n <= 7; n ++ ) printf ( "%6s", txt[n] ); 
      printf ( "\n" ); 
      for ( n = 1; n <= 8; n ++ ) {
         printf ( "%3s", txt[n - 1] ); 
         for ( m = 1; m <= 8; m ++ )
            printf ( "%6d", ( int ) ( 0.5 + tab[n][m] ) ); 
         printf ( "\n" ); 
      }
      printf ( "\n%17s %14s %16s\n", 
         "kendall tau", "std. dev.", "probability" ); 
      printf ( "%15.6f %15.6f %15.6f\n\n", tau, z, prob ); 
   }
   nrc_free_matrix ( tab, 1, IP, 1, JP ); 
   return 0; 
}
#undef NRANSI
