
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_gaucof ( int n, sReal a[], sReal b[], sReal amu0, sReal x[], sReal w[] )
{
   void nrc_eigsrt ( sReal d[], sReal **v, int n ); 
   void nrc_tqli ( sReal d[], sReal e[], int n, sReal **z ); 
   int i, j; 
   sReal **z; 

   z = nrc_matrix ( 1, n, 1, n ); 
   for ( i = 1; i <= n; i ++ ) {
      if ( i != 1 ) b[i]= sqrt ( b[i] ); 
      for ( j = 1; j <= n; j ++ ) z[i][j]=( sReal )( i == j ); 
   }
   nrc_tqli ( a, b, n, z ); 
   nrc_eigsrt ( a, z, n ); 
   for ( i = 1; i <= n; i ++ ) {
      x[i]= a[i]; 
      w[i]= amu0*z[1][i]*z[1][i]; 
   }
   nrc_free_matrix ( z, 1, n, 1, n ); 
}
#undef NRANSI
