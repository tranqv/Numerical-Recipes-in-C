
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define POTN 1.571000
#define BIG    1.0e30
#define PI 3.141592653589793238462643383279502884197
#define ACC 1.0e-3

int nn; 
sReal *xx, *yy, *sx, *sy, *ww, aa, offs; 

void nrc_fitexy ( sReal x[], sReal y[], int ndat, sReal sigx[], sReal sigy[], 
   sReal *a, sReal *b, sReal *siga, sReal *sigb, sReal *chi2, sReal *q )
{
   void nrc_avevar ( sReal data[], unsigned long n, sReal *ave, sReal *var ); 
   sReal nrc_brent ( sReal ax, sReal bx, sReal cx, 
      sReal ( *f )( sReal ), sReal tol, sReal *xmin ); 
   sReal nrc_chixy ( sReal bang ); 
   void nrc_fit ( sReal x[], sReal y[], int ndata, sReal sig[], int mwt, 
      sReal *a, sReal *b, sReal *siga, sReal *sigb, sReal *chi2, sReal *q ); 
   sReal nrc_gammq ( sReal a, sReal x ); 
   void nrc_mnbrak ( sReal *ax, sReal *bx, sReal *cx, sReal *fa, sReal *fb, 
      sReal *fc, sReal ( *func )( sReal ) ); 
   sReal nrc_zbrent ( sReal ( *func )( sReal ), sReal x1, sReal x2, sReal tol ); 
   int j; 
   sReal swap, amx, amn, varx, vary, ang[7], ch[7], scale, bmn, bmx, d1, d2, r2, 
      dum1, dum2, dum3, dum4, dum5; 

   xx = nrc_vector ( 1, ndat ); 
   yy = nrc_vector ( 1, ndat ); 
   sx = nrc_vector ( 1, ndat ); 
   sy = nrc_vector ( 1, ndat ); 
   ww = nrc_vector ( 1, ndat ); 
   nrc_avevar ( x, ndat, &dum1, &varx ); 
   nrc_avevar ( y, ndat, &dum1, &vary ); 
   scale = sqrt ( varx/vary ); 
   nn = ndat; 
   for ( j = 1; j <= ndat; j ++ ) {
      xx[j]= x[j]; 
      yy[j]= y[j]*scale; 
      sx[j]= sigx[j]; 
      sy[j]= sigy[j]*scale; 
      ww[j]= sqrt ( SQR ( sx[j] )+ SQR ( sy[j] ) ); 
   }
   nrc_fit ( xx, yy, nn, ww, 1, &dum1, b, &dum2, &dum3, &dum4, &dum5 ); 
   offs = ang[1]= 0.0; 
   ang[2]= atan ( *b ); 
   ang[4]= 0.0; 
   ang[5]= ang[2]; 
   ang[6]= POTN; 
   for ( j = 4; j <= 6; j ++ ) ch[j]= nrc_chixy ( ang[j] ); 
   nrc_mnbrak ( &ang[1], &ang[2], &ang[3], &ch[1], &ch[2], &ch[3], nrc_chixy ); 
   *chi2 = nrc_brent ( ang[1], ang[2], ang[3], nrc_chixy, ACC, b ); 
   *chi2 = nrc_chixy ( *b ); 
   *a = aa; 
   *q = nrc_gammq ( 0.5*( nn - 2 ), *chi2*0.5 ); 
   for ( r2 = 0.0, j = 1; j <= nn; j ++ ) r2 += ww[j]; 
   r2 = 1.0/r2; 
   bmx = BIG; 
   bmn = BIG; 
   offs =( *chi2 )+ 1.0; 
   for ( j = 1; j <= 6; j ++ ) {
      if ( ch[j] > offs ) {
         d1 = fabs ( ang[j]-( *b ) ); 
         while ( d1 >= PI ) d1 -= PI; 
         d2 = PI - d1; 
         if ( ang[j] < *b ) {
            swap = d1; 
            d1 = d2; 
            d2 = swap; 
         }
         if ( d1 < bmx ) bmx = d1; 
         if ( d2 < bmn ) bmn = d2; 
      }
   }
   if ( bmx < BIG ) {
      bmx = nrc_zbrent ( nrc_chixy, *b, *b + bmx, ACC )-( *b ); 
      amx = aa -( *a ); 
      bmn = nrc_zbrent ( nrc_chixy, *b, *b - bmn, ACC )-( *b ); 
      amn = aa -( *a ); 
      *sigb = sqrt ( 0.5*( bmx*bmx + bmn*bmn ) )/( scale*SQR ( cos ( *b ) ) ); 
      *siga = sqrt ( 0.5*( amx*amx + amn*amn )+ r2 )/scale; 
   } else ( *sigb )=( *siga )= BIG; 
   *a /= scale; 
   *b = tan ( *b )/scale; 
   nrc_free_vector ( ww, 1, ndat ); 
   nrc_free_vector ( sy, 1, ndat ); 
   nrc_free_vector ( sx, 1, ndat ); 
   nrc_free_vector ( yy, 1, ndat ); 
   nrc_free_vector ( xx, 1, ndat ); 
}
#undef POTN
#undef BIG
#undef PI
#undef ACC
#undef NRANSI
