
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define PI 3.141592653589793238462643383279502884197

dReal x; 

void nrc_quadmx ( sReal **a, int n )
{
   void nrc_kermom ( dReal w[], dReal y, int m ); 
   void nrc_wwghts ( sReal wghts[], int n, sReal h, 
      void ( *nrc_kermom )( dReal [], dReal , int ) ); 
   int j, k; 
   sReal h, *wt, xx, cx; 

   wt = nrc_vector ( 1, n ); 
   h = PI/( n - 1 ); 
   for ( j = 1; j <= n; j ++ ) {
      x = xx =( j - 1 )*h; 
      nrc_wwghts ( wt, n, h, nrc_kermom ); 
      cx = cos ( xx ); 
      for ( k = 1; k <= n; k ++ ) a[j][k]= wt[k]*cx*cos ( ( k - 1 )*h ); 
      ++ a[j][j]; 
   }
   nrc_free_vector ( wt, 1, n ); 
}
#undef PI
#undef NRANSI
