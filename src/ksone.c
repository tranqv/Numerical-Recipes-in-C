
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_ksone ( sReal data[], unsigned long n, sReal ( *func )( sReal ), sReal *d, 
   sReal *prob )
{
   sReal nrc_probks ( sReal alam ); 
   void nrc_sort ( unsigned long n, sReal arr[] ); 
   unsigned long j; 
   sReal dt, en, ff, fn, fo = 0.0; 

   nrc_sort ( n, data ); 
   en = n; 
   *d = 0.0; 
   for ( j = 1; j <= n; j ++ ) {
      fn = j/en; 
      ff =( *func )( data[j] ); 
      dt = FMAX ( fabs ( fo - ff ), fabs ( fn - ff ) ); 
      if ( dt > *d ) *d = dt; 
      fo = fn; 
   }
   en = sqrt ( en ); 
   *prob = nrc_probks ( ( en + 0.12 + 0.11/en )*( *d ) ); 
}
#undef NRANSI
