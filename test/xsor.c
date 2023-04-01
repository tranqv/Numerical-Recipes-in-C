
#include "nrc_types.h"

/* Driver for routine nrc_sor */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NSTEP 4
#define JMAX 33
#define PI 3.1415926

int main ( void )
{
   int i, j, midl; 
   dReal **a, **b, **c, **d, **e, **f, **u, rjac; 

   a = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   b = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   c = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   d = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   e = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   f = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   u = nrc_dmatrix ( 1, JMAX, 1, JMAX ); 
   for ( i = 1; i <= JMAX; i ++ )
      for ( j = 1; j <= JMAX; j ++ ) {
         a[i][j]= b[i][j]= c[i][j]= d[i][j]= 1.0; 
         e[i][j]=( - 4.0 ); 
         f[i][j]= u[i][j]= 0.0; 
      }
   midl = JMAX/2 + 1; 
   f[midl][midl]= 2.0/( ( JMAX - 1 )*( JMAX - 1 ) ); 
   rjac = cos ( PI/JMAX ); 
   nrc_sor ( a, b, c, d, e, f, u, JMAX, rjac ); 
   printf ( "SOR solution:\n" ); 
   for ( i = 1; i <= JMAX; i += NSTEP ) {
      for ( j = 1; j <= JMAX; j += NSTEP ) printf ( "%8.4f", u[i][j] ); 
      printf ( "\n" ); 
   }
   printf ( "\n Test that solution satisfies difference equations:\n" ); 
   for ( i = NSTEP + 1; i < JMAX; i += NSTEP ) {
      for ( j = NSTEP + 1; j < JMAX; j += NSTEP )
         f[i][j]= u[i + 1][j]+ u[i - 1][j]+ u[i][j + 1]+ u[i][j - 1]
            - 4.0*u[i][j]; 
      printf ( "%7s", " " ); 
      for ( j = NSTEP + 1; j < JMAX; j += NSTEP ) printf ( "%8.4f", f[i][j] ); 
      printf ( "\n" ); 
   }
   nrc_free_dmatrix ( u, 1, JMAX, 1, JMAX ); 
   nrc_free_dmatrix ( f, 1, JMAX, 1, JMAX ); 
   nrc_free_dmatrix ( e, 1, JMAX, 1, JMAX ); 
   nrc_free_dmatrix ( d, 1, JMAX, 1, JMAX ); 
   nrc_free_dmatrix ( c, 1, JMAX, 1, JMAX ); 
   nrc_free_dmatrix ( b, 1, JMAX, 1, JMAX ); 
   nrc_free_dmatrix ( a, 1, JMAX, 1, JMAX ); 
   return 0; 
}
#undef NRANSI
