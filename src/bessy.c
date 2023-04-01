
#include "nrc_types.h"

sReal nrc_bessy ( int n, sReal x )
{
   sReal nrc_bessy0 ( sReal x ); 
   sReal nrc_bessy1 ( sReal x ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal by, bym, byp, tox; 

   if ( n < 2 ) nrc_error ( "Index n less than 2 in nrc_bessy" ); 
   tox = 2.0/x; 
   by = nrc_bessy1 ( x ); 
   bym = nrc_bessy0 ( x ); 
   for ( j = 1; j < n; j ++ ) {
      byp = j*tox*by - bym; 
      bym = by; 
      by = byp; 
   }
   return by; 
}
