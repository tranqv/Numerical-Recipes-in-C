
#include "nrc_types.h"

#define EPS    1.0e-14

void nrc_simp2 ( sReal **a, int m, int n, int *ip, int kp )
{
   int k, i; 
   sReal qp, q0, q, q1; 

   *ip = 0; 
   for ( i = 1; i <= m; i ++ )
      if ( a[i + 1][kp + 1] < - EPS ) break; 
   if ( i > m ) return; 
   q1 = - a[i + 1][1]/a[i + 1][kp + 1]; 
   *ip = i; 
   for ( i =*ip + 1; i <= m; i ++ ) {
      if ( a[i + 1][kp + 1] < - EPS ) {
         q = - a[i + 1][1]/a[i + 1][kp + 1]; 
         if ( q < q1 ) {
            *ip = i; 
            q1 = q; 
         } else if ( q == q1 ) {
            for ( k = 1; k <= n; k ++ ) {
               qp = - a[*ip + 1][k + 1]/a[*ip + 1][kp + 1]; 
               q0 = - a[i + 1][k + 1]/a[i + 1][kp + 1]; 
               if ( q0 != qp ) break; 
            }
            if ( q0 < qp ) *ip = i; 
         }
      }
   }
}
#undef EPS
