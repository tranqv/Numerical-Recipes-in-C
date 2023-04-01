
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"

void nrc_simpr ( sReal y[], sReal dydx[], sReal dfdx[], sReal **dfdy, int n, 
   sReal xs, sReal htot, int nstep, sReal yout[], 
   void ( *nrc_derivs )( sReal, sReal [], sReal [] ) )
{
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d ); 
   int i, j, nn, *indx; 
   sReal d, h, x, **a, *del, *ytemp; 

   indx = nrc_ivector ( 1, n ); 
   a = nrc_matrix ( 1, n, 1, n ); 
   del = nrc_vector ( 1, n ); 
   ytemp = nrc_vector ( 1, n ); 
   h = htot/nstep; 
   for ( i = 1; i <= n; i ++ ) {
      for ( j = 1; j <= n; j ++ ) a[i][j] = - h*dfdy[i][j]; 
      ++ a[i][i]; 
   }
   nrc_ludcmp ( a, n, indx, &d ); 
   for ( i = 1; i <= n; i ++ )
      yout[i]= h*( dydx[i]+ h*dfdx[i] ); 
   nrc_lubksb ( a, n, indx, yout ); 
   for ( i = 1; i <= n; i ++ )
      ytemp[i]= y[i]+( del[i]= yout[i] ); 
   x = xs + h; 
   ( *nrc_derivs )( x, ytemp, yout ); 
   for ( nn = 2; nn <= nstep; nn ++ ) {
      for ( i = 1; i <= n; i ++ )
         yout[i]= h*yout[i]- del[i]; 
      nrc_lubksb ( a, n, indx, yout ); 
      for ( i = 1; i <= n; i ++ )
         ytemp[i] += ( del[i] += 2.0*yout[i] ); 
      x += h; 
      ( *nrc_derivs )( x, ytemp, yout ); 
   }
   for ( i = 1; i <= n; i ++ )
      yout[i]= h*yout[i]- del[i]; 
   nrc_lubksb ( a, n, indx, yout ); 
   for ( i = 1; i <= n; i ++ )
      yout[i] += ytemp[i]; 
   nrc_free_vector ( ytemp, 1, n ); 
   nrc_free_vector ( del, 1, n ); 
   nrc_free_matrix ( a, 1, n, 1, n ); 
   nrc_free_ivector ( indx, 1, n ); 
}
#undef NRANSI
