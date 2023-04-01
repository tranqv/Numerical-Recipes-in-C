
#include "nrc_types.h"

/* Driver for routine nrc_eclazz */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define N 15

int equiv ( int i, int j )
{
   return ( i % 4 ) == ( j % 4 ); 
}

int main ( void )
{
   int i, j, k, lclas = 0, nclass, *nf, *nflag, *nsav; 

   nf = nrc_ivector ( 1, N ); 
   nflag = nrc_ivector ( 1, N ); 
   nsav = nrc_ivector ( 1, N ); 
   nrc_eclazz ( nf, N, equiv ); 
   for ( i = 1; i <= N; i ++ ) nflag[i]= 1; 
   printf ( "\nNumbers from 1 -%d divided according to\n", N ); 
   printf ( "their value modulo 4:\n" ); 
   for ( i = 1; i <= N; i ++ ) {
      nclass = nf[i]; 
      if ( nflag[nclass] ) {
         nflag[nclass]= 0; 
         lclas ++; 
         k = 0; 
         for ( j = i; j <= N; j ++ )
            if ( nf[j] == nf[i] ) nsav[++ k]= j; 
         printf ( "Class %2d:      ", lclas ); 
         for ( j = 1; j <= k; j ++ ) printf ( "%3d", nsav[j] ); 
         printf ( "\n" ); 
      }
   }
   nrc_free_ivector ( nsav, 1, N ); 
   nrc_free_ivector ( nflag, 1, N ); 
   nrc_free_ivector ( nf, 1, N ); 
   return 0; 
}
#undef NRANSI
