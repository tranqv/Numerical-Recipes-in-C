
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define EPS 1.0e-4

void nrc_fdjac ( int n, sReal x[], sReal fvec[], sReal **df, 
   void ( *vecfunc )( int, sReal [], sReal [] ) )
{
   int i, j; 
   sReal h, temp, *f; 

   f = nrc_vector ( 1, n ); 
   for ( j = 1; j <= n; j ++ ) {
      temp = x[j]; 
      h = EPS*fabs ( temp ); 
      if ( h == 0.0 ) h = EPS; 
      x[j]= temp + h; 
      h = x[j]- temp; 
      ( *vecfunc )( n, x, f ); 
      x[j]= temp; 
      for ( i = 1; i <= n; i ++ ) df[i][j]=( f[i]- fvec[i] )/h; 
   }
   nrc_free_vector ( f, 1, n ); 
}
#undef EPS
#undef NRANSI
