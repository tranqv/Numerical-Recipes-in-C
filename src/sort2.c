
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;
#define M 7
#define NSTACK 50

void nrc_sort2 ( unsigned long n, sReal arr[], sReal brr[] )
{
   unsigned long i, ir = n, j, k, l = 1, *istack; 
   int jstack = 0; 
   sReal a, b, temp; 

   istack = nrc_lvector ( 1, NSTACK ); 
   for ( ; ; ) {
      if ( ir - l < M ) {
         for ( j = l + 1; j <= ir; j ++ ) {
            a = arr[j]; 
            b = brr[j]; 
            for ( i = j - 1; i >= l; i -- ) {
               if ( arr[i] <= a ) break; 
               arr[i + 1]= arr[i]; 
               brr[i + 1]= brr[i]; 
            }
            arr[i + 1]= a; 
            brr[i + 1]= b; 
         }
         if ( !jstack ) {
            nrc_free_lvector ( istack, 1, NSTACK ); 
            return; 
         }
         ir = istack[jstack]; 
         l = istack[jstack - 1]; 
         jstack -= 2; 
      } else {
         k =( l + ir ) >> 1; 
         SWAP ( arr[k], arr[l + 1] )
         SWAP ( brr[k], brr[l + 1] )
         if ( arr[l] > arr[ir] ) {
            SWAP ( arr[l], arr[ir] )
            SWAP ( brr[l], brr[ir] )
         }
         if ( arr[l + 1] > arr[ir] ) {
            SWAP ( arr[l + 1], arr[ir] )
            SWAP ( brr[l + 1], brr[ir] )
         }
         if ( arr[l] > arr[l + 1] ) {
            SWAP ( arr[l], arr[l + 1] )
            SWAP ( brr[l], brr[l + 1] )
         }
         i = l + 1; 
         j = ir; 
         a = arr[l + 1]; 
         b = brr[l + 1]; 
         for ( ; ; ) {
            do i ++; while ( arr[i] < a ); 
            do j --; while ( arr[j] > a ); 
            if ( j < i ) break; 
            SWAP ( arr[i], arr[j] )
            SWAP ( brr[i], brr[j] )
         }
         arr[l + 1]= arr[j]; 
         arr[j]= a; 
         brr[l + 1]= brr[j]; 
         brr[j]= b; 
         jstack += 2; 
         if ( jstack > NSTACK ) nrc_error ( "NSTACK too small in nrc_sort2." ); 
         if ( ir - i + 1 >= j - l ) {
            istack[jstack]= ir; 
            istack[jstack - 1]= i; 
            ir = j - 1; 
         } else {
            istack[jstack]= j - 1; 
            istack[jstack - 1]= l; 
            l = i; 
         }
      }
   }
}
#undef M
#undef NSTACK
#undef SWAP
#undef NRANSI
