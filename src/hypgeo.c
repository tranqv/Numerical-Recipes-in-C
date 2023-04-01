
#include "nrc_types.h"

#include <math.h>
#include "nrc_complex.h"
#define NRANSI
#include "nrc_util.h"
#define EPS    1.0e-14

sComp aa, bb, cc, z0, dz; 

int kmax, kount; 
sReal *xp, **yp, dxsav; 

sComp nrc_hypgeo ( sComp a, sComp b, sComp c, sComp z )
{
   void nrc_bsstep ( sReal y[], sReal dydx[], int nv, sReal *xx, sReal htry, 
      sReal eps, sReal yscal[], sReal *hdid, sReal *hnext, 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ) ); 
   void nrc_hypdrv ( sReal s, sReal yy[], sReal dyyds[] ); 
   void nrc_hypser ( sComp a, sComp b, sComp c, sComp z, 
      sComp *series, sComp *deriv ); 
   void nrc_odeint ( sReal ystart[], int nvar, sReal x1, sReal x2, 
      sReal eps, sReal h1, sReal hmin, int *nok, int *nbad, 
      void ( *nrc_derivs )( sReal, sReal [], sReal [] ), 
      void ( *nrc_rkqs )( sReal [], sReal [], int, sReal *, sReal, sReal, 
      sReal [], sReal *, sReal *, void ( * )( sReal, sReal [], sReal [] ) ) ); 
   int nbad, nok; 
   sComp ans, y[3]; 
   sReal *yy; 

   kmax = 0; 
   if ( z.r*z.r + z.i*z.i <= 0.25 ) {
      nrc_hypser ( a, b, c, z, &ans, &y[2] ); 
      return ans; 
   }
   else if ( z.r < 0.0 ) z0 = nrc_cmplx ( - 0.5, 0.0 ); 
   else if ( z.r <= 1.0 ) z0 = nrc_cmplx ( 0.5, 0.0 ); 
   else z0 = nrc_cmplx ( 0.0, z.i >= 0.0 ? 0.5 : - 0.5 ); 
   aa = a; 
   bb = b; 
   cc = c; 
   dz = nrc_csub ( z, z0 ); 
   nrc_hypser ( aa, bb, cc, z0, &y[1], &y[2] ); 
   yy = nrc_vector ( 1, 4 ); 
   yy[1]= y[1].r; 
   yy[2]= y[1].i; 
   yy[3]= y[2].r; 
   yy[4]= y[2].i; 
   nrc_odeint ( yy, 4, 0.0, 1.0, EPS, 0.1, 0.0001, &nok, &nbad, nrc_hypdrv, nrc_bsstep ); 
   y[1]= nrc_cmplx ( yy[1], yy[2] ); 
   nrc_free_vector ( yy, 1, 4 ); 
   return y[1]; 
}
#undef EPS
#undef NRANSI
