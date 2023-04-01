
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define TINY 1.0e-30

void nrc_cntab1 ( int **nn, int ni, int nj, sReal *chisq, sReal *df, sReal *prob, 
   sReal *cramrv, sReal *ccc )
{
   sReal nrc_gammq ( sReal a, sReal x ); 
   int nnj, nni, j, i, minij; 
   sReal sum = 0.0, expctd, *sumi, *sumj, temp; 

   sumi = nrc_vector ( 1, ni ); 
   sumj = nrc_vector ( 1, nj ); 
   nni = ni; 
   nnj = nj; 
   for ( i = 1; i <= ni; i ++ ) {
      sumi[i]= 0.0; 
      for ( j = 1; j <= nj; j ++ ) {
         sumi[i] += nn[i][j]; 
         sum += nn[i][j]; 
      }
      if ( sumi[i] == 0.0 ) -- nni; 
   }
   for ( j = 1; j <= nj; j ++ ) {
      sumj[j]= 0.0; 
      for ( i = 1; i <= ni; i ++ ) sumj[j] += nn[i][j]; 
      if ( sumj[j] == 0.0 ) -- nnj; 
   }
   *df = nni*nnj - nni - nnj + 1; 
   *chisq = 0.0; 
   for ( i = 1; i <= ni; i ++ ) {
      for ( j = 1; j <= nj; j ++ ) {
         expctd = sumj[j]*sumi[i]/sum; 
         temp = nn[i][j]- expctd; 
         *chisq += temp*temp/( expctd + TINY ); 
      }
   }
   *prob = nrc_gammq ( 0.5*( *df ), 0.5*( *chisq ) ); 
   minij = nni < nnj ? nni - 1 : nnj - 1; 
   *cramrv = sqrt ( *chisq/( sum*minij ) ); 
   *ccc = sqrt ( *chisq/( *chisq + sum ) ); 
   nrc_free_vector ( sumj, 1, nj ); 
   nrc_free_vector ( sumi, 1, ni ); 
}
#undef TINY
#undef NRANSI
