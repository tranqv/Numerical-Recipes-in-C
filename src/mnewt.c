
#include "nrc_types.h"

#include <math.h>
#define NRANSI
#include "nrc_util.h"

void usrfun ( sReal *x, int n, sReal *fvec, sReal **fjac ); 
#define FREERETURN {nrc_free_matrix(fjac,1,n,1,n);nrc_free_vector(fvec,1,n);\
	nrc_free_vector(p,1,n);nrc_free_ivector(indx,1,n);return;}

void nrc_mnewt ( int ntrial, sReal x[], int n, sReal tolx, sReal tolf )
{
   void nrc_lubksb ( sReal **a, int n, int *indx, sReal b[] ); 
   void nrc_ludcmp ( sReal **a, int n, int *indx, sReal *d ); 
   int k, i, *indx; 
   sReal errx, errf, d, *fvec, **fjac, *p; 

   indx = nrc_ivector ( 1, n ); 
   p = nrc_vector ( 1, n ); 
   fvec = nrc_vector ( 1, n ); 
   fjac = nrc_matrix ( 1, n, 1, n ); 
   for ( k = 1; k <= ntrial; k ++ ) {
      usrfun ( x, n, fvec, fjac ); 
      errf = 0.0; 
      for ( i = 1; i <= n; i ++ ) errf += fabs ( fvec[i] ); 
      if ( errf <= tolf ) FREERETURN
      for ( i = 1; i <= n; i ++ ) p[i] = - fvec[i]; 
      nrc_ludcmp ( fjac, n, indx, &d ); 
      nrc_lubksb ( fjac, n, indx, p ); 
      errx = 0.0; 
      for ( i = 1; i <= n; i ++ ) {
         errx += fabs ( p[i] ); 
         x[i] += p[i]; 
      }
      if ( errx <= tolx ) FREERETURN
   }
   FREERETURN
}
#undef FREERETURN
#undef NRANSI
