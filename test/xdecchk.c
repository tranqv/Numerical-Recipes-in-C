
#include "nrc_types.h"

/* Driver for routine nrc_decchk */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define MAXLINE 128

int main ( void )
{
   int j, k, l, n, nbad = 0, ntot = 0; 
   int iok, jok; 
   char lin[MAXLINE+2], ch, chh; 

   /* test all jump transpositions of the form 86jlk41 */
   lin[0]='8'; 
   lin[1]='6'; 
   lin[5]='4'; 
   lin[6]='1'; 
   for ( j = 48; j <= 57; j ++ ) {
      for ( k = 48; k <= 57; k ++ ) {
         for ( l = 48; l <= 57; l ++ ) {
            lin[3]= l; 
            if ( j != k ) {
               ntot ++; 
               lin[2]= j; 
               lin[4]= k; 
               iok = nrc_decchk ( lin, 7, &ch ); 
               lin[7]= ch; 
               iok = nrc_decchk ( lin, 8, &chh ); 
               lin[2]= k; 
               lin[4]= j; 
               jok = nrc_decchk ( lin, 8, &chh ); 
               if ( !iok || jok ) nbad ++; 
            }
         }
      }
   }
   printf ( "%s %14s %3d\n", "Total tries:", " ", ntot ); 
   printf ( "%s %16s %3d\n", "Bad tries:", " ", nbad ); 
   printf ( "%s %11s %4.2f\n", "Fraction good:", " ", ( ( sReal )( ntot - nbad ) )/ntot ); 
   for ( ; ;  ) {
      printf ( "enter string terminated by x:\n" ); 
      if ( gets ( lin ) == NULL ) break; 
      for ( j = 0; j < MAXLINE; j ++ )
         if ( lin[j] == 'x' ) break; 
      n = j; 
      if ( !n ) break; 
      iok = nrc_decchk ( lin, n, &ch ); 
      lin[n]= ch; 
      jok = nrc_decchk ( lin, n + 1, &chh ); 
      lin[n + 1]= 0; 
      printf ( "%s checks as %c\n", lin, jok ? 'T' : 'F' ); 
   }
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
