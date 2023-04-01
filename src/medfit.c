
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
int ndatat; 
sReal *xt, *yt, aa, abdevt; 

void nrc_medfit ( sReal x[], sReal y[], int ndata, sReal *a, sReal *b, sReal *abdev )
{
   sReal nrc_rofunc ( sReal b ); 
   int j; 
   sReal bb, b1, b2, del, f, nrc_f1, nrc_f2, sigb, temp; 
   sReal sx = 0.0, sy = 0.0, sxy = 0.0, sxx = 0.0, chisq = 0.0; 

   ndatat = ndata; 
   xt = x; 
   yt = y; 
   for ( j = 1; j <= ndata; j ++ ) {
      sx += x[j]; 
      sy += y[j]; 
      sxy += x[j]*y[j]; 
      sxx += x[j]*x[j]; 
   }
   del = ndata*sxx - sx*sx; 
   aa =( sxx*sy - sx*sxy )/del; 
   bb =( ndata*sxy - sx*sy )/del; 
   for ( j = 1; j <= ndata; j ++ )
      chisq += ( temp = y[j]-( aa + bb*x[j] ), temp*temp ); 
   sigb = sqrt ( chisq/del ); 
   b1 = bb; 
   nrc_f1 = nrc_rofunc ( b1 ); 
   if ( sigb > 0.0 ) {
      b2 = bb + SIGN ( 3.0*sigb, nrc_f1 ); 
      nrc_f2 = nrc_rofunc ( b2 ); 
      if ( b2 == b1 ) {
         *a = aa; 
         *b = bb; 
         *abdev = abdevt/ndata; 
         return; 
      }
      while ( nrc_f1*nrc_f2 > 0.0 ) {
         bb = b2 + 1.6*( b2 - b1 ); 
         b1 = b2; 
         nrc_f1 = nrc_f2; 
         b2 = bb; 
         nrc_f2 = nrc_rofunc ( b2 ); 
      }
      sigb = 0.01*sigb; 
      while ( fabs ( b2 - b1 ) > sigb ) {
         bb = b1 + 0.5*( b2 - b1 ); 
         if ( bb == b1 || bb == b2 ) break; 
         f = nrc_rofunc ( bb ); 
         if ( f*nrc_f1 >= 0.0 ) {
            nrc_f1 = f; 
            b1 = bb; 
         } else {
            nrc_f2 = f; 
            b2 = bb; 
         }
      }
   }
   *a = aa; 
   *b = bb; 
   *abdev = abdevt/ndata; 
}
#undef NRANSI
