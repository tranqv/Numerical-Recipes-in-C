
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_polcof ( sReal xa[], sReal ya[], int n, sReal cof[] )
{
   void nrc_polint ( sReal xa[], sReal ya[], int n, sReal x, sReal *y, sReal *dy ); 
   int k, j, i; 
   sReal xmin, dy, *x, *y; 

   x = nrc_vector ( 0, n ); 
   y = nrc_vector ( 0, n ); 
   for ( j = 0; j <= n; j ++ ) {
      x[j]= xa[j]; 
      y[j]= ya[j]; 
   }
   for ( j = 0; j <= n; j ++ ) {
      nrc_polint ( x - 1, y - 1, n + 1 - j, 0.0, &cof[j], &dy ); 
      xmin = 1.0e38; 
      k = - 1; 
      for ( i = 0; i <= n - j; i ++ ) {
         if ( fabs ( x[i] ) < xmin ) {
            xmin = fabs ( x[i] ); 
            k = i; 
         }
         if ( x[i] ) y[i]=( y[i]- cof[j] )/x[i]; 
      }
      for ( i = k + 1; i <= n - j; i ++ ) {
         y[i - 1]= y[i]; 
         x[i - 1]= x[i]; 
      }
   }
   nrc_free_vector ( y, 0, n ); 
   nrc_free_vector ( x, 0, n ); 
}
#undef NRANSI
