
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define PI 3.141592653589793238462643383279502884197

void nrc_chebft ( sReal a, sReal b, sReal c[], int n, sReal ( *func )( sReal ) )
{
   int k, j; 
   sReal fac, bpa, bma, *f; 

   f = nrc_vector ( 0, n - 1 ); 
   bma = 0.5*( b - a ); 
   bpa = 0.5*( b + a ); 
   for ( k = 0; k < n; k ++ ) {
      sReal y = cos ( PI*( k + 0.5 )/n ); 
      f[k]=( *func )( y*bma + bpa ); 
   }
   fac = 2.0/n; 
   for ( j = 0; j < n; j ++ ) {
      dReal sum = 0.0; 
      for ( k = 0; k < n; k ++ )
         sum += f[k]*cos ( PI*j*( k + 0.5 )/n ); 
      c[j]= fac*sum; 
   }
   nrc_free_vector ( f, 0, n - 1 ); 
}
#undef PI
#undef NRANSI
