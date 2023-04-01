
#include "nrc_types.h"

#include <math.h>

sReal nrc_factrl ( int n )
{
   sReal nrc_gammln ( sReal xx ); 
   void nrc_error ( char error_text[] ); 
   static int ntop = 4; 
   static sReal a[33]={1.0, 1.0, 2.0, 6.0, 24.0}; 
   int j; 

   if ( n < 0 ) nrc_error ( "Negative factorial in routine nrc_factrl" ); 
   if ( n > 32 ) return exp ( nrc_gammln ( n + 1.0 ) ); 
   while ( ntop < n ) {
      j = ntop ++; 
      a[ntop]= a[j]*ntop; 
   }
   return a[n]; 
}
