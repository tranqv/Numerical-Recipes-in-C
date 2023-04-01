
#include "nrc_types.h"

void nrc_piksrt ( int n, sReal arr[] )
{
   int i, j; 
   sReal a; 

   for ( j = 2; j <= n; j ++ ) {
      a = arr[j]; 
      i = j - 1; 
      while ( i > 0 && arr[i] > a ) {
         arr[i + 1]= arr[i]; 
         i --; 
      }
      arr[i + 1]= a; 
   }
}
