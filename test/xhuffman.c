
#include "nrc_types.h"

/* Driver for routines nrc_hufmak, nrc_hufenc, nrc_hufdec */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MC 512
#define MQ (2*MC-1)

#define MAXLINE 256

int main ( void )
{
   int k; 
   unsigned long i, j, ilong, n, nb, nh, nlong, nt, lcode = MAXLINE, nch, nfreq[257]; 
   unsigned char *code, mess[MAXLINE], ness[MAXLINE]; 
   huffcode hcode; 
   FILE *fp; 

   code = nrc_cvector ( 0, MAXLINE ); 
   hcode.icod = nrc_lvector ( 1, MQ ); 
   hcode.ncod = nrc_lvector ( 1, MQ ); 
   hcode.left = nrc_lvector ( 1, MQ ); 
   hcode.right = nrc_lvector ( 1, MQ ); 
   for ( j = 1; j <= MQ; j ++ ) hcode.icod[j]= hcode.ncod[j]= 0; 
   /* construct a letter frequency table from the file text.dat */
   if ( ( fp = fopen ( "text.dat", "r" ) ) == NULL )
      nrc_error ( "Input file text.dat not found.\n" ); 
   for ( j = 1; j <= 256; j ++ ) nfreq[j]= 0; 
   while ( ( k = getc ( fp ) ) != EOF ) {
      if ( ( k -= 31 ) >= 1 ) nfreq[k]++; 
   }
   fclose ( fp ); 
   nch = 96; 
   /* here is the initialization that constructs the code */
   nrc_hufmak ( nfreq, nch, &ilong, &nlong, &hcode ); 
   printf ( "ind char nfreq ncod icod\n" ); 
   for ( j = 1; j <= nch; j ++ )
      if ( nfreq[j] ) printf ( "%3lu %c %6lu %6lu %6lu\n", 
         j, ( char )( j + 31 ), nfreq[j], hcode.ncod[j], hcode.icod[j] ); 
   for ( ; ; ) {
      /* now ready to prompt for lines to encode */
      printf ( "Enter a line:\n" ); 
      if ( gets ( ( char * )&mess[1] ) == NULL ) break; 
      n = strlen ( ( char * )&mess[1] ); 
      /* shift from 256 character alphabet to 96 printing characters */
      for ( j = 1; j <= n; j ++ ) mess[j] -= 32; 
      /* here we Huffman encode mess[1..n] */
      nb = 0; 
      for ( j = 1; j <= n; j ++ ) nrc_hufenc ( ( unsigned long ) mess[j], &code, &lcode, &nb, &hcode ); 
      nh =( nb >> 3 )+ 1; 
      /* message termination ( encode a single long character ) */
      nrc_hufenc ( ilong, &code, &lcode, &nb, &hcode ); 
      /* here we decode the message, hopefully to get the original back */
      nb = 0; 
      for ( j = 1; j <= MAXLINE; j ++ ) {
         nrc_hufdec ( &i, code, nh, &nb, &hcode ); 
         if ( i == nch ) break; 
         else ness[j]=( unsigned char ) i; 
      }
      if ( j > lcode ) nrc_error ( "Huffman coding: Never get here" ); 
      nt = j - 1; 
      printf ( "Length of line input, coded = %lu %lu\n", n, nh ); 
      printf ( "Decoded output:\n" ); 
      for ( j = 1; j <= nt; j ++ ) printf ( "%c", ( char )( ness[j]+ 32 ) ); 
      printf ( "\n" ); 
      if ( nt != n ) printf ( "Error! :  n decoded != n input\n" ); 
      if ( nt - n == 1 ) printf ( "May be harmless spurious character.\n" ); 
   }
   nrc_free_cvector ( code, 0, MAXLINE ); 
   nrc_free_lvector ( hcode.right, 1, MQ ); 
   nrc_free_lvector ( hcode.left, 1, MQ ); 
   nrc_free_lvector ( hcode.ncod, 1, MQ ); 
   nrc_free_lvector ( hcode.icod, 1, MQ ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
