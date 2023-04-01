
#include "nrc_types.h"

#include <math.h>
#include "nrc_complex.h"
#define MAXM 100
#define EPS    1.0e-14

void nrc_zroots ( sComp a[], int m, sComp roots[], int polish )
{
   void nrc_laguer ( sComp a[], int m, sComp *x, int *its ); 
   int i, its, j, jj; 
   sComp x, b, c, ad[MAXM]; 

   for ( j = 0; j <= m; j ++ ) ad[j]= a[j]; 
   for ( j = m; j >= 1; j -- ) {
      x = nrc_cmplx ( 0.0, 0.0 ); 
      nrc_laguer ( ad, j, &x, &its ); 
      if ( fabs ( x.i ) <= 2.0*EPS*fabs ( x.r ) ) x.i = 0.0; 
      roots[j]= x; 
      b = ad[j]; 
      for ( jj = j - 1; jj >= 0; jj -- ) {
         c = ad[jj]; 
         ad[jj]= b; 
         b = nrc_cadd ( nrc_cmul ( x, b ), c ); 
      }
   }
   if ( polish )
      for ( j = 1; j <= m; j ++ )
         nrc_laguer ( a, m, &roots[j], &its ); 
   for ( j = 2; j <= m; j ++ ) {
      x = roots[j]; 
      for ( i = j - 1; i >= 1; i -- ) {
         if ( roots[i].r <= x.r ) break; 
         roots[i + 1]= roots[i]; 
      }
      roots[i + 1]= x; 
   }
}
#undef EPS
#undef MAXM
