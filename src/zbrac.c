
#include "nrc_types.h"

#include <math.h>
#define FACTOR 1.6
#define NTRY 50

int nrc_zbrac ( sReal ( *func )( sReal ), sReal *x1, sReal *x2 )
{
   void nrc_error ( char error_text[] ); 
   int j; 
   sReal nrc_f1, nrc_f2; 

   if ( *x1 == *x2 ) nrc_error ( "Bad initial range in nrc_zbrac" ); 
   nrc_f1 =( *func )( *x1 ); 
   nrc_f2 =( *func )( *x2 ); 
   for ( j = 1; j <= NTRY; j ++ ) {
      if ( nrc_f1*nrc_f2 < 0.0 ) return 1; 
      if ( fabs ( nrc_f1 ) < fabs ( nrc_f2 ) )
         nrc_f1 =( *func )( *x1 += FACTOR*( *x1 -*x2 ) ); 
      else
         nrc_f2 =( *func )( *x2 += FACTOR*( *x2 -*x1 ) ); 
   }
   return 0; 
}
#undef FACTOR
#undef NTRY
