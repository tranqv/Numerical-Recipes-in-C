
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define EPS     NR_CONST_EPSI

extern int ndatat; 
extern sReal *xt, *yt, aa, abdevt; 

sReal nrc_rofunc ( sReal b )
{
   sReal nrc_select ( unsigned long k, unsigned long n, sReal arr[] ); 
   int j; 
   sReal *arr, d, sum = 0.0; 

   arr = nrc_vector ( 1, ndatat ); 
   for ( j = 1; j <= ndatat; j ++ ) arr[j]= yt[j]- b*xt[j]; 
   if ( ndatat & 1 ) {
      aa = nrc_select ( ( ndatat + 1 )>> 1, ndatat, arr ); 
   }
   else {
      j = ndatat >> 1; 
      aa = 0.5*( nrc_select ( j, ndatat, arr )+ nrc_select ( j + 1, ndatat, arr ) ); 
   }
   abdevt = 0.0; 
   for ( j = 1; j <= ndatat; j ++ ) {
      d = yt[j]-( b*xt[j]+ aa ); 
      abdevt += fabs ( d ); 
      if ( yt[j] != 0.0 ) d /= fabs ( yt[j] ); 
      if ( fabs ( d ) > EPS ) sum += ( d >= 0.0 ? xt[j] : - xt[j] ); 
   }
   nrc_free_vector ( arr, 1, ndatat ); 
   return sum; 
}
#undef EPS
#undef NRANSI
