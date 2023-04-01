
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define EPS    1.0e-14

extern int nvar; 
extern sReal x1, x2; 

int kmax, kount; 
sReal *xp, **yp, dxsav; 

void nrc_shoot ( int n, sReal v[], sReal f[] )
{
   void nrc_derivs ( sReal x, sReal y[], sReal dydx[] ); 
   void nrc_load ( sReal x1, sReal v[], sReal y[] ); 
   void nrc_odeint ( sReal ystart[], int nvar, sReal x1, sReal x2, 
      sReal eps, sReal h1, sReal hmin, int *nok, int *nbad, 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ), 
      void ( *nrc_rkqs )( sReal [], sReal [], int, sReal *, sReal, sReal, 
      sReal [], sReal *, sReal *, void ( * )( sReal, sReal [], sReal [] ) ) ); 
   void nrc_rkqs ( sReal y[], sReal dydx[], int n, sReal *x, 
      sReal htry, sReal eps, sReal yscal[], sReal *hdid, sReal *hnext, 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ) ); 
   void nrc_score ( sReal xf, sReal y[], sReal f[] ); 
   int nbad, nok; 
   sReal h1, hmin = 0.0, *y; 

   y = nrc_vector ( 1, nvar ); 
   kmax = 0; 
   h1 =( x2 - x1 )/100.0; 
   nrc_load ( x1, v, y ); 
   nrc_odeint ( y, nvar, x1, x2, EPS, h1, hmin, &nok, &nbad, nrc_derivs, nrc_rkqs ); 
   nrc_score ( x2, y, f ); 
   nrc_free_vector ( y, 1, nvar ); 
}
#undef EPS
#undef NRANSI
