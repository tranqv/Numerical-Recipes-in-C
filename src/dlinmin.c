
#include "nrc_types.h"

#define NRANSI
#include "nrc_util.h"
#define TOL 2.0e-4

int ncom; 
sReal *pcom, *xicom, ( *nrfunc )( sReal [] ); 
void ( *nrdfun )( sReal [], sReal [] ); 

void nrc_dlinmin ( sReal p[], sReal xi[], int n, sReal *fret, sReal ( *func )( sReal [] ), 
   void ( *dfunc )( sReal [], sReal [] ) )
{
   sReal nrc_dbrent ( sReal ax, sReal bx, sReal cx, 
      sReal ( *f )( sReal ), sReal ( *df )( sReal ), sReal tol, sReal *xmin ); 
   sReal nrc_f1dim ( sReal x ); 
   sReal nrc_df1dim ( sReal x ); 
   void nrc_mnbrak ( sReal *ax, sReal *bx, sReal *cx, sReal *fa, sReal *fb, 
      sReal *fc, sReal ( *func )( sReal ) ); 
   int j; 
   sReal xx, xmin, fx, fb, fa, bx, ax; 

   ncom = n; 
   pcom = nrc_vector ( 1, n ); 
   xicom = nrc_vector ( 1, n ); 
   nrfunc = func; 
   nrdfun = dfunc; 
   for ( j = 1; j <= n; j ++ ) {
      pcom[j]= p[j]; 
      xicom[j]= xi[j]; 
   }
   ax = 0.0; 
   xx = 1.0; 
   nrc_mnbrak ( &ax, &xx, &bx, &fa, &fx, &fb, nrc_f1dim ); 
   *fret = nrc_dbrent ( ax, xx, bx, nrc_f1dim, nrc_df1dim, TOL, &xmin ); 
   for ( j = 1; j <= n; j ++ ) {
      xi[j] *= xmin; 
      p[j] += xi[j]; 
   }
   nrc_free_vector ( xicom, 1, n ); 
   nrc_free_vector ( pcom, 1, n ); 
}
#undef TOL
#undef NRANSI
