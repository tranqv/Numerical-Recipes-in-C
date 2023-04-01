
#include "nrc_types.h"

#include <stdio.h>
#define NRANSI
#include "nrc_util.h"
#define IAOFF 48

void nrc_mppi ( int n )
{
   void nrc_mp2dfr ( unsigned char a[], unsigned char s[], int n, int *m ); 
   void nrc_mpadd ( unsigned char w[], unsigned char u[], unsigned char v[], int n ); 
   void nrc_mpinv ( unsigned char u[], unsigned char v[], int n, int m ); 
   void nrc_mplsh ( unsigned char u[], int n ); 
   void nrc_mpmov ( unsigned char u[], unsigned char v[], int n ); 
   void nrc_mpmul ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
      int m ); 
   void nrc_mpsdv ( unsigned char w[], unsigned char u[], int n, int iv, int *ir ); 
   void nrc_mpsqrt ( unsigned char w[], unsigned char u[], unsigned char v[], int n, 
      int m ); 
   int ir, j, m; 
   unsigned char mm, *x, *y, *sx, *sxi, *t, *s, *pi; 

   x = nrc_cvector ( 1, n + 1 ); 
   y = nrc_cvector ( 1, n << 1 ); 
   sx = nrc_cvector ( 1, n ); 
   sxi = nrc_cvector ( 1, n ); 
   t = nrc_cvector ( 1, n << 1 ); 
   s = nrc_cvector ( 1, 3*n ); 
   pi = nrc_cvector ( 1, n + 1 ); 
   t[1]= 2; 
   for ( j = 2; j <= n; j ++ ) t[j]= 0; 
   nrc_mpsqrt ( x, x, t, n, n ); 
   nrc_mpadd ( pi, t, x, n ); 
   nrc_mplsh ( pi, n ); 
   nrc_mpsqrt ( sx, sxi, x, n, n ); 
   nrc_mpmov ( y, sx, n ); 
   for ( ; ; ) {
      nrc_mpadd ( x, sx, sxi, n ); 
      nrc_mpsdv ( x, &x[1], n, 2, &ir ); 
      nrc_mpsqrt ( sx, sxi, x, n, n ); 
      nrc_mpmul ( t, y, sx, n, n ); 
      nrc_mpadd ( &t[1], &t[1], sxi, n ); 
      x[1]++; 
      y[1]++; 
      nrc_mpinv ( s, y, n, n ); 
      nrc_mpmul ( y, &t[2], s, n, n ); 
      nrc_mplsh ( y, n ); 
      nrc_mpmul ( t, x, s, n, n ); 
      mm = t[2]- 1; 
      for ( j = 3; j <= n; j ++ ) {
         if ( t[j] != mm ) break; 
      }
      m = t[n + 1]- mm; 
      if ( j <= n || m > 1 || m < - 1 ) {
            nrc_mpmul ( s, pi, &t[1], n, n ); 
            nrc_mpmov ( pi, &s[1], n ); 
            continue; 
      }
      printf ( "pi =\n" ); 
      s[1]= pi[1]+ IAOFF; 
      s[2]='.'; 
      m = mm; 
      nrc_mp2dfr ( &pi[1], &s[2], n - 1, &m ); 
      s[m + 3]= 0; 
      printf ( " %64s\n", &s[1] ); 
      nrc_free_cvector ( pi, 1, n + 1 ); 
      nrc_free_cvector ( s, 1, 3*n ); 
      nrc_free_cvector ( t, 1, n << 1 ); 
      nrc_free_cvector ( sxi, 1, n ); 
      nrc_free_cvector ( sx, 1, n ); 
      nrc_free_cvector ( y, 1, n << 1 ); 
      nrc_free_cvector ( x, 1, n + 1 ); 
      return; 
   }
}
#undef IAOFF
#undef NRANSI
