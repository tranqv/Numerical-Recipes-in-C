
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define TOL 1.0e-5

void nrc_svdfit ( sReal x[], sReal y[], sReal sig[], int ndata, sReal a[], int ma, 
   sReal **u, sReal **v, sReal w[], sReal *chisq, 
   void ( *funcs )( sReal, sReal [], int ) )
{
   void nrc_svbksb ( sReal **u, sReal w[], sReal **v, int m, int n, sReal b[], 
      sReal x[] ); 
   void nrc_svdcmp ( sReal **a, int m, int n, sReal w[], sReal **v ); 
   int j, i; 
   sReal wmax, tmp, thresh, sum, *b, *afunc; 

   b = nrc_vector ( 1, ndata ); 
   afunc = nrc_vector ( 1, ma ); 
   for ( i = 1; i <= ndata; i ++ ) {
      ( *funcs )( x[i], afunc, ma ); 
      tmp = 1.0/sig[i]; 
      for ( j = 1; j <= ma; j ++ ) u[i][j]= afunc[j]*tmp; 
      b[i]= y[i]*tmp; 
   }
   nrc_svdcmp ( u, ndata, ma, w, v ); 
   wmax = 0.0; 
   for ( j = 1; j <= ma; j ++ )
      if ( w[j] > wmax ) wmax = w[j]; 
   thresh = TOL*wmax; 
   for ( j = 1; j <= ma; j ++ )
      if ( w[j] < thresh ) w[j]= 0.0; 
   nrc_svbksb ( u, w, v, ndata, ma, b, a ); 
   *chisq = 0.0; 
   for ( i = 1; i <= ndata; i ++ ) {
      ( *funcs )( x[i], afunc, ma ); 
      for ( sum = 0.0, j = 1; j <= ma; j ++ ) sum += a[j]*afunc[j]; 
      *chisq += ( tmp =( y[i]- sum )/sig[i], tmp*tmp ); 
   }
   nrc_free_vector ( afunc, 1, ma ); 
   nrc_free_vector ( b, 1, ndata ); 
}
#undef TOL
#undef NRANSI
