
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define TINY 1.0e-20

void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d )
{
   int i, imax, j, k; 
   sReal big, dum, sum, temp; 
   sReal *vv; 

   vv = nrc_vector ( 1, n ); 
   *d = 1.0; 
   for ( i = 1; i <= n; i ++ ) {
      big = 0.0; 
      for ( j = 1; j <= n; j ++ )
         if ( ( temp = fabs ( a[i][j] ) ) > big ) big = temp; 
      if ( big == 0.0 ) nrc_error ( "Singular nrc_matrix in routine nrc_ludcmp" ); 
      vv[i]= 1.0/big; 
   }
   for ( j = 1; j <= n; j ++ ) {
      for ( i = 1; i < j; i ++ ) {
         sum = a[i][j]; 
         for ( k = 1; k < i; k ++ ) sum -= a[i][k]*a[k][j]; 
         a[i][j]= sum; 
      }
      big = 0.0; 
      for ( i = j; i <= n; i ++ ) {
         sum = a[i][j]; 
         for ( k = 1; k < j; k ++ )
            sum -= a[i][k]*a[k][j]; 
         a[i][j]= sum; 
         if ( ( dum = vv[i]*fabs ( sum ) ) >= big ) {
            big = dum; 
            imax = i; 
         }
      }
      if ( j != imax ) {
         for ( k = 1; k <= n; k ++ ) {
            dum = a[imax][k]; 
            a[imax][k]= a[j][k]; 
            a[j][k]= dum; 
         }
         *d = -( *d ); 
         vv[imax]= vv[j]; 
      }
      indx[j]= imax; 
      if ( a[j][j] == 0.0 ) a[j][j]= TINY; 
      if ( j != n ) {
         dum = 1.0/( a[j][j] ); 
         for ( i = j + 1; i <= n; i ++ ) a[i][j] *= dum; 
      }
   }
   nrc_free_vector ( vv, 1, n ); 
}
#undef TINY
#undef NRANSI
