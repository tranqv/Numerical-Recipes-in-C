
#include "nrc_types.h"

/* Driver for routine nrc_mnewt */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

void usrfun ( sReal *x, int n, sReal *fvec, sReal **fjac )
{
   int i; 

   fjac[1][1] = - 2.0*x[1]; 
   fjac[1][2] = - 2.0*x[2]; 
   fjac[1][3] = - 2.0*x[3]; 
   fjac[1][4]= 1.0; 
   for ( i = 1; i <= n; i ++ ) fjac[2][i]= 2.0*x[i]; 
   fjac[3][1]= 1.0; 
   fjac[3][2] = - 1.0; 
   fjac[3][3]= 0.0; 
   fjac[3][4]= 0.0; 
   fjac[4][1]= 0.0; 
   fjac[4][2]= 1.0; 
   fjac[4][3] = - 1.0; 
   fjac[4][4]= 0.0; 
   fvec[1] = - SQR ( x[1] )- SQR ( x[2] )- SQR ( x[3] )+ x[4]; 
   fvec[2]= SQR ( x[1] )+ SQR ( x[2] )+ SQR ( x[3] )+ SQR ( x[4] )- 1.0; 
   fvec[3]= x[1]- x[2]; 
   fvec[4]= x[2]- x[3]; 
}

#define NTRIAL 5
#define TOLX 1.0e-6
#define N 4
#define TOLF 1.0e-6

int main ( void )
{
   int i, j, k, kk; 
   sReal xx, *x, *fvec, **fjac; 

   fjac = nrc_matrix ( 1, N, 1, N ); 
   fvec = nrc_vector ( 1, N ); 
   x = nrc_vector ( 1, N ); 
   for ( kk = 1; kk <= 2; kk ++ ) {
      for ( k = 1; k <= 3; k ++ ) {
         xx = 0.2001*k*( 2*kk - 3 ); 
         printf ( "Starting nrc_vector number %2d\n", k ); 
         for ( i = 1; i <= 4; i ++ ) {
            x[i]= xx + 0.2*i; 
            printf ( "%7s%1d%s %5.2f\n", 
               "x[", i, "] = ", x[i] ); 
         }
         printf ( "\n" ); 
         for ( j = 1; j <= NTRIAL; j ++ ) {
            nrc_mnewt ( 1, x, N, TOLX, TOLF ); 
            usrfun ( x, N, fvec, fjac ); 
            printf ( "%5s %13s %13s\n", "i", "x[i]", "f" ); 
            for ( i = 1; i <= N; i ++ )
               printf ( "%5d %14.6f %15.6f\n", 
                  i, x[i], fvec[i] ); 
            printf ( "\npress RETURN to continue...\n" ); 
            ( void ) getchar (  ); 
         }
      }
   }
   nrc_free_vector ( x, 1, N ); 
   nrc_free_vector ( fvec, 1, N ); 
   nrc_free_matrix ( fjac, 1, N, 1, N ); 
   return 0; 
}
#undef NRANSI
