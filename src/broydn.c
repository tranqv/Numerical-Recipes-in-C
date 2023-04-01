
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define MAXITS 200
#define EPS     NR_CONST_EPSI
#define TOLF 1.0e-4
#define TOLX EPS
#define STPMX 100.0
#define TOLMIN 1.0e-6
#define FREERETURN {nrc_free_vector(fvec,1,n);nrc_free_vector(xold,1,n);\
	nrc_free_vector(w,1,n);nrc_free_vector(t,1,n);nrc_free_vector(s,1,n);\
	nrc_free_matrix(r,1,n,1,n);nrc_free_matrix(qt,1,n,1,n);nrc_free_vector(p,1,n);\
	nrc_free_vector(g,1,n);nrc_free_vector(fvcold,1,n);nrc_free_vector(d,1,n);\
	nrc_free_vector(c,1,n);return;}

int nn; 
sReal *fvec; 
void ( *nrfuncv )( int n, sReal v[], sReal f[] ); 

void nrc_broydn ( sReal x[], int n, int *check, 
   void ( *vecfunc )( int, sReal [], sReal [] ) )
{
   void nrc_fdjac ( int n, sReal x[], sReal fvec[], sReal **df, 
      void ( *vecfunc )( int, sReal [], sReal [] ) ); 
   sReal nrc_fmin ( sReal x[] ); 
   void nrc_lnsrch ( int n, sReal xold[], sReal fold, sReal g[], sReal p[], sReal x[], 
       sReal *f, sReal stpmax, int *check, sReal ( *func )( sReal [] ) ); 
   void nrc_qrdcmp ( sReal **a, int n, sReal *c, sReal *d, int *sing ); 
   void nrc_qrupdt ( sReal **r, sReal **qt, int n, sReal u[], sReal v[] ); 
   void nrc_rsolv ( sReal **a, int n, sReal d[], sReal b[] ); 
   int i, its, j, k, restrt, sing, skip; 
   sReal den, f, fold, stpmax, sum, temp, test, *c, *d, *fvcold; 
   sReal *g, *p, **qt, **r, *s, *t, *w, *xold; 

   c = nrc_vector ( 1, n ); 
   d = nrc_vector ( 1, n ); 
   fvcold = nrc_vector ( 1, n ); 
   g = nrc_vector ( 1, n ); 
   p = nrc_vector ( 1, n ); 
   qt = nrc_matrix ( 1, n, 1, n ); 
   r = nrc_matrix ( 1, n, 1, n ); 
   s = nrc_vector ( 1, n ); 
   t = nrc_vector ( 1, n ); 
   w = nrc_vector ( 1, n ); 
   xold = nrc_vector ( 1, n ); 
   fvec = nrc_vector ( 1, n ); 
   nn = n; 
   nrfuncv = vecfunc; 
   f = nrc_fmin ( x ); 
   test = 0.0; 
   for ( i = 1; i <= n; i ++ )
      if ( fabs ( fvec[i] ) > test ) test = fabs ( fvec[i] ); 
   if ( test < 0.01*TOLF ) {
      *check = 0; 
      FREERETURN
   }
   for ( sum = 0.0, i = 1; i <= n; i ++ ) sum += SQR ( x[i] ); 
   stpmax = STPMX*FMAX ( sqrt ( sum ), ( sReal ) n ); 
   restrt = 1; 
   for ( its = 1; its <= MAXITS; its ++ ) {
      if ( restrt ) {
         nrc_fdjac ( n, x, fvec, r, vecfunc ); 
         nrc_qrdcmp ( r, n, c, d, &sing ); 
         if ( sing ) nrc_error ( "singular Jacobian in nrc_broydn" ); 
         for ( i = 1; i <= n; i ++ ) {
            for ( j = 1; j <= n; j ++ ) qt[i][j]= 0.0; 
            qt[i][i]= 1.0; 
         }
         for ( k = 1; k < n; k ++ ) {
            if ( c[k] ) {
               for ( j = 1; j <= n; j ++ ) {
                  sum = 0.0; 
                  for ( i = k; i <= n; i ++ )
                     sum += r[i][k]*qt[i][j]; 
                  sum /= c[k]; 
                  for ( i = k; i <= n; i ++ )
                     qt[i][j] -= sum*r[i][k]; 
               }
            }
         }
         for ( i = 1; i <= n; i ++ ) {
            r[i][i]= d[i]; 
            for ( j = 1; j < i; j ++ ) r[i][j]= 0.0; 
         }
      } else {
         for ( i = 1; i <= n; i ++ ) s[i]= x[i]- xold[i]; 
         for ( i = 1; i <= n; i ++ ) {
            for ( sum = 0.0, j = i; j <= n; j ++ ) sum += r[i][j]*s[j]; 
            t[i]= sum; 
         }
         skip = 1; 
         for ( i = 1; i <= n; i ++ ) {
            for ( sum = 0.0, j = 1; j <= n; j ++ ) sum += qt[j][i]*t[j]; 
            w[i]= fvec[i]- fvcold[i]- sum; 
            if ( fabs ( w[i] ) >= EPS*( fabs ( fvec[i] )+ fabs ( fvcold[i] ) ) ) skip = 0; 
            else w[i]= 0.0; 
         }
         if ( !skip ) {
            for ( i = 1; i <= n; i ++ ) {
               for ( sum = 0.0, j = 1; j <= n; j ++ ) sum += qt[i][j]*w[j]; 
               t[i]= sum; 
            }
            for ( den = 0.0, i = 1; i <= n; i ++ ) den += SQR ( s[i] ); 
            for ( i = 1; i <= n; i ++ ) s[i] /= den; 
            nrc_qrupdt ( r, qt, n, t, s ); 
            for ( i = 1; i <= n; i ++ ) {
               if ( r[i][i] == 0.0 ) nrc_error ( "r singular in nrc_broydn" ); 
               d[i]= r[i][i]; 
            }
         }
      }
      for ( i = 1; i <= n; i ++ ) {
         for ( sum = 0.0, j = 1; j <= n; j ++ ) sum += qt[i][j]*fvec[j]; 
         p[i] = - sum; 
      }
      for ( i = n; i >= 1; i -- ) {
         for ( sum = 0.0, j = 1; j <= i; j ++ ) sum -= r[j][i]*p[j]; 
         g[i]= sum; 
      }
      for ( i = 1; i <= n; i ++ ) {
         xold[i]= x[i]; 
         fvcold[i]= fvec[i]; 
      }
      fold = f; 
      nrc_rsolv ( r, n, d, p ); 
      nrc_lnsrch ( n, xold, fold, g, p, x, &f, stpmax, check, nrc_fmin ); 
      test = 0.0; 
      for ( i = 1; i <= n; i ++ )
         if ( fabs ( fvec[i] ) > test ) test = fabs ( fvec[i] ); 
      if ( test < TOLF ) {
         *check = 0; 
         FREERETURN
      }
      if ( *check ) {
         if ( restrt ) FREERETURN
         else {
            test = 0.0; 
            den = FMAX ( f, 0.5*n ); 
            for ( i = 1; i <= n; i ++ ) {
               temp = fabs ( g[i] )*FMAX ( fabs ( x[i] ), 1.0 )/den; 
               if ( temp > test ) test = temp; 
            }
            if ( test < TOLMIN ) FREERETURN
            else restrt = 1; 
         }
      } else {
         restrt = 0; 
         test = 0.0; 
         for ( i = 1; i <= n; i ++ ) {
            temp =( fabs ( x[i]- xold[i] ) )/FMAX ( fabs ( x[i] ), 1.0 ); 
            if ( temp > test ) test = temp; 
         }
         if ( test < TOLX ) FREERETURN
      }
   }
   nrc_error ( "MAXITS exceeded in nrc_broydn" ); 
   FREERETURN
}
#undef MAXITS
#undef EPS
#undef TOLF
#undef TOLMIN
#undef TOLX
#undef STPMX
#undef FREERETURN
#undef NRANSI
