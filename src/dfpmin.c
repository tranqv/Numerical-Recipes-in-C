
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define ITMAX 200
#define EPS     NR_CONST_EPSI
#define TOLX (4*EPS)
#define STPMX 100.0

#define FREEALL nrc_free_vector(xi,1,n);nrc_free_vector(pnew,1,n); \
nrc_free_matrix(hessin,1,n,1,n);nrc_free_vector(hdg,1,n);nrc_free_vector(g,1,n); \
nrc_free_vector(dg,1,n);

void nrc_dfpmin ( sReal p[], int n, sReal gtol, int *iter, sReal *fret, 
   sReal ( *func )( sReal [] ), void ( *dfunc )( sReal [], sReal [] ) )
{
   void nrc_lnsrch ( int n, sReal xold[], sReal fold, sReal g[], sReal p[], sReal x[], 
       sReal *f, sReal stpmax, int *check, sReal ( *func )( sReal [] ) ); 
   int check, i, its, j; 
   sReal den, fac, fad, fae, fp, stpmax, sum = 0.0, sumdg, sumxi, temp, test; 
   sReal *dg, *g, *hdg, **hessin, *pnew, *xi; 

   dg = nrc_vector ( 1, n ); 
   g = nrc_vector ( 1, n ); 
   hdg = nrc_vector ( 1, n ); 
   hessin = nrc_matrix ( 1, n, 1, n ); 
   pnew = nrc_vector ( 1, n ); 
   xi = nrc_vector ( 1, n ); 
   fp =( *func )( p ); 
   ( *dfunc )( p, g ); 
   for ( i = 1; i <= n; i ++ ) {
      for ( j = 1; j <= n; j ++ ) hessin[i][j]= 0.0; 
      hessin[i][i]= 1.0; 
      xi[i] = - g[i]; 
      sum += p[i]*p[i]; 
   }
   stpmax = STPMX*FMAX ( sqrt ( sum ), ( sReal ) n ); 
   for ( its = 1; its <= ITMAX; its ++ ) {
      *iter = its; 
      nrc_lnsrch ( n, p, fp, g, xi, pnew, fret, stpmax, &check, func ); 
      fp = *fret; 
      for ( i = 1; i <= n; i ++ ) {
         xi[i]= pnew[i]- p[i]; 
         p[i]= pnew[i]; 
      }
      test = 0.0; 
      for ( i = 1; i <= n; i ++ ) {
         temp = fabs ( xi[i] )/FMAX ( fabs ( p[i] ), 1.0 ); 
         if ( temp > test ) test = temp; 
      }
      if ( test < TOLX ) {
         FREEALL
         return; 
      }
      for ( i = 1; i <= n; i ++ ) dg[i]= g[i]; 
      ( *dfunc )( p, g ); 
      test = 0.0; 
      den = FMAX ( *fret, 1.0 ); 
      for ( i = 1; i <= n; i ++ ) {
         temp = fabs ( g[i] )*FMAX ( fabs ( p[i] ), 1.0 )/den; 
         if ( temp > test ) test = temp; 
      }
      if ( test < gtol ) {
         FREEALL
         return; 
      }
      for ( i = 1; i <= n; i ++ ) dg[i]= g[i]- dg[i]; 
      for ( i = 1; i <= n; i ++ ) {
         hdg[i]= 0.0; 
         for ( j = 1; j <= n; j ++ ) hdg[i] += hessin[i][j]*dg[j]; 
      }
      fac = fae = sumdg = sumxi = 0.0; 
      for ( i = 1; i <= n; i ++ ) {
         fac += dg[i]*xi[i]; 
         fae += dg[i]*hdg[i]; 
         sumdg += SQR ( dg[i] ); 
         sumxi += SQR ( xi[i] ); 
      }
      if ( fac > sqrt ( EPS*sumdg*sumxi ) ) {
         fac = 1.0/fac; 
         fad = 1.0/fae; 
         for ( i = 1; i <= n; i ++ ) dg[i]= fac*xi[i]- fad*hdg[i]; 
         for ( i = 1; i <= n; i ++ ) {
            for ( j = i; j <= n; j ++ ) {
               hessin[i][j] += fac*xi[i]*xi[j]
               - fad*hdg[i]*hdg[j]+ fae*dg[i]*dg[j]; 
               hessin[j][i]= hessin[i][j]; 
            }
         }
      }
      for ( i = 1; i <= n; i ++ ) {
         xi[i]= 0.0; 
         for ( j = 1; j <= n; j ++ ) xi[i] -= hessin[i][j]*g[j]; 
      }
   }
   nrc_error ( "too many iterations in nrc_dfpmin" ); 
   FREEALL
}
#undef ITMAX
#undef EPS
#undef TOLX
#undef STPMX
#undef FREEALL
#undef NRANSI
