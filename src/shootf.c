
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define EPS    1.0e-14

extern int nn2, nvar; 
extern sReal x1, x2, xf; 

int kmax, kount; 
sReal *xp, **yp, dxsav; 

void nrc_shootf ( int n, sReal v[], sReal f[] )
{
   void nrc_derivs ( sReal x, sReal y[], sReal dydx[] ); 
   void nrc_load1 ( sReal x1, sReal v1[], sReal y[] ); 
   void nrc_load2 ( sReal x2, sReal v2[], sReal y[] ); 
   void nrc_odeint ( sReal ystart[], int nvar, sReal x1, sReal x2, 
      sReal eps, sReal h1, sReal hmin, int *nok, int *nbad, 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ), 
      void ( *nrc_rkqs )( sReal [], sReal [], int, sReal *, sReal, sReal, 
      sReal [], sReal *, sReal *, void ( * )( sReal, sReal [], sReal [] ) ) ); 
   void nrc_rkqs ( sReal y[], sReal dydx[], int n, sReal *x, 
      sReal htry, sReal eps, sReal yscal[], sReal *hdid, sReal *hnext, 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ) ); 
   void nrc_score ( sReal xf, sReal y[], sReal f[] ); 
   int i, nbad, nok; 
   sReal h1, hmin = 0.0, *nrc_f1, *nrc_f2, *y; 

   nrc_f1 = nrc_vector ( 1, nvar ); 
   nrc_f2 = nrc_vector ( 1, nvar ); 
   y = nrc_vector ( 1, nvar ); 
   kmax = 0; 
   h1 =( x2 - x1 )/100.0; 
   nrc_load1 ( x1, v, y ); 
   nrc_odeint ( y, nvar, x1, xf, EPS, h1, hmin, &nok, &nbad, nrc_derivs, nrc_rkqs ); 
   nrc_score ( xf, y, nrc_f1 ); 
   nrc_load2 ( x2, &v[nn2], y ); 
   nrc_odeint ( y, nvar, x2, xf, EPS, h1, hmin, &nok, &nbad, nrc_derivs, nrc_rkqs ); 
   nrc_score ( xf, y, nrc_f2 ); 
   for ( i = 1; i <= n; i ++ ) f[i]= nrc_f1[i]- nrc_f2[i]; 
   nrc_free_vector ( y, 1, nvar ); 
   nrc_free_vector ( nrc_f2, 1, nvar ); 
   nrc_free_vector ( nrc_f1, 1, nvar ); 
}
#undef EPS
#undef NRANSI
