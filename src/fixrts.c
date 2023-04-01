
#include "nrc_types.h"

#include <math.h>
#include "nrc_complex.h"
#define NMAX 100
#define ZERO nrc_cmplx(0.0,0.0)
#define ONE nrc_cmplx(1.0,0.0)

void nrc_fixrts ( sReal d[], int m )
{
   void nrc_zroots ( sComp a[], int m, sComp roots[], int polish ); 
   int i, j, polish; 
   sComp a[NMAX], roots[NMAX]; 

   a[m]= ONE; 
   for ( j = m - 1; j >= 0; j -- )
      a[j]= nrc_cmplx ( - d[m - j], 0.0 ); 
   polish = 1; 
   nrc_zroots ( a, m, roots, polish ); 
   for ( j = 1; j <= m; j ++ )
      if ( nrc_cabs ( roots[j] ) > 1.0 )
         roots[j]= nrc_cdiv ( ONE, nrc_conjg ( roots[j] ) ); 
   a[0]= nrc_csub ( ZERO, roots[1] ); 
   a[1]= ONE; 
   for ( j = 2; j <= m; j ++ ) {
      a[j]= ONE; 
      for ( i = j; i >= 2; i -- )
         a[i - 1]= nrc_csub ( a[i - 2], nrc_cmul ( roots[j], a[i - 1] ) ); 
      a[0]= nrc_csub ( ZERO, nrc_cmul ( roots[j], a[0] ) ); 
   }
   for ( j = 0; j <= m - 1; j ++ )
      d[m - j] = - a[j].r; 
}
#undef NMAX
#undef ZERO
#undef ONE
