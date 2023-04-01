
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define MAXSTP 10000
#define TINY 1.0e-30

extern int kmax, kount; 
extern sReal *xp, **yp, dxsav; 

void nrc_odeint ( sReal ystart[], int nvar, sReal x1, sReal x2, sReal eps, sReal h1, 
   sReal hmin, int *nok, int *nbad, 
   void ( *nrc_derivs )( sReal, sReal [], sReal [] ), 
   void ( *nrc_rkqs )( sReal [], sReal [], int, sReal *, sReal, sReal, sReal [], 
   sReal *, sReal *, void ( * )( sReal, sReal [], sReal [] ) ) )
{
   int nstp, i; 
   sReal xsav, x, hnext, hdid, h; 
   sReal *yscal, *y, *dydx; 

   yscal = nrc_vector ( 1, nvar ); 
   y = nrc_vector ( 1, nvar ); 
   dydx = nrc_vector ( 1, nvar ); 
   x = x1; 
   h = SIGN ( h1, x2 - x1 ); 
   *nok = ( *nbad ) = kount = 0; 
   for ( i = 1; i <= nvar; i ++ ) y[i]= ystart[i]; 
   if ( kmax > 0 ) xsav = x - dxsav*2.0; 
   for ( nstp = 1; nstp <= MAXSTP; nstp ++ ) {
      ( *nrc_derivs )( x, y, dydx ); 
      for ( i = 1; i <= nvar; i ++ )
         yscal[i]= fabs ( y[i] )+ fabs ( dydx[i]*h )+ TINY; 
      if ( kmax > 0 && kount < kmax - 1 && fabs ( x - xsav ) > fabs ( dxsav ) ) {
         xp[++ kount]= x; 
         for ( i = 1; i <= nvar; i ++ ) yp[i][kount]= y[i]; 
         xsav = x; 
      }
      if ( ( x + h - x2 )*( x + h - x1 ) > 0.0 ) h = x2 - x; 
      ( *nrc_rkqs )( y, dydx, nvar, &x, h, eps, yscal, &hdid, &hnext, nrc_derivs ); 
      if ( hdid == h ) ++( *nok ); else ++( *nbad ); 
      if ( ( x - x2 )*( x2 - x1 ) >= 0.0 ) {
         for ( i = 1; i <= nvar; i ++ ) ystart[i]= y[i]; 
         if ( kmax ) {
            xp[++ kount]= x; 
            for ( i = 1; i <= nvar; i ++ ) yp[i][kount]= y[i]; 
         }
         nrc_free_vector ( dydx, 1, nvar ); 
         nrc_free_vector ( y, 1, nvar ); 
         nrc_free_vector ( yscal, 1, nvar ); 
         return; 
      }
      if ( fabs ( hnext ) <= hmin ) nrc_error ( "Step size too small in nrc_odeint" ); 
      h = hnext; 
   }
   nrc_error ( "Too many steps in routine nrc_odeint" ); 
}
#undef MAXSTP
#undef TINY
#undef NRANSI
