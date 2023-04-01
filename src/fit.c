
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void nrc_fit ( sReal x[], sReal y[], int ndata, sReal sig[], int mwt, sReal *a, 
   sReal *b, sReal *siga, sReal *sigb, sReal *chi2, sReal *q )
{
   sReal nrc_gammq ( sReal a, sReal x ); 
   int i; 
   sReal wt, t, sxoss, sx = 0.0, sy = 0.0, st2 = 0.0, ss, sigdat; 

   *b = 0.0; 
   if ( mwt ) {
      ss = 0.0; 
      for ( i = 1; i <= ndata; i ++ ) {
         wt = 1.0/SQR ( sig[i] ); 
         ss += wt; 
         sx += x[i]*wt; 
         sy += y[i]*wt; 
      }
   } else {
      for ( i = 1; i <= ndata; i ++ ) {
         sx += x[i]; 
         sy += y[i]; 
      }
      ss = ndata; 
   }
   sxoss = sx/ss; 
   if ( mwt ) {
      for ( i = 1; i <= ndata; i ++ ) {
         t =( x[i]- sxoss )/sig[i]; 
         st2 += t*t; 
         *b += t*y[i]/sig[i]; 
      }
   } else {
      for ( i = 1; i <= ndata; i ++ ) {
         t = x[i]- sxoss; 
         st2 += t*t; 
         *b += t*y[i]; 
      }
   }
   *b /= st2; 
   *a =( sy - sx*( *b ) )/ss; 
   *siga = sqrt ( ( 1.0 + sx*sx/( ss*st2 ) )/ss ); 
   *sigb = sqrt ( 1.0/st2 ); 
   *chi2 = 0.0; 
   *q = 1.0; 
   if ( mwt == 0 ) {
      for ( i = 1; i <= ndata; i ++ )
         *chi2 += SQR ( y[i]-( *a )-( *b )*x[i] ); 
      sigdat = sqrt ( ( *chi2 )/( ndata - 2 ) ); 
      *siga *= sigdat; 
      *sigb *= sigdat; 
   } else {
      for ( i = 1; i <= ndata; i ++ )
         *chi2 += SQR ( ( y[i]-( *a )-( *b )*x[i] )/sig[i] ); 
      if ( ndata > 2 ) *q = nrc_gammq ( 0.5*( ndata - 2 ), 0.5*( *chi2 ) ); 
   }
}
#undef NRANSI
