
#include "nrc_types.h"

/* Driver for routine nrc_amebsa */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define NP 4
#define MP 5
#define FTOL 1.0E-6
#define N 4
#define RAD 0.3
#define AUG 2.0

long idum =( - 64 ); 

sReal tfunk ( sReal p[] )
{
   int j; 
   sReal q, r, sumd = 0.0, sumr = 0.0; 
   static sReal wid[N + 1]={0.0, 1.0, 3.0, 10.0, 30.0}; 

   for ( j = 1; j <= N; j ++ ) {
      q = p[j]*wid[j]; 
      r =( sReal )( q >= 0 ? ( int )( q + 0.5 ) : -( int )( 0.5 - q ) ); 
      sumr += q*q; 
      sumd += ( q - r )*( q - r ); 
   }
   return 1 + sumr*( 1 +( sumd > RAD*RAD ? AUG : AUG*sumd/( RAD*RAD ) ) ); 
}

int main ( void )
{
   int i, iiter, iter, j, jiter, ndim = NP, nit; 
   sReal temptr, yb, ybb; 
   sReal **p, *x, *y, *pb; 
   static sReal xoff[NP + 1]={0.0, 10.0, 10.0, 10.0, 10.0}; 

   p = nrc_matrix ( 1, MP, 1, NP ); 
   x = nrc_vector ( 1, NP ); 
   y = nrc_vector ( 1, MP ); 
   pb = nrc_vector ( 1, NP ); 
   for ( i = 1; i <= MP; i ++ )
      for ( j = 1; j <= NP; j ++ ) p[i][j]= 0.0; 
   for ( ; ; ) {
      for ( j = 2; j <= MP; j ++ ) p[j][j - 1]= 1.0; 
      for ( i = 1; i <= MP; i ++ ) {
         for ( j = 1; j <= NP; j ++ ) x[j]=( p[i][j] += xoff[j] ); 
         y[i]= tfunk ( x ); 
      }
      yb = 1.0e30; 
      printf ( "Input t, iiter:\n" ); 
      if ( scanf ( "%lf %d", &temptr, &iiter ) == EOF ) break; 

      printf ( "t = %lf, iiter = %d\n", temptr, iiter ); 

      if ( temptr <= 0.0 ) return 1; 

      ybb = 1.0e30; 
      nit = 0; 
      for ( jiter = 1; jiter <= 100; jiter ++ ) {
         iter = iiter; 
         temptr *= 0.8; 
         nrc_amebsa ( p, y, ndim, pb, &yb, FTOL, tfunk, &iter, temptr ); 
         nit += iiter - iter; 
         if ( yb < ybb ) {
            ybb = yb; 
            printf ( "%6d %10.3e ", nit, temptr ); 
            for ( j = 1; j <= NP; j ++ ) printf ( "%10.5f ", pb[j] ); 
            printf ( "%15.7e\n", yb ); 
         }
         if ( iter > 0 ) break; 
      }
      printf ( "Vertices of final 3 - D simplex and\n" ); 
      printf ( "sReal values at the vertices:\n" ); 
      printf ( "%3s %10s %12s %12s %14s\n\n", 
         "i", "x[i]", "y[i]", "z[i]", "function" ); 
      for ( i = 1; i <= MP; i ++ ) {
         printf ( "%3d ", i ); 
         for ( j = 1; j <= NP; j ++ ) printf ( "%12.6f ", p[i][j] ); 
         printf ( "%15.7e\n", y[i] ); 
      }
      printf ( "%3d ", 99 ); 
      for ( j = 1; j <= NP; j ++ ) printf ( "%12.6f ", pb[j] ); 
      printf ( "%15.7e\n", yb ); 
   }
   nrc_free_vector ( pb, 1, NP ); 
   nrc_free_vector ( y, 1, MP ); 
   nrc_free_vector ( x, 1, NP ); 
   nrc_free_matrix ( p, 1, MP, 1, NP ); 
   printf ( "Normal completion\n" ); 
   return 0; 
}
#undef NRANSI
