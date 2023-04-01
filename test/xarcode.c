
#include "nrc_types.h"

/* Driver for routines nrc_arcmak and nrc_arcode */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define MC 512

#define NWK 20

#define MAXLINE 256

int main ( void )
{
   int k; 
   unsigned long i, j, lc, lcode = MAXLINE, n, nch, nrad, nt, nfreq[257], tmp, zero = 0; 
   unsigned char *code, mess[MAXLINE], ness[MAXLINE]; 
   arithcode acode; 
   FILE *fp; 

   code = nrc_cvector ( 0, MAXLINE ); 
   acode.ilob = nrc_lvector ( 1, NWK ); 
   acode.iupb = nrc_lvector ( 1, NWK ); 
   acode.ncumfq = nrc_lvector ( 1, MC + 2 ); 
   if ( ( fp = fopen ( "text.dat", "r" ) ) == NULL )
      nrc_error ( "Input file text.dat not found.\n" ); 
   for ( j = 1; j <= 256; j ++ ) nfreq[j]= 0; 
   while ( ( k = getc ( fp ) ) != EOF ) {
      if ( ( k -= 31 ) >= 1 ) nfreq[k]++; 
   }
   fclose ( fp ); 
   nch = 96; 
   nrad = 256; 
   /* here is the initialization that constructs the code */
   nrc_arcmak ( nfreq, ( int ) nch, ( int ) nrad, &acode ); 
   /* now ready to prompt for lines to encode */
   for ( ; ;  ) {
      printf ( "Enter a line:\n" ); 
      if ( gets ( ( char * )&mess[1] ) == NULL ) break; 
      n = strlen ( ( char * )&mess[1] ); 
      /* shift from 256 character alphabet to 96 printing characters */
      for ( j = 1; j <= n; j ++ ) mess[j] -= 32; 
      /* message initialization */
      lc = 1; 
      nrc_arcode ( &zero, &code, &lcode, &lc, 0, &acode ); 
      /* here we arithmetically encode mess ( 1:n ) */
      for ( j = 1; j <= n; j ++ ) {
         tmp = mess[j]; 
         nrc_arcode ( &tmp, &code, &lcode, &lc, 1, &acode ); 
      }
      /* message termination */
      nrc_arcode ( &nch, &code, &lcode, &lc, 1, &acode ); 
      printf ( "Length of line input,  coded = %lu %lu\n", n, lc - 1 ); 
      /* here we decode the message,  hopefully to get the original back */
      lc = 1; 
      nrc_arcode ( &zero, &code, &lcode, &lc, 0, &acode ); 
      for ( j = 1; j <= lcode; j ++ ) {
         nrc_arcode ( &i, &code, &lcode, &lc, - 1, &acode ); 
         if ( i == nch ) break; 
         else ness[j]=( unsigned char ) i; 
      }
      if ( j > lcode ) nrc_error ( "Arith. coding: Never get here" ); 
      nt = j - 1; 
      printf ( "Decoded output:\n" ); 
      for ( j = 1; j <= nt; j ++ ) printf ( "%c", ( char )( ness[j]+ 32 ) ); 
      printf ( "\n" ); 
      if ( nt != n ) printf ( "Error ! j decoded != n input.\n" ); 
   }
   nrc_free_cvector ( code, 0, MAXLINE ); 
   nrc_free_lvector ( acode.ncumfq, 1, MC + 2 ); 
   nrc_free_lvector ( acode.iupb, 1, NWK ); 
   nrc_free_lvector ( acode.ilob, 1, NWK ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
