
#include "nrc_types.h"

/* Driver for routine nrc_eclass */

#include <stdio.h>
#define NRANSI
#include "nrc.h"
#include "nrc_util.h"

#define M 11
#define N 15

int main ( void )
{
   int i, j, k, lclas = 0, nclass, *nf, *nflag, *nsav; 
   static int lista[]={0, 1, 1, 5, 2, 6, 2, 7, 11, 3, 4, 12}, 
         listb[]={0, 5, 9, 13, 6, 10, 14, 3, 7, 15, 8, 4}; 

   nf = nrc_ivector ( 1, N ); 
   nflag = nrc_ivector ( 1, N ); 
   nsav = nrc_ivector ( 1, N ); 
   nrc_eclass ( nf, N, lista, listb, M ); 
   for ( i = 1; i <= N; i ++ ) nflag[i]= 1; 
   printf ( "\nNumbers from 1 -%d divided according to\n", N ); 
   printf ( "their value modulo 4:\n\n" ); 
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
