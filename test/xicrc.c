
#include "nrc_types.h"

/* Driver for routine nrc_icrc */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

#define LOBYTE(x) ((unsigned char)((x) & 0xFF))
#define HIBYTE(x) ((unsigned char)((x) >> 8))

int main ( void )
{
   unsigned char lin[256]; 
   unsigned short i1, i2; 
   unsigned long n; 

   for ( ; ; ) {
      printf ( "Enter length and string: \n" ); 
      if ( scanf ( "%lu %s", &n, &lin[1] ) == EOF ) break; 
      lin[n + 1]= 0; 
      printf ( "%s\n", &lin[1] ); 
      i1 = nrc_icrc ( 0, lin, n, ( short ) 0, 1 ); 
      lin[n + 1]= HIBYTE ( i1 ); 
      lin[n + 2]= LOBYTE ( i1 ); 
      i2 = nrc_icrc ( i1, lin, n + 2, ( short ) 0, 1 ); 
      printf ( "    XMODEM: String CRC, Packet CRC =    0x%x 0x%x\n", i1, i2 ); 
      i1 = nrc_icrc ( i2, lin, n, ( short ) 0xff, - 1 ); 
      lin[n + 1] = ~LOBYTE ( i1 ); 
      lin[n + 2] = ~HIBYTE ( i1 ); 
      i2 = nrc_icrc ( i1, lin, n + 2, ( short ) 0xff, - 1 ); 
      printf ( "      X.25: String CRC, Packet CRC =    0x%x 0x%x\n", i1, i2 ); 
      i1 = nrc_icrc ( i2, lin, n, ( short ) 0, - 1 ); 
      lin[n + 1]= LOBYTE ( i1 ); 
      lin[n + 2]= HIBYTE ( i1 ); 
      i2 = nrc_icrc ( i1, lin, n + 2, ( short ) 0, - 1 ); 
      printf ( " CRC - CCITT: String CRC, Packet CRC =    0x%x 0x%x\n", i1, i2 ); 
   }
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
