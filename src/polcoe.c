
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_polcoe ( sReal x[], sReal y[], int n, sReal cof[] )
{
   int k, j, i; 
   sReal phi, ff, b, *s; 

   s = nrc_vector ( 0, n ); 
   for ( i = 0; i <= n; i ++ ) s[i]= cof[i]= 0.0; 
   s[n] = - x[0]; 
   for ( i = 1; i <= n; i ++ ) {
      for ( j = n - i; j <= n - 1; j ++ )
         s[j] -= x[i]*s[j + 1]; 
      s[n] -= x[i]; 
   }
   for ( j = 0; j <= n; j ++ ) {
      phi = n + 1; 
      for ( k = n; k >= 1; k -- )
         phi = k*s[k]+ x[j]*phi; 
      ff = y[j]/phi; 
      b = 1.0; 
      for ( k = n; k >= 0; k -- ) {
         cof[k] += b*ff; 
         b = s[k]+ x[j]*b; 
      }
   }
   nrc_free_vector ( s, 0, n ); 
}
#undef NRANSI
