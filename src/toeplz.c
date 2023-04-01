
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define FREERETURN {nrc_free_vector(h,1,n);nrc_free_vector(g,1,n);return;}

void nrc_toeplz ( sReal r[], sReal x[], sReal y[], int n )
{
   int j, k, m, m1, m2; 
   sReal pp, pt1, pt2, qq, qt1, qt2, sd, sgd, sgn, shn, sxn; 
   sReal *g, *h; 

   if ( r[n] == 0.0 ) nrc_error ( "nrc_toeplz - 1 singular principal minor" ); 
   g = nrc_vector ( 1, n ); 
   h = nrc_vector ( 1, n ); 
   x[1]= y[1]/r[n]; 
   if ( n == 1 ) FREERETURN
   g[1]= r[n - 1]/r[n]; 
   h[1]= r[n + 1]/r[n]; 
   for ( m = 1; m <= n; m ++ ) {
      m1 = m + 1; 
      sxn = - y[m1]; 
      sd = - r[n]; 
      for ( j = 1; j <= m; j ++ ) {
         sxn += r[n + m1 - j]*x[j]; 
         sd += r[n + m1 - j]*g[m - j + 1]; 
      }
      if ( sd == 0.0 ) nrc_error ( "nrc_toeplz - 2 singular principal minor" ); 
      x[m1]= sxn/sd; 
      for ( j = 1; j <= m; j ++ ) x[j] -= x[m1]*g[m - j + 1]; 
      if ( m1 == n ) FREERETURN
      sgn = - r[n - m1]; 
      shn = - r[n + m1]; 
      sgd = - r[n]; 
      for ( j = 1; j <= m; j ++ ) {
         sgn += r[n + j - m1]*g[j]; 
         shn += r[n + m1 - j]*h[j]; 
         sgd += r[n + j - m1]*h[m - j + 1]; 
      }
      if ( sgd == 0.0 ) nrc_error ( "nrc_toeplz - 3 singular principal minor" ); 
      g[m1]= sgn/sgd; 
      h[m1]= shn/sd; 
      k = m; 
      m2 =( m + 1 ) >> 1; 
      pp = g[m1]; 
      qq = h[m1]; 
      for ( j = 1; j <= m2; j ++ ) {
         pt1 = g[j]; 
         pt2 = g[k]; 
         qt1 = h[j]; 
         qt2 = h[k]; 
         g[j]= pt1 - pp*qt2; 
         g[k]= pt2 - pp*qt1; 
         h[j]= qt1 - qq*pt2; 
         h[k --]= qt2 - qq*pt1; 
      }
   }
   nrc_error ( "nrc_toeplz - should not arrive here!" ); 
}
#undef FREERETURN
#undef NRANSI
