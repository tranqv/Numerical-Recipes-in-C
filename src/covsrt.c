
#include "nrc_types.h"

#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}

void nrc_covsrt ( sReal **covar, int ma, int ia[], int mfit )
{
   int i, j, k; 
   sReal swap; 

   for ( i = mfit + 1; i <= ma; i ++ )
      for ( j = 1; j <= i; j ++ ) covar[i][j]= covar[j][i]= 0.0; 
   k = mfit; 
   for ( j = ma; j >= 1; j -- ) {
      if ( ia[j] ) {
         for ( i = 1; i <= ma; i ++ ) SWAP ( covar[i][k], covar[i][j] )
         for ( i = 1; i <= ma; i ++ ) SWAP ( covar[k][i], covar[j][i] )
         k --; 
      }
   }
}
#undef SWAP
