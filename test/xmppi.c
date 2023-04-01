
#include "nrc_types.h"

/* Driver for mp routines */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define IAOFF 48
#define NMAX 1024

void mpsqr2 ( int n )
{
   int j, m; 
   unsigned char *x, *y, *t, *q, *r, *s; 

   x = nrc_cvector ( 1, NMAX ); 
   y = nrc_cvector ( 1, NMAX ); 
   t = nrc_cvector ( 1, NMAX ); 
   q = nrc_cvector ( 1, NMAX ); 
   r = nrc_cvector ( 1, NMAX ); 
   s = nrc_cvector ( 1, 3*NMAX ); 
   t[1]= 2; 
   for ( j = 2; j <= n; j ++ ) t[j]= 0; 
   nrc_mpsqrt ( x, x, t, n, n ); 
   nrc_mpmov ( y, x, n ); 
   printf ( "sqrt ( 2 )=\n" ); 
   s[1]= y[1]+ IAOFF; 
   s[2]='.'; 
   /* caution: next step is N**2! omit it for large N */
   nrc_mp2dfr ( &y[1], &s[2], n - 1, &m ); 
   s[m + 3]= 0; 
   printf ( " %64s\n", &s[1] ); 
   printf ( "Result rounded to 1 less base-256 place:\n" ); 
   /* use s as scratch space */
   nrc_mpsad ( s, x, n, 128 ); 
   nrc_mpmov ( y, &s[1], n - 1 ); 
   s[1]= y[1]+ IAOFF; 
   s[2]='.'; 
   /* caution: next step is N**2! omit it for large N */
   nrc_mp2dfr ( &y[1], &s[2], n - 2, &m ); 
   s[m + 3]= 0; 
   printf ( " %64s\n", &s[1] ); 
   printf ( "2 - sqrt ( 2 )=\n" ); 
   /* Calculate this the hard way to exercise the nrc_mpdiv function */
   nrc_mpdiv ( q, r, t, x, n, n ); 
   s[1]= r[1]+ IAOFF; 
   s[2]='.'; 
   /* caution: next step is N**2! omit it for large N */
   nrc_mp2dfr ( &r[1], &s[2], n - 1, &m ); 
   s[m + 3]= 0; 
   printf ( " %64s\n", &s[1] ); 
   nrc_free_cvector ( s, 1, 3*NMAX ); 
   nrc_free_cvector ( r, 1, NMAX ); 
   nrc_free_cvector ( q, 1, NMAX ); 
   nrc_free_cvector ( t, 1, NMAX ); 
   nrc_free_cvector ( y, 1, NMAX ); 
   nrc_free_cvector ( x, 1, NMAX ); 
}

int main ( void )
{
   int n; 

   for ( ; ;  ) {
      printf ( "Input n\n" ); 
      if ( scanf ( "%d", &n ) == EOF ) break; 
      mpsqr2 ( n ); 
      nrc_mppi ( n ); 
   }
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
