
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_lfit ( sReal x[], sReal y[], sReal sig[], int ndat, sReal a[], int ia[], 
   int ma, sReal **covar, sReal *chisq, void ( *funcs )( sReal, sReal [], int ) )
{
   void nrc_covsrt ( sReal **covar, int ma, int ia[], int mfit ); 
   void nrc_gaussj ( sReal **a, int n, sReal **b, int m ); 
   int i, j, k, l, m, mfit = 0; 
   sReal ym, wt, sum, sig2i, **nrc_beta, *afunc; 

   nrc_beta = nrc_matrix ( 1, ma, 1, 1 ); 
   afunc = nrc_vector ( 1, ma ); 
   for ( j = 1; j <= ma; j ++ )
      if ( ia[j] ) mfit ++; 
   if ( mfit == 0 ) nrc_error ( "nrc_lfit: no parameters to be fitted" ); 
   for ( j = 1; j <= mfit; j ++ ) {
      for ( k = 1; k <= mfit; k ++ ) covar[j][k]= 0.0; 
      nrc_beta[j][1]= 0.0; 
   }
   for ( i = 1; i <= ndat; i ++ ) {
      ( *funcs )( x[i], afunc, ma ); 
      ym = y[i]; 
      if ( mfit < ma ) {
         for ( j = 1; j <= ma; j ++ )
            if ( !ia[j] ) ym -= a[j]*afunc[j]; 
      }
      sig2i = 1.0/SQR ( sig[i] ); 
      for ( j = 0, l = 1; l <= ma; l ++ ) {
         if ( ia[l] ) {
            wt = afunc[l]*sig2i; 
            for ( j ++, k = 0, m = 1; m <= l; m ++ )
               if ( ia[m] ) covar[j][++ k] += wt*afunc[m]; 
            nrc_beta[j][1] += ym*wt; 
         }
      }
   }
   for ( j = 2; j <= mfit; j ++ )
      for ( k = 1; k < j; k ++ )
         covar[k][j]= covar[j][k]; 
   nrc_gaussj ( covar, mfit, nrc_beta, 1 ); 
   for ( j = 0, l = 1; l <= ma; l ++ )
      if ( ia[l] ) a[l]= nrc_beta[++ j][1]; 
   *chisq = 0.0; 
   for ( i = 1; i <= ndat; i ++ ) {
      ( *funcs )( x[i], afunc, ma ); 
      for ( sum = 0.0, j = 1; j <= ma; j ++ ) sum += a[j]*afunc[j]; 
      *chisq += SQR ( ( y[i]- sum )/sig[i] ); 
   }
   nrc_covsrt ( covar, ma, ia, mfit ); 
   nrc_free_vector ( afunc, 1, ma ); 
   nrc_free_matrix ( nrc_beta, 1, ma, 1, 1 ); 
}
#undef NRANSI
