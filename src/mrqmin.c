
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_mrqmin ( sReal x[], sReal y[], sReal sig[], int ndata, sReal a[], int ia[], 
   int ma, sReal **covar, sReal **alpha, sReal *chisq, 
   void ( *funcs )( sReal, sReal [], sReal *, sReal [], int ), sReal *alamda )
{
   void nrc_covsrt ( sReal **covar, int ma, int ia[], int mfit ); 
   void nrc_gaussj ( sReal **a, int n, sReal **b, int m ); 
   void nrc_mrqcof ( sReal x[], sReal y[], sReal sig[], int ndata, sReal a[], 
      int ia[], int ma, sReal **alpha, sReal nrc_beta[], sReal *chisq, 
      void ( *funcs )( sReal, sReal [], sReal *, sReal [], int ) ); 
   int j, k, l; 
   static int mfit; 
   static sReal ochisq, *atry, *nrc_beta, *da, **oneda; 

   if ( *alamda < 0.0 ) {
      atry = nrc_vector ( 1, ma ); 
      nrc_beta = nrc_vector ( 1, ma ); 
      da = nrc_vector ( 1, ma ); 
      for ( mfit = 0, j = 1; j <= ma; j ++ )
         if ( ia[j] ) mfit ++; 
      oneda = nrc_matrix ( 1, mfit, 1, 1 ); 
      *alamda = 0.001; 
      nrc_mrqcof ( x, y, sig, ndata, a, ia, ma, alpha, nrc_beta, chisq, funcs ); 
      ochisq =( *chisq ); 
      for ( j = 1; j <= ma; j ++ ) atry[j]= a[j]; 
   }
   for ( j = 1; j <= mfit; j ++ ) {
      for ( k = 1; k <= mfit; k ++ ) covar[j][k]= alpha[j][k]; 
      covar[j][j]= alpha[j][j]*( 1.0 +( *alamda ) ); 
      oneda[j][1]= nrc_beta[j]; 
   }
   nrc_gaussj ( covar, mfit, oneda, 1 ); 
   for ( j = 1; j <= mfit; j ++ ) da[j]= oneda[j][1]; 
   if ( *alamda == 0.0 ) {
      nrc_covsrt ( covar, ma, ia, mfit ); 
      nrc_covsrt ( alpha, ma, ia, mfit ); 
      nrc_free_matrix ( oneda, 1, mfit, 1, 1 ); 
      nrc_free_vector ( da, 1, ma ); 
      nrc_free_vector ( nrc_beta, 1, ma ); 
      nrc_free_vector ( atry, 1, ma ); 
      return; 
   }
   for ( j = 0, l = 1; l <= ma; l ++ )
      if ( ia[l] ) atry[l]= a[l]+ da[++ j]; 
   nrc_mrqcof ( x, y, sig, ndata, atry, ia, ma, covar, da, chisq, funcs ); 
   if ( *chisq < ochisq ) {
      *alamda *= 0.1; 
      ochisq =( *chisq ); 
      for ( j = 1; j <= mfit; j ++ ) {
         for ( k = 1; k <= mfit; k ++ ) alpha[j][k]= covar[j][k]; 
         nrc_beta[j]= da[j]; 
      }
      for ( l = 1; l <= ma; l ++ ) a[l]= atry[l]; 
   } else {
      *alamda *= 10.0; 
      *chisq = ochisq; 
   }
}
#undef NRANSI
