
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_mrqcof ( sReal x[], sReal y[], sReal sig[], int ndata, sReal a[], int ia[], 
   int ma, sReal **alpha, sReal nrc_beta[], sReal *chisq, 
   void ( *funcs )( sReal, sReal [], sReal *, sReal [], int ) )
{
   int i, j, k, l, m, mfit = 0; 
   sReal ymod, wt, sig2i, dy, *dyda; 

   dyda = nrc_vector ( 1, ma ); 
   for ( j = 1; j <= ma; j ++ )
      if ( ia[j] ) mfit ++; 
   for ( j = 1; j <= mfit; j ++ ) {
      for ( k = 1; k <= j; k ++ ) alpha[j][k]= 0.0; 
      nrc_beta[j]= 0.0; 
   }
   *chisq = 0.0; 
   for ( i = 1; i <= ndata; i ++ ) {
      ( *funcs )( x[i], a, &ymod, dyda, ma ); 
      sig2i = 1.0/( sig[i]*sig[i] ); 
      dy = y[i]- ymod; 
      for ( j = 0, l = 1; l <= ma; l ++ ) {
         if ( ia[l] ) {
            wt = dyda[l]*sig2i; 
            for ( j ++, k = 0, m = 1; m <= l; m ++ )
               if ( ia[m] ) alpha[j][++ k] += wt*dyda[m]; 
            nrc_beta[j] += dy*wt; 
         }
      }
      *chisq += dy*dy*sig2i; 
   }
   for ( j = 2; j <= mfit; j ++ )
      for ( k = 1; k < j; k ++ ) alpha[k][j]= alpha[j][k]; 
   nrc_free_vector ( dyda, 1, ma ); 
}
#undef NRANSI
