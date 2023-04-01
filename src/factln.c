
#include "nrc_types.h"

sReal nrc_factln ( int n )
{
   sReal nrc_gammln ( sReal xx ); 
   void nrc_error ( char error_text[] ); 
   static sReal a[101]; 

   if ( n < 0 ) nrc_error ( "Negative factorial in routine nrc_factln" ); 
   if ( n <= 1 ) return 0.0; 
   if ( n <= 100 ) return a[n] ? a[n] : ( a[n]= nrc_gammln ( n + 1.0 ) ); 
   else return nrc_gammln ( n + 1.0 ); 
}
