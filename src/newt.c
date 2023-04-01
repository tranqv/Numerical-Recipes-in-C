
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"
#define MAXITS 200
#define TOLF 1.0e-4
#define TOLMIN 1.0e-6
#define TOLX 1.0e-7
#define STPMX 100.0

int nn; 
sReal *fvec; 
void ( *nrfuncv )( int n, sReal v[], sReal f[] ); 
#define FREERETURN {nrc_free_vector(fvec,1,n);nrc_free_vector(xold,1,n);\
	nrc_free_vector(p,1,n);nrc_free_vector(g,1,n);nrc_free_matrix(fjac,1,n,1,n);\
	nrc_free_ivector(indx,1,n);return;}

void nrc_newt ( sReal x[], int n, int *check, 
   void ( *vecfunc )( int, sReal [], sReal [] ) )
{
   void nrc_fdjac ( int n, sReal x[], sReal fvec[], sReal **df, 
      void ( *vecfunc )( int, sReal [], sReal [] ) ); 
   sReal nrc_fmin ( sReal x[] ); 
   void nrc_lnsrch ( int n, sReal xold[], sReal fold, sReal g[], sReal p[], sReal x[], 
       sReal *f, sReal stpmax, int *check, sReal ( *func )( sReal [] ) ); 
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d ); 
   int i, its, j, *indx; 
   sReal d, den, f, fold, stpmax, sum, temp, test, **fjac, *g, *p, *xold; 

   indx = nrc_ivector ( 1, n ); 
   fjac = nrc_matrix ( 1, n, 1, n ); 
   g = nrc_vector ( 1, n ); 
   p = nrc_vector ( 1, n ); 
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
   for ( its = 1; its <= MAXITS; its ++ ) {
      nrc_fdjac ( n, x, fvec, fjac, vecfunc ); 
      for ( i = 1; i <= n; i ++ ) {
         for ( sum = 0.0, j = 1; j <= n; j ++ ) sum += fjac[j][i]*fvec[j]; 
         g[i]= sum; 
      }
      for ( i = 1; i <= n; i ++ ) xold[i]= x[i]; 
      fold = f; 
      for ( i = 1; i <= n; i ++ ) p[i] = - fvec[i]; 
      nrc_ludcmp ( fjac, n, indx, &d ); 
      nrc_lubksb ( fjac, n, indx, p ); 
      nrc_lnsrch ( n, xold, fold, g, p, x, &f, stpmax, check, nrc_fmin ); 
      test = 0.0; 
      for ( i = 1; i <= n; i ++ )
         if ( fabs ( fvec[i] ) > test ) test = fabs ( fvec[i] ); 
      if ( test < TOLF ) {
         *check = 0; 
         FREERETURN
      }
      if ( *check ) {
         test = 0.0; 
         den = FMAX ( f, 0.5*n ); 
         for ( i = 1; i <= n; i ++ ) {
            temp = fabs ( g[i] )*FMAX ( fabs ( x[i] ), 1.0 )/den; 
            if ( temp > test ) test = temp; 
         }
         *check =( test < TOLMIN ? 1 : 0 ); 
         FREERETURN
      }
      test = 0.0; 
      for ( i = 1; i <= n; i ++ ) {
         temp =( fabs ( x[i]- xold[i] ) )/FMAX ( fabs ( x[i] ), 1.0 ); 
         if ( temp > test ) test = temp; 
      }
      if ( test < TOLX ) FREERETURN
   }
   nrc_error ( "MAXITS exceeded in nrc_newt" ); 
}
#undef MAXITS
#undef TOLF
#undef TOLMIN
#undef TOLX
#undef STPMX
#undef FREERETURN
#undef NRANSI
