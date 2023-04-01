
#include "nrc_types.h"

/* Driver for routine nrc_psdes */

#include <stdio.h>
#define NRANSI
#include "nrc.h"

int main ( void )
{
   static unsigned long lword[5]={0, 1, 1, 99, 99}; 
   static unsigned long irword[5]={0, 1, 99, 1, 99}; 
   static char *ans[5]={
      "", 
      "0x604d1dce 0x509c0c23", 
      "0xd97f8571 0xa66cb41a", 
      "0x7822309d 0x64300984", 
      "0xd7f376f0 0x59ba89eb"}; 
   int i; 

   for ( i = 1; i <= 4; i ++ ) {
      nrc_psdes ( &lword[i], &irword[i] ); 
      printf ( "PSDES now calculates:       0x%x 0x%x\n", lword[i], irword[i] ); 
      printf ( "Known correct answers are:  %s\n", ans[i] ); 
   }
   return 0; 
}
#undef NRANSI
