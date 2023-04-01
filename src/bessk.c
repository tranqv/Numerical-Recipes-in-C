
#include "nrc_types.h"

sReal nrc_bessk ( int n, sReal x )
{
   sReal nrc_bessk0 ( sReal x ); 
   sReal nrc_bessk1 ( sReal x ); 
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal bk, bkm, bkp, tox; 

   if ( n < 2 ) nrc_error ( "Index n less than 2 in nrc_bessk" ); 
   tox = 2.0/x; 
   bkm = nrc_bessk0 ( x ); 
   bk = nrc_bessk1 ( x ); 
   for ( j = 1; j < n; j ++ ) {
      bkp = bkm + j*tox*bk; 
      bkm = bk; 
      bk = bkp; 
   }
   return bk; 
}
