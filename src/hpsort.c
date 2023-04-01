
#include "nrc_types.h"

void nrc_hpsort ( unsigned long n, sReal ra[] )
{
   unsigned long i, ir, j, l; 
   sReal rra; 

   if ( n < 2 ) return; 
   l =( n >> 1 )+ 1; 
   ir = n; 
   for ( ; ; ) {
      if ( l > 1 ) {
         rra = ra[-- l]; 
      } else {
         rra = ra[ir]; 
         ra[ir]= ra[1]; 
         if ( -- ir == 1 ) {
            ra[1]= rra; 
            break; 
         }
      }
      i = l; 
      j = l + l; 
      while ( j <= ir ) {
         if ( j < ir && ra[j] < ra[j + 1] ) j ++; 
         if ( rra < ra[j] ) {
            ra[i]= ra[j]; 
            i = j; 
            j <<= 1; 
         } else break; 
      }
      ra[i]= rra; 
   }
}
