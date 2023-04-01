
#include "nrc_types.h"

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

sReal nrc_select ( unsigned long k, unsigned long n, sReal arr[] )
{
   unsigned long i, ir, j, l, mid; 
   sReal a, temp; 

   l = 1; 
   ir = n; 
   for ( ; ; ) {
      if ( ir <= l + 1 ) {
         if ( ir == l + 1 && arr[ir] < arr[l] ) {
            SWAP ( arr[l], arr[ir] )
         }
         return arr[k]; 
      } else {
         mid =( l + ir ) >> 1; 
         SWAP ( arr[mid], arr[l + 1] )
         if ( arr[l] > arr[ir] ) {
            SWAP ( arr[l], arr[ir] )
         }
         if ( arr[l + 1] > arr[ir] ) {
            SWAP ( arr[l + 1], arr[ir] )
         }
         if ( arr[l] > arr[l + 1] ) {
            SWAP ( arr[l], arr[l + 1] )
         }
         i = l + 1; 
         j = ir; 
         a = arr[l + 1]; 
         for ( ; ; ) {
            do i ++; while ( arr[i] < a ); 
            do j --; while ( arr[j] > a ); 
            if ( j < i ) break; 
            SWAP ( arr[i], arr[j] )
         }
         arr[l + 1]= arr[j]; 
         arr[j]= a; 
         if ( j >= k ) ir = j - 1; 
         if ( j <= k ) l = i; 
      }
   }
}
#undef SWAP
